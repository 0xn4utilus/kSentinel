#include <device.hpp>
#include <unistd.h>
#include <pwd.h>
#include <utils.hpp>
#include <sys/utsname.h>
#include <fstream>
#include <uberswitch.hpp>
#include<logger.hpp>
#include<networking.hpp>
#include <algorithm>
#include<utils.hpp>

std::string DeviceUtils::get_device_key(){
    YamlUtils<std::string>yaml_utils;
    std::string kscore_api = yaml_utils.read_config_var("KS_KSCORE_API");
    std::string device_id = get_device_id();
    if(device_id.length()==0){
        Logger::error("Error! Failed to read device id");
        return "";
    }
    std::string key_retrieval_url = kscore_api + "/key/"+device_id+"?token="+this->get_auth_token();
    HttpRequest http_request(key_retrieval_url);
    std::unique_ptr<http_response>response = http_request.http_get();
    if(response->status_code!=200){
        Logger::error(response->response);
        return "";
    }
    return response->response;
}

std::string DeviceUtils::get_auth_token(){
    std::string config_dir = FileUtils::get_config_dir();
    std::string token_file = config_dir+"/.kst";
    std::string token;
    std::ifstream ifile(token_file);
    std::getline(ifile,token);
    ifile.close();  
    return token;
}

std::string DeviceUtils::get_device_id(){
    std::string config_dir = FileUtils::get_config_dir();
    std::string fileName = config_dir+"/.ksdata";
    std::string device_id;
    std::ifstream ifile(fileName);
    std::getline(ifile,device_id);
    ifile.close(); 
    return device_id;  
}
std::string DeviceUtils::fetch_events(){
    std::string device_id = this->get_device_id();
    YamlUtils<std::string> yaml_utils;
    std::string kscore_api = yaml_utils.read_config_var("KS_KSCORE_API");
    std::string event_endpoint = kscore_api + "/events/"+device_id;
    HttpRequest http_request(event_endpoint);
    std::unique_ptr<http_response> response = http_request.http_get();
    if(response->status_code!=200){
        Logger::error(response->response);
        return nullptr;
    }
    return response->response;
}

DeviceUtils::DeviceUtils(){
    YamlUtils<std::string>* yaml_utils = new YamlUtils<std::string>;
    std::string kscore_api = yaml_utils->read_config_var("KS_KSCORE_API");
    if(kscore_api.length()==0){
        std::cerr<<"Error! Failed to fetch KS_KSCORE_API in the configuration file"<<std::endl;
        std::exit(1);
    }
    this->device_check_url = kscore_api + "/checkdevice";
    this->device_reg_url = kscore_api + "/device";
    delete yaml_utils;
}

void DeviceUtils::check_all_env_vars(){
    bool error = false;
    if(!std::getenv("KS_CONFIG_DIR")){
        error = true;
        std::cerr<<"Environment variable KS_CONFIG_DIR not found"<<std::endl;
    }
    if(error){
        std::exit(1);
    }
}
std::string DeviceUtils::get_username(){
    uid_t uid = geteuid();
    passwd* pw = getpwuid(uid);
    if(pw){
        return std::string(pw->pw_name);
    }
    return {};
}

std::string DeviceUtils::generate_device_id(){
    std::string config_dir = FileUtils::get_config_dir();
    std::string device_id = this->get_username();
    std::ifstream ifile(config_dir+"/.ksdata");
    std::stringstream buffer;
    buffer<<ifile.rdbuf();
    if(buffer.str().length()==0){
        std::string rand_string = OtherUtils::generate_rand_string(10,TYPE_NUMBER);
        device_id += "_"+rand_string;
    }
    else{
        device_id = buffer.str();
    }
    return device_id;
}

std::string DeviceUtils::get_kernel_version(){
    struct utsname* utsbuffer = new struct utsname;
    uname(utsbuffer);
    std::string release = utsbuffer->release;
    delete utsbuffer;
    return release;
}

