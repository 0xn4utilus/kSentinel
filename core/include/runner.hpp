#ifndef RUNNER_H
#define RUNNER_H
#include<sys/stat.h>
#include<semaphore.h>
#include<string>
#include<logger.hpp>
#include<memory>
#include<device.hpp>

#define KS_SEMAPHORE "ks-semaphore"

class Runner{
    std::unique_ptr<DeviceUtils>device_utils;
    sem_t* semaphore;
    public:
    bool is_ksentinel_running();
    void run();
    Runner();
    static void term_sighandler(int);
    static void ks_fatal(std::string message);
    void ks_main();
    ~Runner();
};
#endif