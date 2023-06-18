#include<auth.hpp>
#include<termios.h>
#include<unistd.h>
#include<iostream>
#include<networking.hpp>
#include<utils.hpp>
#include<json/json.hpp>
#include<logger.hpp>

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
            Logger::verbose("Loggin successful");
        }
        else{
            Logger::error(message);
        }
    }
}

bool Auth::validate_auth_token(std::string token,std::string config_file){
    YamlUtils<std::string> yaml_utils;    
    std::string kscore_env = yaml_utils.read_config_var("KS_AUTH_API");
    if(kscore_env.length()==0){
        Logger::error("Error! Failed to read KS_AUTH_API from the configuration file");
        return false;
    }
    std::string url = kscore_env+"/validate/"+token;
    HttpRequest http_request(url);
    std::unique_ptr<http_response>response = http_request.http_get();
    if(response->success==false || response->status_code!=200){
        Logger::error(response->response);
        return false;
    }
    return true;
}

bool Auth::is_logged_in(){
    const char* config_dir = std::getenv("KS_CONFIG_DIR");
    if(!config_dir){
        Logger::error("Error! Environment variable KS_CONFIG_DIR not found");
        return false;
    }
    std::string config_dir_str = std::string(config_dir);
    std::string tokenFile = config_dir_str+"/.kst";
    std::ifstream ifile(tokenFile,std::ios::in);
    std::stringstream streambuf;
    streambuf<<ifile.rdbuf();
    ifile.close();
    return this->validate_auth_token(streambuf.str(),config_dir_str+"/config.yml");
}