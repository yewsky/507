#ifndef _NDVRINTERDACE_H_
#define _NDVRINTERFACE_H_

typedef void (*NdvrCallback)(int error, void *context);

int ndvrLogin(std::string addr, int port, std::string user, std::string pswd, NdvrCallback fun, void* context);

int ndvrLogout(int key);


#endif /* _NDVRINTERFACE_H_ */
