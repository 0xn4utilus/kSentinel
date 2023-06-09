#include<logger.hpp>
#include<plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include<plog/Appenders/ColorConsoleAppender.h>
#include<plog/Formatters/TxtFormatter.h>
#include<envvars.h>

Logger::Logger(){
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    std::string log_file = std::string(std::getenv(KS_CONFIG_DIR))+"/kSentinel_logs.txt";
    plog::init(plog::verbose,(plog::util::nchar*)log_file.c_str()).addAppender(&consoleAppender);
}
void Logger::info(std::string message){
    PLOGI<<message;
}
void Logger::debug(std::string message){
    PLOGD<<message;
}
void Logger::error(std::string message){
    PLOGE<<message;
}
void Logger::fatal(std::string message){
    PLOGF<<message;
    std::exit(1);
}
void Logger::verbose(std::string message){
    PLOGV<<message;
}
void Logger::warning(std::string message){
    PLOGW<<message;
}