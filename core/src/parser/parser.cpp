#include<argparse.hpp>
#include<parser.h>
#include<utils.hpp>
#include<yaml.hpp>
#include<envvars.h>
#include<runner.hpp>
#include<auth.hpp>
#include<utils.hpp>

void run();
void setup_parser(int argc, char** argv){
    argparse::ArgumentParser program("kSentinel");
    program.add_argument("-s","--server").help("URL of the kSentinel backend server");
    program.add_argument("--status").help("Check status of the kSentinel backend").default_value(false).implicit_value(true);
    program.add_argument("--config").help("Read the configuration file").default_value(false).implicit_value(true);
    program.add_argument("--run").help("Run kSentinel").default_value(false).implicit_value(true);
    program.add_argument("--login").help("Login to kSentinel server").default_value(false).implicit_value(true);

    try{
        program.parse_args(argc,argv);
    }
    catch(const std::runtime_error& err){
        std::cerr<<err.what()<<std::endl;
        std::cerr<<program;
        std::exit(1);
    }
    if(program["--status"]==true){
        std::cout<<"Checking status of backend..."<<std::endl;
        check_status();
    }
    else if(program["--config"]==true){
        const char* configDir = std::getenv(KS_CONFIG_DIR);
        if(!configDir){
            std::cerr<<"Environment variable KS_CONFIG_DIR not found"<<std::endl;
        }
        else{
            std::string configFile = std::string(configDir)+"/config.yml";
            FileUtils* fileUtils = new FileUtils(configFile);
            std::string data = fileUtils->read_file();
            if(data.length()>0){
                std::cout<<data<<std::endl;
            }
            delete fileUtils;
        }
    }
    else if(program["--login"]==true){
        Auth* auth = new Auth;
        auth->login();
        delete auth;
    }
    else if(program["--run"]==true){
        Runner* runner = new Runner();
        OtherUtils::check_required_env_vars();
        if(!runner->is_ksentinel_running()){
            runner->run();
        }
        delete runner;
    }
}

void run(){

}