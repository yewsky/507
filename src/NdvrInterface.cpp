#include "Common.h"

#include "NdvrInterface.h"
#include "IpcamClient.h"

#include "HandleManager.h"
#include "Handle.h"

int ndvrLogin(std::string addr, int port, std::string user, std::string pswd, NdvrCallback fun, void* context)
{
    IpcamClient::SmartPtr ic(new IpcamClient);
    return ic->login(addr, port, user, pswd, fun, context);
}

int ndvrLogout(int key)
{
    Handle::Ptr p = theHandleManager().lookupHandle(key);
    if (p == Handle::null()) {
        return -1;
    }

    IpcamClient::SmartPtr ic = (IpcamClient::SmartPtr)(*p);
    ic->logout();

    return 0;
}
