#ifndef UTILS_H
#define UTILS_H
#include<string>
#include<yaml.hpp>
#include<envvars.h>
#include<cstring>
#include<logger.hpp>
#include<iostream>
#include<fstream>

#define SMALLCASE_ALPHABETS "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE_ALPHABETS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUMS "0123456789"
#define MIXED_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" 
#define MIXED_ALPHABETS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

#define TYPE_SMALLCASE 0x1
#define TYPE_UPPERCASE 0x2
#define TYPE_ALPHAMIXED 0x3
#define TYPE_FULLMIXED 0x4
#define TYPE_NUMBER 0x5

bool check_status();

class FileUtils{
    std::string filename;
    public:
    FileUtils(){

    }
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
    static std::string get_config_dir(){
        const char* config_dir = std::getenv("KS_CONFIG_DIR");
        if(!config_dir){
            Logger::fatal("Error! Failed to read the KS_CONFIG_DIR environment variable");
        }
        return std::string(config_dir);
    }
};

template<class T>
class YamlUtils:public FileUtils{
    public:
    YamlUtils(){}
    T read_config_var(std::string key){
        const char* configDir = std::getenv(KS_CONFIG_DIR);
        if(!configDir){
            std::cerr<<"Environment variable KS_CONFIG_DIR not found"<<std::endl;
            std::exit(1);
        }
        std::string configFile = std::string(configDir)+"/config.yml";
        Yaml::Node root;
        try{
            Yaml::Parse(root,configFile.c_str());
        }
        catch(Yaml::ParsingException){
            std::cerr<<"Error! Syntax error in "+configFile;
            std::exit(1);
        }
        return root[key].As<T>();
    }
};

class OtherUtils{
    public:
    static void check_required_env_vars();
    static std::string generate_rand_string(int len, int type);
    static int generate_random_num(int lower,int upper);
    static void disable_input_hiding();
    static void enable_input_hiding();
    static std::string pad_string(std::string,int,char);
};
#endif