#include<models.h>
#include<networking.hpp>
#include<curl/curl.h>
#include<iostream>

size_t HttpRequest::write_callback(void* contents, size_t size,size_t nmemb,std::string* response){
    size_t total_size = nmemb*size;
    response->append((char*)contents,total_size);
    return total_size;
}

std::unique_ptr<http_response> HttpRequest::http_get(){
    std::unique_ptr<http_response>response = std::make_unique<http_response>();
    CURL* curl = curl_easy_init();
    if(!curl){
        response->response = "Failed to initialize libcurl";
        response->success = false;
    }
    else{
        curl_easy_setopt(curl,CURLOPT_URL,this->url.c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,this->write_callback);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response->response);
        CURLcode res = curl_easy_perform(curl);
        if(res!=CURLE_OK){
            response->response = "Failed to GET "+this->url;
            response->success = false;
        }
        else{
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&response->status_code);
            response->success = true;
        }
    }
    curl_easy_cleanup(curl);
    return response;
}
