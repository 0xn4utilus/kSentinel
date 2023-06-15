#include <device.hpp>
#include <unistd.h>
#include <pwd.h>
#include <utils.hpp>
#include <sys/utsname.h>
#include <fstream>
#include <uberswitch.hpp>
#include <algorithm>

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
    std::string device_id = this->get_username();
    std::string rand_string = OtherUtils::generate_rand_string(10,TYPE_NUMBER);
    device_id += "_"+rand_string;
    return device_id;
}

std::string DeviceUtils::get_kernel_version(){
    struct utsname* utsbuffer = new struct utsname;
    uname(utsbuffer);
    std::string release = utsbuffer->release;
    delete utsbuffer;
    return release;
}

bool DeviceUtils::register_device(){

}

bool DeviceUtils::is_device_registered(){
    
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
    if(ifile){
        buffer<<ifile.rdbuf();
        bufstr = buffer.str();
        if(bufstr.substr(0,4)!="init" || bufstr.substr(0,7)!="systemd"){
            return true;
        }
    }
    return false;
}

bool DockerDetection::detect_container_m3(){

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

std::string DockerDetection::detect_host(){
    return "docker_container";
}

std::string VMDetection::detect_host(){
    return "virtual_machine";
}
