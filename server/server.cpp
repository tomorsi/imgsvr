#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/fcntl.h> 

#include "server.hpp"

Server::Server(unsigned short port)
    :m_udpserver(port)
{
    if (0>=m_udpserver.createSocketFd())
    {
	// throw exception
    }

}

void Server::ioThreadFunction(void)
{
    while(m_running)
    {
	int history;

	int cid = m_udpserver.Recieve(history);
    
	// get images from file system.
	imagearraytype imagearray;

	m_udpserver.Send(imagearray, cid);
    }
}

void Server::controlThreadFunction()
{
    

}

void Server::Start()
{
    m_running = true;

    m_mutex.lock();
    for (int i = m_nthreads)
    {
	std::thread Thread(&Server::ioThread, this);
	m_activeThread.push_back(std::move(thread));
    }
    m_mutex.unlock();
}

void Server::Wait()
{
    m_controlThread = std::Thread(&Server::controlThreadFunction);
    m_controlThread.join();
}

