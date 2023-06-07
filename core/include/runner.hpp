#ifndef RUNNER_H
#define RUNNER_H
#include<sys/stat.h>
#include<semaphore.h>
#include<string>

#define KS_SEMAPHORE "ks-semaphore"
class Runner{
    sem_t* semaphore;
    public:
    bool is_ksentinel_running();
    void run();
    static void term_sighandler(int);
    static bool ks_fatal(std::string message);
    ~Runner();
};
#endif