std::string DeviceUtils::get_device_type(){
    DockerDetection* docker_detection = new DockerDetection;
    VMDetection* vm_detection = new VMDetection;
    HostDetection* host_detection = new HostDetection;
    std::string host = host_detection->detect_host();
    if(docker_detection->is_docker_container()){
        return "Docker container";
    }
    if(vm_detection->is_virtual_machine()){
        return "Virtual machine";
    }
    delete docker_detection;
    delete vm_detection;
    delete host_detection;
    return host;
}
bool DeviceUtils::register_device(){
    std::unordered_map<std::string,std::string>umap;
    umap["device_id"] = this->generate_device_id();
    umap["device_kernel"] = this->get_kernel_version();
    umap["device_type"] = this->get_device_type();
    Logger::info("Verifying registration status");
    bool result;
    if(!this->is_device_registered(umap["device_id"])){
        HttpRequest http_request(this->device_reg_url);
        std::unique_ptr<http_response>response = http_request.http_post(umap);
        if(response->success==false || response->status_code!=200){
            Logger::fatal(response->response);
        }
        const char* config_dir = std::getenv("KS_CONFIG_DIR");
        if(!config_dir){
            Logger::fatal("Error! Environment variable KS_CONFIG_DIR not found");
        }
        std::string metadata_file = std::string(config_dir)+"/"+".ksdata";
        std::ofstream ofile(metadata_file,std::ios::out);
        ofile.write(umap["device_id"].c_str(),umap["device_id"].length());
        ofile.close();
        Logger::info(response->response);
    }
    return result;
}

bool DeviceUtils::is_device_registered(std::string device_id){
    HttpRequest http_request(this->device_check_url+"/"+device_id);
    std::unique_ptr<http_response>response =  http_request.http_get();
    if(response->success==false || response->status_code!=200){
        Logger::fatal(response->response);
    }
    if(response->response=="Device has not been registered yet"){
        Logger::info(response->response);
        return false;
    }
    Logger::warning(response->response);
    return true;
}

bool DockerDetection::is_docker_container(){
    if(this->detect_container_m1()||this->detect_container_m2()||this->detect_container_m3()){
        return true;
    }
    return false;
}

bool DockerDetection::detect_container_m1(){
    std::ifstream ifile;
    ifile.open("/.dockerenv");
    if(ifile){
        return true;
    }
    return false;
}

bool DockerDetection::detect_container_m2(){
    std::ifstream ifile("/proc/1/sched");
    std::stringstream buffer;
    std::string bufstr;
    bool result;
    if(ifile){
        buffer<<ifile.rdbuf();
        bufstr = buffer.str();
        if(bufstr.substr(0,4)!="init" || bufstr.substr(0,7)!="systemd"){
            result = true;
        }
    }
    ifile.close();
    return result;
}

bool DockerDetection::detect_container_m3(){
    return false;
}

bool VMDetection::detect_vm_m1(){
    std::ifstream sysVendorFile("/sys/class/dmi/id/sys_vendor");
    if(sysVendorFile.is_open()){
        std::getline(sysVendorFile,sysVendor);
        uswitch(sysVendor){
            ucase("VMware, Inc."):
                return true;
            ucase("QEMU"):
                return true;
            ucase("innotek GmbH"):
                return true;
            default:
                return false;
        }
    }
    return true;
}

bool VMDetection::detect_vm_m2(){
    std::ifstream chassisNumberFile("/sys/class/dmi/id/chassis_serial");
    if(chassisNumberFile.is_open()){
        std::getline(chassisNumberFile,chassisNumber);
        std::transform(chassisNumber.begin(),chassisNumber.end(),chassisNumber.begin(), ::tolower);
        uswitch(chassisNumber){
            ucase(""):
                return true;
            ucase("0"):
                return true;
            ucase("none"):
                return true;
            default:
                return false;
        }
    }
    return true;
}

bool VMDetection::detect_vm_m3(){
	__asm__ volatile("cpuid" \
			: "=b"(ebx), \
			"=c"(ecx), \
			"=d"(edx) \
			: "a"(0x40000000));
	sprintf(vendor  , "%c%c%c%c", ebx, (ebx >> 8), (ebx >> 16), (ebx >> 24));
	sprintf(vendor+4, "%c%c%c%c", ecx, (ecx >> 8), (ecx >> 16), (ecx >> 24));
	sprintf(vendor+8, "%c%c%c%c", edx, (edx >> 8), (edx >> 16), (edx >> 24));
	vendor[12] = 0x00;
    
    strVendor = vendor;
    uswitch(strVendor){
        ucase("KVMKVMKVM"):
            return true;
        ucase("Microsoft Hv"):
            return true;
        ucase("VMwareVMware"):
            return true;
        ucase("XenVMMXenVMM"):
            return true;
        ucase("prl hyperv"):
            return true;
        ucase("VBoxVBoxVBox"):
            return true;
        default:
            return false;
    }
    return false;
}

bool VMDetection::is_virtual_machine(){
    return this->detect_vm_m1() || this->detect_vm_m2() || this->detect_vm_m3();
}

std::string HostDetection::detect_host(){
    struct utsname utsbuffer;
    uname(&utsbuffer);
    return std::string(utsbuffer.machine);
}