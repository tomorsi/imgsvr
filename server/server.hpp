#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <netinet/in.h>
#include <sys/socket.h>

#include <thread>
#include <array>
#include <vector>
#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>

class Server
{
private:
    unsigned short m_port;
    struct sockaddr_in m_serverAddr;
    timeval m_timeout;

    fd_set m_readFds;

    int m_socketFd;

    int m_maxRecvBufferLen;

    bool m_Finished;

    std::vector<std::thread> m_activeThreads;
    std::thread m_controlThread;


    void ioThreadFunction(int socketfd);

    void controlThreadFunction(void);

    std::mutex m_mutex;
    std::condition_variable m_condvar;

public:
    Server(unsigned short port);

    void Start();
};

 
#endif 

