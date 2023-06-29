#include<runner.hpp>
#include<device.hpp>
#include<iostream>
#include<crypto/md5.hpp>
#include<fstream>
#include<set>


void Runner::ks_main(){
    Logger::debug("Running main loop");
    DeviceUtils device_utils;
    std::string events = device_utils.fetch_events();
    json json_data;
    try{
        json_data = json::parse(events);
    }
    catch(const std::exception &e){
        Logger::error("Found invalid event data");
        return;
    }
    std::string key = device_utils.get_device_key();
    if(key.length()==0){
        Logger::error("Failed to retrieve device key");
        return;
    }
    // Encrypt events using AES and store them in /.ksevents file
    Logger::debug(key);
}