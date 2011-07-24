#include "Common.h"
#include "IpcamClient.h"

#include "md5/md5.h"
#include "xml/CustomWriter.h"

#include "SessionManager.h"
#include "Session.h"
#include "HandleManager.h"

#include "Message.h"
#include "Cmd.h"

IpcamClient::IpcamClient(void)
{
	//
}

IpcamClient::~IpcamClient(void)
{
    std::cout<< "IpcamClient Destructors.\n";
}

void IpcamClient::defaultFun(void *buf, size_t size, CallbackFun fun, void* context)
{
    Message *msg = (Message*)buf;
    if (msg->flag != 0) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_buffer(msg->content, msg->size);
        if (!result) {
        	PRINTF("load_buffer failed\n");
        }
        std::string id = doc.child("message").child("id").first_child().value();
        std::string text = doc.child("message").child("text").first_child().value();
        PRINTF("text = %s\n", text.c_str());
    }

    if (fun != NULL) {
        fun(msg->flag, context);
    } else {
        _condition.notify_one();
    }
}

int IpcamClient::login(std::string addr, int port, std::string user, std::string pswd, CallbackFun fun, void* context)
{
    using boost::interprocess::interprocess_mutex;
    using boost::interprocess::defer_lock_type;
    using boost::interprocess::scoped_lock;
    scoped_lock<interprocess_mutex> lock(_mutex, defer_lock_type());

    if (fun == NULL) {
        lock.lock();
    }
    
    _username = user;
    _userpswd = pswd;

    _sesson = theSessionManager().createSession();
    _sesson->startConnection(addr, "6005", boost::bind(&IpcamClient::onConnectDone, shared_from_this(), _1, _2, fun, context));
     _key = theHandleManager().createHandle(shared_from_this());

    if (fun == NULL) {
        _condition.wait(lock);
        lock.unlock();
    }

    return _key;
}

void IpcamClient::onConnectDone(void *buf, size_t size, CallbackFun fun, void* context)
{
    Message *msg = (Message*)buf;
    std::cout<<msg->content<<std::endl;
    if (msg->flag == 0) {
        _sesson->submitRequest(CMD_REQ_SECODE, NULL, 0, boost::bind(&IpcamClient::doLogin, shared_from_this(), _1, _2, fun, context));
    } else {
    	defaultFun(buf, size, fun, context);
		_key = 0;
		if (msg->flag == NE_ERROR) {
			theHandleManager().destroyHandle(_key);
		}
    }
}

void IpcamClient::doLogin(void *buf, size_t size, CallbackFun fun, void* context)
{
	Message *msg = (Message*)buf;
	PRINTF("%s\n", msg->content);
	if (msg->flag == 0) {

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_buffer(msg->content, msg->size);
		if (!result) {
			PRINTF("load_buffer failed\n");
			defaultFun(buf, size, fun, context);
			return ;
		}
		std::string secode = doc.child("message").child("secode").first_child().value();
		if (secode != "") {
			PRINTF("the security code is [%s]\n", secode.c_str());
		} else {
			PRINTF("fetch security code failed\n");
		}

		unsigned char md[16];
		std::string hash_buf = _userpswd + secode;
		md5Hash(hash_buf.c_str(), hash_buf.length(), md);
		char str[36] = {0};
		md5ToString(md, str);
		doc.reset();

		doc.append_child(pugi::node_declaration).set_name("xml version=\"1.0\" encoding=\"utf-8\"");
		pugi::xml_node node = doc.append_child("message");
		node.append_attribute("type") = 0;
		node.append_attribute("version") = 1;
		node = node.append_child("auth");
		node.append_child("user").append_child(pugi::node_pcdata).set_value(_username.c_str());
		node.append_child("pswd").append_child(pugi::node_pcdata).set_value(str);

		int n = node_to_buffer(doc, _buf, MAX_CONTENT_LEN);
		_sesson->submitRequest(CMD_REQ_LOGIN, _buf, n, boost::bind(&IpcamClient::doLoginResult, shared_from_this(), _1, _2, fun, context));
	} else {
		defaultFun(buf, size, fun, context);
		std::cout<<"获取安全码失败\n";
		_key = 0;
		if (msg->flag == NE_ERROR) {
			theHandleManager().destroyHandle(_key);
		}
	}
}

void IpcamClient::doLoginResult(void *buf, size_t size, CallbackFun fun, void* context)
{
    Message *msg = (Message*)buf;
    defaultFun(buf, size, fun, context);

    if (msg->flag == NE_ERROR) {
        theHandleManager().destroyHandle(_key);
        _key = 0;
    }
}

void IpcamClient::logout()
{
    _sesson->stopConnection();
    theHandleManager().destroyHandle(_key);
}
