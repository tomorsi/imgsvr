
#include "udpclientserver.hpp"

#include <sys/socket.h>

ImgUDPServer::ImgUDPServer(unsigned int port)
    :UDPServer(port)
{
}

int UDPClientServer::Receive(unsigned int& history)
{
    class UDPClient cid;

    cid = this->ReceiveBytes(&history, sizeof(history));

    return cid;
}

int UDPClientServer::Send(imagearraytype& imagearray, int id)
{
    int bytesSent = 0;
    UDPClient client = m_activeClients[id];

    int imagecount = imagearray.size();
    int result = this->SendBytes(&imagecount, sizeof(imagecount), id);

    if (result < 0)
	return result;

    bytesSent += result;

    for(auto i = imagearray.begin(); i != imagearray.end(); i++)
    {

	result = this->SendVector(*i,cid);

	if (result < 0)
	    return result;

	bytesSent += result;
    }
    
    return bytesSent;
} 

