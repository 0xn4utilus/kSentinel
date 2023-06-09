#include<device.hpp>
#include<unistd.h>
#include<pwd.h>
#include<utils.hpp>
#include<sys/utsname.h>
#include<fstream>

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

bool VMDetection::is_virtual_machine(){

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
