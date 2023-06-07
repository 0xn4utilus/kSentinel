#ifndef UTILS_H
#define UTILS_H
#include<string>
#include<yaml.hpp>
#include<envvars.h>
#include<cstring>
#include<iostream>
#include<fstream>
bool check_status();

class FileUtils{
    std::string filename;
    public:
    FileUtils(std::string filename){
        this->filename = filename.c_str();
    }
    std::string read_file(){
        std::string data = "";
        std::ifstream ifile(this->filename);
        std::stringstream buffer;
        if(ifile){
            buffer<<ifile.rdbuf();
            data = buffer.str();
        }
        else{
            std::cerr<<"Failed to open "+this->filename<<std::endl;
        }
        return data;
    }
};

template<class T>
class YamlUtils:public FileUtils{
    public:
    T read_config_var(std::string key){
        const char* configDir = std::getenv(KS_CONFIG_DIR);
        if(!configDir){
            std::cerr<<"Environment variable KS_CONFIG_DIR not found"<<std::endl;
            std::exit(1);
        }
        std::string configFile = std::string(configDir)+"/config.yml";
        Yaml::Node root;
        Yaml::Parse(root,configFile.c_str());
        return root[key].As<T>();
    }
};
#endif