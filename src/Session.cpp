#include "Common.h"
#include "Session.h"
#include "SessionManager.h"
#include "WorkerThreads.h"
#include "Message.h"

Session::Session(std::string& uuid, boost::asio::io_service& ios)
    : _ioService(ios)
    , _socket(ios)
    , _timer(ios, boost::posix_time::seconds(1))
    , _uuid(uuid)
{
}

Session::~Session()
{
    std::cout << "Session: Destructors: " << _uuid << "\n";
}

// protected methods;
void Session::doTicker(unsigned int us)
{
    _timer.expires_at(_timer.expires_at() + boost::posix_time::microseconds(us));
    _timer.async_wait(boost::bind(&Session::onTickerDone,
        shared_from_this(),
        boost::asio::placeholders::error));
}

void Session::onTickerDone(const boost::system::error_code& error)
{
    if (!error) {
        doTicker(100000);
    } else {
//        onError(error);
    }
}

void Session::write(const void *buf, size_t size, Callback cb)
{
    _socket.async_write_some(boost::asio::buffer(buf, size),
        boost::bind(&Session::onWriteDone, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, cb));
}

void Session::onWriteDone(const boost::system::error_code& error, size_t bytes_transferred, Callback cb)
{
    if (!error) {
//        doRead(_buf, 128, cb);
    } else {
 //       onError(error);
    }
}

void Session::doRead(void *buf, size_t size, Callback cb)
{
 //   boost::asio::async_read_some(_socket, boost::asio::buffer(buf, size),
 //       boost::bind(&Session::onReadDone, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, cb));

    _socket.async_read_some(boost::asio::buffer(buf, size),
        boost::bind(&Session::onReadDone, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, cb));
}

void Session::onReadDone(const boost::system::error_code& error, size_t  bytes_transferred, Callback cb)
{
    if (!error) {
        onSuccess(cb);
    } else {
        onError(error, cb);
    }
}

void Session::stopConnection()
{
    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    _socket.close();
    theSessionManager().destroySession(_uuid);
}

void Session::startConnection(const std::string& ip, const std::string& port, Callback cb)
{
    tcp::resolver resolver(_socket.io_service());
    tcp::resolver::query query(tcp::v4(), ip, port);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    _socket.async_connect(*iterator, boost::bind(&Session::onConnectDone, this, boost::asio::placeholders::error, cb));  
}

void Session::onConnectDone(const boost::system::error_code& error, Callback cb)
{
    if (!error) {
    	_response.hdr.flags = 0;
    	_response.hdr.extra = sizeof("连接成功");
    	strcpy(_response.content, "连接成功");
        onSuccess(cb);
    } else {
        onError(error, cb);
    }
}

void Session::submitRequest(uint32_t cmd, void* buf, size_t size, Callback cb)
{
    _request.hdr.cmd = cmd;
    _request.hdr.extra = size;
    memcpy(_request.content, buf, size);
    doSubmit(cb);
}

void Session::doSubmit(Callback cb)
{
    boost::asio::async_write(_socket, boost::asio::buffer((char*)&_request, sizeof(RequestHeader)+_request.hdr.extra),
        boost::bind(&Session::doFetchHeader, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, cb));
}

void Session::doFetchHeader(const boost::system::error_code& error, size_t  bytes_transferred, Callback cb)
{
    if (!error) {
        boost::asio::async_read(_socket, boost::asio::buffer((char*)&_response.hdr, sizeof(ResponseHeader)),
            boost::bind(&Session::doFetchBody, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, cb));
    } else {
        onError(error, cb);
    }
}

void Session::doFetchBody(const boost::system::error_code& error, size_t  bytes_transferred, Callback cb)
{
    if (!error) {
        boost::asio::async_read(_socket, boost::asio::buffer((char*)&_response.content, _response.hdr.extra),
            boost::bind(&Session::doFetchDone, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, cb));
    } else {
        onError(error, cb);
    }
}

void Session::doFetchDone(const boost::system::error_code& error, size_t bytes_transferred, Callback cb)
{
    if (!error) {
        onSuccess(cb);
    } else {
        onError(error, cb);
    }
}

void Session::onSuccess(Callback cb)
{
	int msg_size = sizeof(Message) + _response.hdr.extra;
	Message *msg = (Message*)malloc(msg_size);
	msg->flag = _response.hdr.flags;
	msg->size = _response.hdr.extra;
    memcpy(msg->content, _response.content, _response.hdr.extra);
    theWorkerThreads().deliverJob(WorkerThreads::Job(msg, sizeof(msg_size), cb));
}   

void Session::onError(const boost::system::error_code& error, Callback cb)
{
    std::cout << "Session: error: " << error.message() << std::endl;

    int msg_size = sizeof(Message) + strlen(error.message().c_str());
    Message *msg = (Message*)malloc(msg_size);
    msg->flag = NE_ERROR;
    msg->size = strlen(error.message().c_str());
    strcpy(msg->content, error.message().c_str());
    theWorkerThreads().deliverJob(WorkerThreads::Job(msg, sizeof(msg_size), cb));

    theSessionManager().destroySession(_uuid);
}
