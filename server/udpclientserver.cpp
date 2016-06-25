
#include "UDPClientServer.h"

#include <sys/socket.h>

UDPClientServer::UDPClientServer(unsigned int port)
    :m_port(port)
{
    // Create server address to listen for UDP packets. 
    memset(&m_serveraddr,0,sizeof(m_serveraddr));
    m_serveraddr.sin_family = AF_INET;
    m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_serveraddr.sin_port = htons(m_port);

    
}

int UDPClientServer::createSocketFd()
{
    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd == -1)
    {
	return socketfd;
    }

    
    int result = bind(m_socketFd, (struct sockaddr *)&m_serveraddr, sizeof(m_serveraddr));
    if (result < 0)
    {
	return result;
    }

}


int UDPClientServer::Receive(unsigned int& history)
{
    class UDPClient client;

    unsigned int recvbytes;
    int actual = recvfrom(m_socketfd, &recvbytes, sizeof(recvbytes), 0,
	     &client.m_addr, client.m_len);

    if (actual < 0 )
	return actual;
    if (actual != sizeof(recvbytes))
	return -1;


    m_activeClients.push_back(client);
    
    return m_activeClients.size()-1;
}

int UDPClientServer::Send(imagearraytype& imagearray, int id)
{
    UDPClient client = m_activeClients[id];

    int imagecount = imagearray.size();
    sendto(m_socketfd, imagecount, sizeof(imagecount), 0,
	   client.m_addr, client.m_len);

    for(auto i = imagearray.begin(); i != imagearray.end(); i++)
    {
	// Send the size of the image. 
	unsigned int imagesize = i->size();
	sendto(m_socketfd, imagesize, sizeof(imagesize), 0,
	       client.m_addr, client.m_len);


	RawImageBytes bytes(imagesize);
	std::for_each(i->begin(), i->end(), bytes);

	sendto(m_socketfd, bytes.m_bytes, bytes.m_size, 0,
	       client.m_addr, client.m_len);
    }

} 

