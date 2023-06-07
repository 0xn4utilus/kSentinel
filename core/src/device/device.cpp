#include<device.hpp>
#include<unistd.h>
#include<pwd.h>
#include<utils.hpp>
#include<sys/utsname.h>

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