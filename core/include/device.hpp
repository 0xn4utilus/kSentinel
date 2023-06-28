#ifndef DEVICE_H
#define DEVICE_H
#include<string>
#include<json/json.hpp>

using nlohmann::json;

class DeviceUtils{
    std::string device_reg_url;
    std::string device_check_url;
    public:
    DeviceUtils();
    static void check_all_env_vars();
    std::string get_username();
    std::string get_device_id();
    std::string generate_device_id();
    std::string get_kernel_version();
    std::string get_device_type();
    bool register_device();
    bool is_device_registered(std::string);
    std::string fetch_events();
};

class HostDetection{
    public:
    std::string detect_host();
};

class DockerDetection{
    public:
    bool is_docker_container();
    private:
    bool detect_container_m1();
    bool detect_container_m2();
    bool detect_container_m3();
    friend class HostDetection;
};

class VMDetection{
    private:
        std::string chassisNumber;
        std::string sysVendor;
        int ebx = 0,ecx = 0,edx = 0;
        char vendor[0x10];
        std::string strVendor;
        bool detect_vm_m1();
        bool detect_vm_m2();
        bool detect_vm_m3();
    public:
        bool is_virtual_machine();
        friend class HostDetection;
};
#endif