
#ifndef __UDPSERVER__HPP__
#define __UDPSERVER__HPP__

class UDPClient
{
 public:

    UDPClient(void) 
    :m_len(sizeof(m_addr))
    {
    }

    sockaddr_in m_addr;
    unsigned int m_len;
};


class UDPServer
{
protected:
    std::vector<UDPClient> m_activeClients;
  
    unsigned short m_port;
    struct sockaddr_in m_serveraddr;

    int m_socketfd;

    int createSocketFd();

    int ReceiveBytes(std::vector<char>& bytes);
    int SendBytes(std::vector<char> bytes);

};

#endif 
