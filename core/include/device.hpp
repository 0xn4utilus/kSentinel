#ifndef DEVICE_H
#define DEVICE_H
#include<string>
class DeviceUtils{
    public:
    static void check_all_env_vars();
    std::string get_username();
    std::string get_device_id();
    std::string generate_device_id();
    std::string get_kernel_version();
    bool register_device();
    bool is_device_registered();
};

class HostDetection{
    public:
    virtual std::string detect_host();
};

class DockerDetection:public HostDetection{
    public:
    std::string detect_host();
    bool is_docker_container();
    bool detect_container_m1();
    bool detect_container_m2();
    bool detect_container_m3();
};

class VMDetection:public HostDetection{
    private:
        std::string chassisNumber;
        std::string sysVendor;
        int ebx = 0,ecx = 0,edx = 0;
        char vendor[0x10];
        std::string strVendor;
    public:
        std::string detect_host();
        bool is_virtual_machine();
        bool detect_vm_m1();
        bool detect_vm_m2();
        bool detect_vm_m3();
};
#endif