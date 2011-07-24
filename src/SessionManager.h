#ifndef _SESSIONMANAGER_H_
#define _SESSIONMANAGER_H_

#include "Session.h"

class SessionManager : public boost::noncopyable
{
public:
    SessionManager() 
    {
    }

    virtual ~SessionManager() 
    {
        std::cout<< "SessionManager Destructors..\n";
    }

public:
    Session::SmartPtr createSession()
    {
        std::string uuid = genUuid();
        Session::SmartPtr ss = Session::create(uuid, _ios);
        _sessions[uuid] = ss;
        return ss;
    }

    void destroySession(std::string& uuid)
    {
        if (_sessions.count(uuid)) {
            _sessions.erase(uuid);
            std::cout << "SessionManager: erase: " << uuid << "\n";
        }
    }

    std::string genUuid()
    {
        boost::uuids::uuid uu = _uuidGenerator();
        return boost::uuids::to_string(uu);
    }

private:
    boost::unordered_map<std::string, Session::SmartPtr> _sessions;
    boost::uuids::random_generator _uuidGenerator;

    friend SessionManager& theSessionManager();

public:
    static boost::asio::io_service _ios;
};

SessionManager& theSessionManager();

#endif /* _SESSIONMANAGER_H_ */

