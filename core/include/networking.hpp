#ifndef NETWORKING_H
#define NETWORKING_H
#include "models.h"
#include<string>
#include<memory>
#include<unordered_map>

class HttpRequest{
    std::string url;
    static size_t write_callback(void* contents, size_t size,size_t nmemb,std::string* response);
    std::string post_map_to_str(std::unordered_map<std::string,std::string>data);
    public:
    HttpRequest(const std::string u):url(u){};
    std::unique_ptr<http_response> http_get();
    std::unique_ptr<http_response>http_post(std::unordered_map<std::string,std::string>post_data);
};
#endif