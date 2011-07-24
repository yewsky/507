#include "Common.h"
#include "WorkerThreads.h"
#include "SessionManager.h"

WorkerThreads::WorkerThreads(void)
    : _sem(0)
    , _state(WT_STOPPED)
{

}

WorkerThreads::~WorkerThreads(void)
{
}

void WorkerThreads::init()
{
    _state = WT_RUNNING;
    _toeThread1 = boost::thread(boost::bind(&WorkerThreads::schedulingWorker, this));
    _toeThread2 = boost::thread(boost::bind(&WorkerThreads::schedulingWorker, this));

    _ioSerivceWork = new boost::asio::io_service::work(theSessionManager()._ios);
    _ioThread = boost::thread(boost::bind(&WorkerThreads::ioWoker, this));
}

void WorkerThreads::cleanup()
{
    _state = WT_STOPPED;
    _sem.post();
    _sem.post();
    _toeThread1.join();
    _toeThread2.join();
    if (NULL != _ioSerivceWork) {
        delete _ioSerivceWork;
    }
}

void WorkerThreads::schedulingWorker()
{
    for (; ;) {
        _sem.wait();
        if (_state != WT_RUNNING) {
            break;
        }
        _jobs.front()._cb(_jobs.front()._buf, _jobs.front()._size);
        _jobs.pop();
    }
}

void WorkerThreads::deliverJob(Job job)
{
    _jobs.push(job);
    _sem.post();
}

void WorkerThreads::ioWoker()
{
    theSessionManager()._ios.run();
}

WorkerThreads& theWorkerThreads()
{
    static WorkerThreads _instance;
    return _instance;
}
