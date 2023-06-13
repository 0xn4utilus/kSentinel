#include<auth.hpp>
#include<termios.h>
#include<unistd.h>
#include<iostream>
#include<networking.hpp>
#include<utils.hpp>
#include<json/json.hpp>

using json = nlohmann::json;

Auth::Auth(){
    YamlUtils<std::string>*yaml_utils = new YamlUtils<std::string>;
    this->login_url = yaml_utils->read_config_var("KS_LOGIN_URL");
    this->logout_url = yaml_utils->read_config_var("KS_LOGOUT_URL");
    if(this->login_url.length()==0){
        std::cerr<<"Error! KS_LOGIN_URL not found in the configuration file"<<std::endl;
        std::exit(1);
    }
    if(this->logout_url.length()==0){
        std::cerr<<"Error! KS_LOGOUT_URL not found in the configuration file"<<std::endl;
        std::exit(1);
    }
    delete yaml_utils;
}
void Auth::login(){
    termios oldt;
    std::string username;
    std::string password;
    std::cout<<"Username: ";
    getline(std::cin,username);
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::cout<<"Password (will not be echoed): ";
    std::getline(std::cin, password);

    std::unordered_map<std::string,std::string>form_data;
    form_data["username"] = username;
    form_data["password"] = password;
    HttpRequest* httpRequest = new HttpRequest(this->login_url);
    std::unique_ptr<http_response>response =  httpRequest->http_post(form_data);
    puts("");
    if(response->success==false){
        std::cerr<<response->response<<std::endl;
    }
    else{
        json data = json::parse(response->response);
        std::string message = data["Message"];
        if(message=="Login successful"){
            std::string token = data["Token"];
            std::string tokenFile = std::string(std::getenv("KS_CONFIG_DIR"))+"/.kst";
            std::ofstream ofile(tokenFile,std::ios::out);
            ofile.write(token.c_str(),token.length());
            ofile.close();
            std::cout<<"Login successful"<<std::endl;
        }
        else{
            std::cerr<<message<<std::endl;
        }
    }
}