#include <utils.hpp>
#include<curl/curl.h>
#include<iostream>
#include<networking.hpp>
#include<yaml.hpp>
#include<ctime>

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

int OtherUtils::generate_random_num(int lower, int upper){
    int range = upper-lower+1;
    int num = std::rand()%range+lower;
    return num;
}
std::string OtherUtils::generate_rand_string(int len, int type){
    std::srand(std::time(nullptr));
    std::string rand_str = "";
    for(int i=0;i<len;i++){
        switch(type){
            case TYPE_ALPHAMIXED:
                rand_str += MIXED_ALPHABETS[generate_random_num(0,51)];
                break;
            case TYPE_FULLMIXED:
                rand_str += MIXED_CHARS[generate_random_num(0,61)];
                break;
            case TYPE_NUMBER:
                rand_str += NUMS[generate_random_num(0,9)];
                break;
            case TYPE_SMALLCASE:
                rand_str += SMALLCASE_ALPHABETS[generate_random_num(0,25)];
                break;
            case TYPE_UPPERCASE:
                rand_str += UPPERCASE_ALPHABETS[generate_random_num(0,25)];
                break;
            default:
                rand_str += MIXED_CHARS[generate_random_num(0,61)];
        }
    }
    return rand_str;
}