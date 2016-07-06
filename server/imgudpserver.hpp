#ifndef __UDPCLIENTSERVER__
#define __UDPCLIENTSERVER__

#include <netinet/in.h>
#include <sys/socket.h>

#include <algorithm>
#include <vector>


class RawImageBytes
{
 public:
    unsigned int m_size;
    unsigned char *m_bytes;
  
    unsigned int m_next;
 
    RawImageBytes(unsigned int size) 
      : m_size(size),m_next(0) 
    { 
      m_bytes = new unsigned char[size];
    }

    void operator()(unsigned char c)
    {
      m_bytes[m_next++] = c;
    }

    ~RawImageBytes()
    {
      delete m_bytes;
    }

};

class ImageUDPClientServer : public UDPServer
{

 private:


 public:
  typedef std::vector<std::vector<unsigned char> > imagearraytype;

  ImageUDPClientServer(unsigned int port); 



  int Receive(unsigned int& history);
  int Send(imagearraytype& imagearray, int client);
  

};

#endif
