#ifndef _WORKERTHREADS_H_
#define _WORKERTHREADS_H_

#include "Session.h"

class WorkerThreads : public boost::noncopyable
{
public:
    struct Job {
        Job(void *buf, size_t size, Session::Callback cb)
            : _buf(buf)
            , _size(size)
            , _cb(cb)
        { }
        void *_buf;
        size_t _size;
        Session::Callback _cb;
    };

public:
    WorkerThreads(void);
    ~WorkerThreads(void);

    enum {
          WT_NULL
        , WT_RUNNING
        , WT_STOPPED
    };

public:
    void init();
    void cleanup();

    void deliverJob(Job job);

private:
    void schedulingWorker();
    void ioWoker();

private:
    boost::interprocess::interprocess_semaphore _sem;
    int _state;

    boost::thread _toeThread1;
    boost::thread _toeThread2;

    boost::thread _ioThread;

private:
    std::queue<Job> _jobs;
    boost::asio::io_service::work *_ioSerivceWork;
};

WorkerThreads& theWorkerThreads();

#endif /* _WORKERTHREADS_H_ */
