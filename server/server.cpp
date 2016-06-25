#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/fcntl.h> 

#include "server.hpp"

Server::Server(unsigned short port)
    :m_port(port),m_Finished(false)
{
    memset(&m_serverAddr,0,sizeof(m_serverAddr));
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // can remove m_port data member probably. 
    m_serverAddr.sin_port = htons(m_port);

    m_socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socketFd == -1)
    {
	// throw.
	std::cout << "failed socket creation" << std::endl;
    }

    int flags = fcntl(m_socketFd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(m_socketFd, F_SETFL, flags);

    FD_ZERO(&m_readFds);
    FD_SET(m_socketFd,&m_readFds);

    int result = bind(m_socketFd, (struct sockaddr *)&m_serverAddr, sizeof(m_serverAddr));
    if (result < 0)
    {
	// throw
	std::cout << "failed bind: " << result << std::endl;
    }

    m_timeout.tv_usec = 0;
    m_timeout.tv_sec = 15;

    m_maxRecvBufferLen = 2048;

}


void Server::joinerThreadFunction(void)
{

    while(!m_Finished)
    {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_condvar.wait(lock);

	// Refactor this to use for_each.
	std::cout << "active threads: " << m_activeThreads.size() << std::endl;
	auto i = m_activeThreads.begin();
	while ( i != m_activeThreads.end() )
	{
	    std::cout << "joining" << std::endl;
	    if(i->joinable())
	    {
		i->join();
		i = m_activeThreads.erase(i);
	    }
	    else
		i++;
	}
    }


}

void Server::ioThreadFunction(int socketfd)
{
    static int n = 0;
    int l = n++;
    printf("ENTERING service thread[%d] started\n", l );

    struct sockaddr_in clientAddr;
    unsigned int addrLen = sizeof(clientAddr);

    char recvBuffer[m_maxRecvBufferLen];

    // read the request for a history specification then return the
    // n images based on the history request. 
    // example: 5, send back last 5 images taken, or 1 send back most
    // recent immge. 
    int bytesread = recvfrom(socketfd,recvBuffer,m_maxRecvBufferLen,0,
			     (struct sockaddr *)&clientAddr, &addrLen);

    if (bytesread>0)
    {
	// send images...
	recvBuffer[bytesread] = '\0';
	
	printf("recv: %s\n", recvBuffer);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	//std::cout << "recevied: " << recvBuffer << std::endl; 
	//	  << " from ip: " << inet_ntoa(clientAddr.sin_addr) 
	//	  << " port: " << ntohs(clientAddr.sin_port) << std::endl;
    }
    else
    {
	printf("recvfrom returned: %d\n", bytesread);
	exit(1);
    }

    printf("EXITING service thread[%d] started\n", l );

}

void Server::Start()
{
    std::unique_ptr<std::thread> joinerThread (new std::thread(&Server::joinerThreadFunction, this)); 


    int iter = 1;
    while(iter++)
    {
	FD_ZERO(&m_readFds);
	FD_SET(m_socketFd,&m_readFds);

	printf("waiting on client on port: %d\n",  m_port);

	int nready = select(m_socketFd+1,&m_readFds,NULL,NULL,&m_timeout);
	if (nready<0) {
	    // throw 
	    return;
	} 
	
	printf("select returns: %d\n", nready);
	
	if (FD_ISSET(m_socketFd, &m_readFds)) //if set to read
	{ 
	    FD_CLR(m_socketFd, &m_readFds);
	    
	    printf("starting service thread[%d]\n", iter);

	    m_mutex.lock();
	    std::thread Thread(&Server::ioThreadFunction, this, m_socketFd);
	    m_activeThreads.push_back(std::move(Thread));
	    m_mutex.unlock();

	}
	
	m_condvar.notify_all();

    }
}

