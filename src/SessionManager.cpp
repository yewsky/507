#include "Common.h"
#include "SessionManager.h"

boost::asio::io_service SessionManager::_ios;


SessionManager& theSessionManager()
{
    static SessionManager _instance;
    return _instance;
}