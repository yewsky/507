#ifndef _IPCAMCLIENT_H_ 
#define _IPCAMCLIENT_H_

#include "Session.h"
#include "Handle.h"

class IpcamClient : public boost::enable_shared_from_this<IpcamClient>
{
public:
    IpcamClient(void);
    ~IpcamClient(void);

    typedef boost::shared_ptr<IpcamClient> SmartPtr;
    typedef boost::function<void (int, void*)> CallbackFun;

    int login(std::string addr, int port, std::string user, std::string pswd, CallbackFun fun, void* context);
    void logout();
    void videoStreamStart();
    void videoStreamStop();

private:
    void onConnectDone(void *buf, size_t size, CallbackFun fun, void* context);
    void doLogin(void *buf, size_t size, CallbackFun fun, void* context);
    void doLoginResult(void *buf, size_t size, CallbackFun fun, void* context);

private:
    void defaultFun(void *buf, size_t size, CallbackFun fun, void* context);

private:
    std::string _username;
    std::string _userpswd;
    char _buf[MAX_CONTENT_LEN];

private:
    int _lastErrno; 

private:
    Session::SmartPtr _sesson;
    Handle::Key _key;

private:
    boost::interprocess::interprocess_mutex  	_mutex;
    boost::interprocess::interprocess_condition  _condition;
};

#endif /* _IPCAMCLIENT_H_ */
