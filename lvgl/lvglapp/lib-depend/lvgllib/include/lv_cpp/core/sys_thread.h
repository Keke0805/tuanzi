#ifndef SYS_THREAD_H
#define SYS_THREAD_H

#include "lv_cpp/include/lvcpp_sysconfig.h"

#ifdef LVGL_DRIVER
#include  <pthread.h>
#include  <signal.h>
#include  <stdio.h>
#include  <unistd.h>
#include  <iostream>
#include  <mutex>
#include  <semaphore.h>
#include  <condition_variable>

using namespace std;

class SYS_Thread
{
public:
    SYS_Thread();

    virtual ~SYS_Thread();
    virtual void run() = 0;

    pthread_t getTid();
    bool isAlive();

    int thread_start(void);
    int thread_join(void);
    int thread_quit(void);

    void thread_lock(void);
    void thread_unlock(void);
private:
    pthread_t m_tid;
    bool m_isAlive;
    pthread_mutex_t mutex_lock;

    static void* start_func(void* arg);
};

class mThread
{
public:
    mThread();

    virtual ~mThread();

    pthread_t getTid();
    bool isAlive();

    int thread_start(void *(* func)(void *), void *arg);
    int thread_join(void);
    int thread_quit(void);

    void thread_lock(void);
    void thread_unlock(void);

private:
    pthread_t m_tid;
    bool m_isAlive;
    pthread_mutex_t mutex_lock;
};

class semaphore
{
public:

    semaphore(int value = 1) :count(value) {}

    void wait()
    {
        unique_lock<mutex> lck(mtk);
        if (--count < 0)
            cv.wait(lck);
    }

    void post()
    {
        unique_lock<mutex> lck(mtk);
        if (++count <= 0)
            cv.notify_one();
    }

private:
    int count;
    mutex mtk;
    condition_variable cv;
};


class lvcpp_sem
{
public:
    lvcpp_sem(int value = 1);
    ~lvcpp_sem();

    int wait(void);
    int post(void);
    int trywait(void);
    int close(void);
    int getvalue(int * sval);
    int unlink(const char * name);
    sem_t* open(const char * name, int oflag, mode_t mode, unsigned int value);
    sem_t* get_sem(void);

private:
    sem_t sem;
};

#endif

#endif // SYS_THREAD_H
