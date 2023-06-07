#ifndef DEVICE_H
#define DEVICE_H
#include<string>
class DeviceUtils{
    public:
    std::string get_username();
    std::string get_device_id();
    std::string generate_device_id();
    std::string get_kernel_version();
    bool register_device();
    bool is_device_registered();
};
#endif