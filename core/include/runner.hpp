#ifndef RUNNER_H
#define RUNNER_H
#include<sys/stat.h>
#include<semaphore.h>

#define KS_SEMAPHORE "ks-semaphore"
class Runner{
    sem_t* semaphore;
    public:
    bool is_ksentinel_running();
    void run();
    static void sigint_handler(int);
    ~Runner();
};
#endif