#include<argparse.hpp>
#include<parser.h>
#include<utils.h>

void setup_parser(int argc, char** argv){
    argparse::ArgumentParser program("kSentinel");
    program.add_argument("-s","--server").help("URL of the kSentinel backend server");
    program.add_argument("--status").help("Check status of the kSentinel backend").default_value(false).implicit_value(true);
    program.add_argument("--config").help("Read the configuration file").default_value(false).implicit_value(true);
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
        std::cout<<"Reading config file"<<std::endl;
    }
}