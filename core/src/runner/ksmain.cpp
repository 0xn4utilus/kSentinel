#include<runner.hpp>
#include<device.hpp>
#include<iostream>
#include<crypto/md5.hpp>
#include<crypto/aes/aes.h>
#include<fstream>
#include<utils.hpp>
#include<set>



void Runner::ks_main(){
    std::set<json>events;
    events = this->device_utils->fetch_events();
    for(auto it:events){
        Logger::debug(it.dump());
    }
}