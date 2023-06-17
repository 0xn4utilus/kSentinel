#ifndef LOGGER_H
#define LOGGER_H
#include<string>

class Logger{
    public:
    static void info(std::string);
    static void verbose(std::string);
    static void warning(std::string);
    static void error(std::string);
    static void fatal(std::string);
    static void debug(std::string);
};
#endif