#include<runner.hpp>
#include<fcntl.h>
#include<iostream>
#include<signal.h>
#include<errno.h>
#include<models.h>
#include<networking.hpp>
#include<device.hpp>

bool Runner::is_ksentinel_running(){
    sem_t* semaphore = sem_open(KS_SEMAPHORE,O_CREAT|O_EXCL,0644,1);
    if(semaphore==SEM_FAILED){
        if(errno==EEXIST){
            ks_fatal("Error! Another instance of kSentinel is already running");
        }
        else{
            ks_fatal("ks-semaphore creation failed");
        }
    }
    else{
        this->semaphore = semaphore;
        std::cout<<"Starting kSentinel...\n";
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
        ks_fatal("Failed to unlink ks-semaphore");
    }
}

void Runner::term_sighandler(int signum){
    if(sem_unlink(KS_SEMAPHORE)!=0){
        ks_fatal("Failed to unlink ks-semaphore");
    }
    ks_fatal("Shutting down kSentinel..");
}

bool Runner::ks_fatal(std::string message){
    std::cerr<<message<<std::endl;
    std::exit(1);
}