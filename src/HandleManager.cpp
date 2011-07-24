#include "Common.h"
#include "HandleManager.h"

HandleManager& theHandleManager()
{
    static HandleManager _instance;
    return _instance;
}
