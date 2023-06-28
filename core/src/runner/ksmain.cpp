#include<runner.hpp>
#include<device.hpp>
#include<iostream>
#include<crypto/md5.hpp>

void Runner::ks_main(){
    Logger::debug("Running main loop");
    DeviceUtils device_utils;
    std::string events = device_utils.fetch_events();
    json json_data = json::parse(events);
    Md5 md5;
    std::vector<std::string>hashes;
    for(auto data:json_data){
        md5.update(data.dump());
        hashes.push_back(md5.hexdigest());
    }
    for(auto hash:hashes){
        std::cout<<hash<<std::endl;
    }
}