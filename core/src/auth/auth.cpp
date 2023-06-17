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
    std::string ks_auth_api = yaml_utils->read_config_var("KS_AUTH_API");
    if(ks_auth_api.length()==0){
        std::cerr<<"Error! KS_AUTH_API not found in the configuration file"<<std::endl;
        std::exit(1);
    }
    this->login_url = ks_auth_api+"/login";
    this->logout_url = ks_auth_api+"/logout";
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

bool Auth::is_logged_in(){
    // Read the token from $KS_CONFIG_DIR/.kst
    // Validate the token by sending a post request to /api/auth/validate_token
}