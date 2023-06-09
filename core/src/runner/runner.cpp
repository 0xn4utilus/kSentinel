#include<runner.hpp>
#include<fcntl.h>
#include<iostream>
#include<signal.h>
#include<errno.h>
#include<models.h>
#include<networking.hpp>
#include<device.hpp>
#include<logger.hpp>

Runner:: Runner(){
    log = new Logger;
}

bool Runner::is_ksentinel_running(){
    log->info("Starting kSentinel");
    sem_t* semaphore = sem_open(KS_SEMAPHORE,O_CREAT|O_EXCL,0644,1);
    if(semaphore==SEM_FAILED){
        if(errno==EEXIST){
            log->fatal("Another instance of kSentinel is already running");
        }
        else{
            log->fatal("ks-semaphore creation failed");
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
    HttpRequest httpRequest("http://127.0.0.1:8000");
    std::unordered_map<std::string,std::string>umap;
    umap["name"] = "shady";
    umap["age"] = "18";
    std::unique_ptr<http_response>response = httpRequest.http_post(umap);
    std::cout<<response->response<<std::endl;
    while(1){
    }
}

Runner::~Runner(){
    if(sem_unlink(KS_SEMAPHORE)!=0){
        log->fatal("Failed to unlink ks-semaphore");
    }
    delete log;
}

void Runner::term_sighandler(int signum){
    if(sem_unlink(KS_SEMAPHORE)!=0){
        ks_fatal("Failed to unlink ks-semaphore");
    }
    ks_fatal("Shutting down kSentinel..");
}

void Runner::ks_fatal(std::string message){
    std::cerr<<message<<std::endl;
    std::exit(1);
}