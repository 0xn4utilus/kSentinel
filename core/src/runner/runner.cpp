#include<runner.hpp>
#include<fcntl.h>
#include<iostream>
#include<signal.h>
#include<errno.h>

sem_t* globalSemaphore;
bool Runner::is_ksentinel_running(){
    sem_t* semaphore = sem_open(KS_SEMAPHORE,O_CREAT|O_EXCL,0644,1);
    if(semaphore==SEM_FAILED){
        if(errno==EEXIST){
            std::cout<<"Another instance of kSentinel is already running\n";
            std::exit(0);
        }
        else{
            std::cout<<"Semaphore creation failed\n";
            std::exit(0);
        }
    }
    else{
        this->semaphore = semaphore;
        globalSemaphore = semaphore;
        std::cout<<"Started kSentinel\n";
    }
    return false;
}

void Runner::run(){
    signal(SIGINT,sigint_handler);
    while(1){
    }
}

Runner::~Runner(){
    if(sem_destroy(this->semaphore)==0){
        std::cout<<"Destroyed semaphore\n";
    }
    else{
        std::cout<<"Failed to destroy semaphore\n";
    }
}

void Runner::sigint_handler(int signum){
    if(sem_destroy(globalSemaphore)==0){
        std::cout<<"Destroyed semaphore\n";
    }
    else{
        std::cout<<"Failed to destroy semaphore\n";
    }
    std::exit(0);
}