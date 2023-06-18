#include<iostream>
#include<parser.h>
#include<device.hpp>
#include<unistd.h>
#include<plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include<plog/Appenders/ColorConsoleAppender.h>
#include<envvars.h>
#include<runner.hpp>

void remove_default_semaphore(){
    if(sem_unlink(KS_SEMAPHORE)!=0){
        Logger::error("Failed to remove ks-semaphore");
    }
}

void register_cleanup_handlers(){
    std::atexit(remove_default_semaphore);
}

int main(int argc,char** argv){
    if(getuid()!=0){
        std::cerr<<"kSentinel should be run as root"<<std::endl;
    }
    else{
        register_cleanup_handlers();
        DeviceUtils::check_all_env_vars();
        static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
        std::string log_file = std::string(std::getenv(KS_CONFIG_DIR))+"/kSentinel_logs.txt";
        plog::init(plog::verbose,(plog::util::nchar*)log_file.c_str()).addAppender(&consoleAppender);
        setup_parser(argc,argv);
    }
    return 0;
}