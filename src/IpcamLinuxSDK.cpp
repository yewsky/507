
#include "Common.h"
#include "NdvrInterface.h"
#include "WorkerThreads.h"

void fun(int err, void* context)
{
    std::cout << "errno = " << err << std::endl;
}

int main(int argc, char* argv[])
{
	theWorkerThreads().init();
	int s = ndvrLogin("10.0.0.213", 6005, "sa", "123456", NULL, NULL);

	std::cout<<"请按键继续..\n";
	getchar();

	ndvrLogout(s);

	theWorkerThreads().cleanup();

    return 0;
}

