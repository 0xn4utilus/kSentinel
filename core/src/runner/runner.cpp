#include<runner.hpp>
#include<fcntl.h>
#include<iostream>
#include<signal.h>
#include<errno.h>
#include<models.h>
#include<networking.hpp>
#include<device.hpp>
#include<logger.hpp>
#include<unistd.h>
#include<auth.hpp>

Runner:: Runner(){
    this->device_utils = std::make_unique<DeviceUtils>();
}

bool Runner::is_ksentinel_running(){
    Logger::info("Starting kSentinel");
    sem_t* semaphore = sem_open(KS_SEMAPHORE,O_CREAT|O_EXCL,0644,1);
    if(semaphore==SEM_FAILED){
        if(errno==EEXIST){
            Logger::fatal("Another instance of kSentinel is already running");
        }
        else{
            Logger::fatal("Semaphore creation failed");
        }
    }
    else{
        this->semaphore = semaphore;
    }
    return false;
}

void Runner::run(){
    signal(SIGINT,term_sighandler);
    signal(SIGTSTP,term_sighandler);
    Auth auth;
    if(!auth.is_logged_in()){
        std::exit(1);
    }
    Logger::info("Login successful");
    {
        DeviceUtils device_utils;
        device_utils.register_device();
    }
    while(1){
        this->ks_main();
        break;
    }
}

Runner::~Runner(){
    if(sem_unlink(KS_SEMAPHORE)!=0){
        Logger::fatal("Failed to unlink ks-semaphore");
    }
}

void Runner::term_sighandler(int signum){
    if(sem_unlink(KS_SEMAPHORE)!=0){
        Logger::fatal("Failed to unlink ks-semaphore");
    }
    Logger::fatal("Shutting down kSentinel");
}

void Runner::ks_fatal(std::string message){
    std::cerr<<message<<std::endl;
    std::exit(1);
}