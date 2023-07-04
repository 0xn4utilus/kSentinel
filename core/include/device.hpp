#ifndef DEVICE_H
#define DEVICE_H
#include<string>
#include<json/json.hpp>
#include<set>
#include<memory>
#include<utils.hpp>


using nlohmann::json;

class DeviceUtils{
    std::string device_reg_url;
    std::string device_check_url;
    std::unique_ptr<YamlUtils<std::string>>yaml_utils;
    public:
    DeviceUtils();
    static void check_all_env_vars();
    void clean_event_logs();
    std::string get_username();
    std::string get_device_id();
    std::string get_device_key();
    std::string get_auth_token();
    std::string generate_device_id();
    std::string get_kernel_version();
    std::string get_device_type();
    std::set<json>fetch_events();
    bool new_events_added();
    bool register_device();
    bool is_device_registered(std::string);
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