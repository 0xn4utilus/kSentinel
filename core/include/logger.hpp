#ifndef LOGGER_H
#define LOGGER_H
#include<string>

class Logger{
    public:
    Logger();
    void info(std::string);
    void verbose(std::string);
    void warning(std::string);
    void error(std::string);
    void fatal(std::string);
    void debug(std::string);
};
#endif