#ifndef MODELS_H
#define MODELS_H
#include<string>

struct http_response{
    long status_code;
    std::string response;
    bool success;
};
#endif