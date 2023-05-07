#include "sys_thread.h"

#ifdef QTSIM_PLATFORM
SYS_Thread::SYS_Thread()
{
    pthread_mutex_init(&mutex_lock,NULL);
}

SYS_Thread::~SYS_Thread()
{
    cout << "~SYS_Thread tid="<< m_tid << endl;
    if (m_isAlive)
    {
        cout << "Kill the thread tid= "<< m_tid << endl;
        pthread_kill(m_tid, 0);
    }
    pthread_mutex_destroy(&mutex_lock);
}

void* SYS_Thread::start_func(void* arg)
{
   SYS_Thread* ptr = (SYS_Thread*) arg;
   ptr->run();
   return NULL;
}

int SYS_Thread::thread_start()
{
    cout << "Start a new thread" << endl;
    if (pthread_create(&m_tid, NULL, start_func, (void*)this) != 0)
    {
        cout << "Start a new thread failed!" << endl;
        return -1;
    }

    cout << "Start a new thread success! tid="<< m_tid << endl;
    m_isAlive = true;
    return 0;
}

int SYS_Thread::thread_join()
{
    int ret = -1;
    cout << "Join the thread tid=" << m_tid <<endl;
    ret = pthread_join(m_tid, NULL);

    if (ret != 0)
    {
        cout << "Join the thread fail tid=" << m_tid <<endl;
    }
    else
    {
        cout << "Join the thread success tid=" << m_tid <<endl;
    }

    return ret;
}

int SYS_Thread::thread_quit()
{
    cout << "Quit the thread tid=" << m_tid <<endl;
    m_isAlive = false;
    return 0;
}

pthread_t SYS_Thread::getTid()
{
    return m_tid;
}

bool SYS_Thread::isAlive()
{
    return m_isAlive;
}

void SYS_Thread::thread_lock(void)
{
    pthread_mutex_lock(&mutex_lock);
}

void SYS_Thread::thread_unlock(void)
{
    pthread_mutex_unlock(&mutex_lock);
}


mThread::mThread()
{
    pthread_mutex_init(&mutex_lock,NULL);
}

mThread::~mThread()
{
    cout << "~SYS_Thread tid="<< m_tid << endl;
    if (m_isAlive)
    {
        cout << "Kill the thread tid= "<< m_tid << endl;
        pthread_kill(m_tid, 0);
    }
    pthread_mutex_destroy(&mutex_lock);
}


int mThread::thread_start(void *(* func)(void *), void *arg)
{
    cout << "Start a new thread" << endl;
    if (pthread_create(&m_tid, NULL, func, arg) != 0)
    {
        cout << "Start a new thread failed!" << endl;
        return -1;
    }

    cout << "Start a new thread success! tid="<< m_tid << endl;
    m_isAlive = true;
    return 0;
}

int mThread::thread_join()
{
    int ret = -1;
    cout << "Join the thread tid=" << m_tid <<endl;
    ret = pthread_join(m_tid, NULL);

    if (ret != 0)
    {
        cout << "Join the thread fail tid=" << m_tid <<endl;
    }
    else
    {
        cout << "Join the thread success tid=" << m_tid <<endl;
    }

    return ret;
}

int mThread::thread_quit()
{
    cout << "Quit the thread tid=" << m_tid <<endl;
    m_isAlive = false;
    return 0;
}

pthread_t mThread::getTid()
{
    return m_tid;
}

bool mThread::isAlive()
{
    return m_isAlive;
}

void mThread::thread_lock(void)
{
    pthread_mutex_lock(&mutex_lock);
}

void mThread::thread_unlock(void)
{
    pthread_mutex_unlock(&mutex_lock);
}

lvcpp_sem::lvcpp_sem(int value)
{
    sem_init(&sem,0,value);
}

lvcpp_sem::~lvcpp_sem()
{
    sem_destroy(&sem);
}

int lvcpp_sem::wait()
{
    return sem_wait(&sem);
}

int lvcpp_sem::post()
{
    return sem_post(&sem);
}

int lvcpp_sem::trywait()
{
    return sem_trywait(&sem);
}


int lvcpp_sem::close()
{
    return sem_close(&sem);
}

int lvcpp_sem::getvalue(int * sval)
{
    return sem_getvalue(&sem,sval);
}

sem_t* lvcpp_sem::open(const char * name, int oflag, mode_t mode, unsigned int value)
{
    return sem_open(name,oflag,mode,value);
}

int lvcpp_sem::unlink(const char * name)
{
    return sem_unlink(name);
}

sem_t* lvcpp_sem::get_sem(void)
{
    return &sem;
}

#endif
