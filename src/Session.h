#ifndef _SESSION_H_
#define _SESSION_H_

using boost::asio::ip::tcp;

#include "Def.h"

class Session : public boost::enable_shared_from_this<Session>
              , public boost::noncopyable
{
public:
    typedef boost::shared_ptr<Session> SmartPtr;

    /// @param buf 返回结果空间
    /// @param size 返回结果大小
    typedef boost::function<void (void* buf, size_t size)> Callback;

    static SmartPtr create(std::string& uuid, boost::asio::io_service& ios)
    {
        return Session::SmartPtr(new Session(uuid, ios));
    }

    std::string& uuid() const
    {
        return const_cast<std::string&>(_uuid);
    }

    /**
     * 连接指定地址
     * @param [in] ip
     * @param [in] port
     * @param [in] cb 
     */
    void startConnection(const std::string& ip, const std::string& port, Callback cb);
    void stopConnection();

public:
    /**
     * 提交指定命令
     * @param [in] cmd 
     * @param [in] buf
     * @param [in] size
     * @param [in] cb
     */
    void submitRequest(uint32_t cmd, void* buf, size_t size, Callback cb);

public:
    void doTicker(unsigned int us);
    void write(const void *buf, size_t size, Callback cb);
    void doRead(void *buf, size_t size, Callback cb);

    Session(std::string& uuid, boost::asio::io_service& ios);
    ~Session();

private:
    void doSubmit(Callback cb);
    void doFetchHeader(const boost::system::error_code& error, size_t  bytes_transferred, Callback cb);
    void doFetchBody(const boost::system::error_code& error, size_t  bytes_transferred, Callback cb);
    void doFetchDone(const boost::system::error_code& error, size_t bytes_transferred, Callback cb);

private:
    void onWriteDone(const boost::system::error_code& error, size_t bytes_transferred, Callback cb);
    void onReadDone(const boost::system::error_code& error, size_t bytes_transferred, Callback cb);
    void onConnectDone(const boost::system::error_code& error, Callback cb);
    void onTickerDone(const boost::system::error_code& error);

private:
    void onError(const boost::system::error_code& error, Callback cb);
    void onSuccess(Callback cb);

private:
    boost::asio::io_service& _ioService;
    tcp::socket _socket;  
    boost::asio::deadline_timer _timer;
    std::string _uuid;

private:
    Request _request;
    Response _response;
};

#endif /* _SESSION_H_ */
