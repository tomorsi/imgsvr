
#include "udpserver.hpp"

#include <sys/socket.h>

UDPServer::UDPServer(unsigned int port)
    :m_port(port)
{
    // Create server address to listen for UDP packets. 
    memset(&m_serveraddr,0,sizeof(m_serveraddr));
    m_serveraddr.sin_family = AF_INET;
    m_serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_serveraddr.sin_port = htons(m_port);

    
}

int UDPServer::createSocketFd()
{
    m_socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socketfd == -1)
    {
	return m_socketfd;
    }

    
    int result = bind(m_socketfd, (struct sockaddr *)&m_serveraddr, sizeof(m_serveraddr));
    if (result < 0)
    {
	return result;
    }

    return m_socketfd;
}

int UDPServer::ReceiveBytes(char *buffer, size_t size, int &cid)
{
    int actual = recvfrom(m_socketfd, &buffer, buffersize, 0,
			  (struct sockaddr *)&client.m_addr, &client.m_len);

    m_activeClients.push_back(client);

    cid = m_activeClients.size()-1;

    return actual; 

}

int UDPServer::ReceiveVector(std::vector<unsigned char>& bytes)
{
    int cid;

    char buffer = new char[2048];

    unsigned int recvbytes = this->ReceiveBytes(buffer,2048, cid);
 
    if (recvbytes < 0 )
	return recvbytes;

    bytes.clear();

    for(int i = 0; i < recvbytes; i++)
	bytes.push_back(buffer[i]);
}

int UDPServer::SendBytes(char *buffer, size_t bytes, int cid)
{
    int bytesSent = 0;
    UDPClient client = m_activeClients[id];


}

int UDPServer::SendVector(std::vector<unsigned char> bytes, int cid)
{


    size_t size = bytes.count();
    char *buffer = new char[size];

    for (int i = 0; i < size; i++)
    {
	buffer[i] = bytes[i];
    }

    int bytesSent = this->SendBytes(buffer, size, cid);

    if (bytesSent < 0)
	return bytesSent;

    return bytesSent;
} 

