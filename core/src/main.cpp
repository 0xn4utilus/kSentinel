#include<iostream>
#include<parser.h>
#include<device.hpp>

int main(int argc,char** argv){
    DeviceUtils::check_all_env_vars();
    setup_parser(argc,argv);
}