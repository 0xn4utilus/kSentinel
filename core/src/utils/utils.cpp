#include <utils.h>
#include<curl/curl.h>
#include<iostream>
#include<networking.hpp>

bool check_status(){
    HttpRequest httpRequest("http://localhost:8080");
    std::unique_ptr<http_response>response = httpRequest.http_get();
    if(response->success){
        std::cout<<response->response<<std::endl;
        return true;
    }
    else{
        std::cout<<"kSentinel backend is down"<<std::endl;
    }
    return false;
}