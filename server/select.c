
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>//use select() for multiplexing
#include <sys/fcntl.h> // for non-blocking

#include "select.h"
#include "server.h"


void read_select()
{
  fd_set readfds, allset;
  int socketfd;
  char recvbuffer[MAXLENGTH],sendbuffer[MAXLENGTH];
  struct timeval timeout;

  timeout.tv_sec = 4;
  timeout.tv_usec = 150000; 

  if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
  {
    handle_errormsg("socket()");
  }

  int flags = fcntl(socketfd, F_GETFL);
  flags |= O_NONBLOCK;
  fcntl(socketfd, F_SETFL, flags);

  FD_ZERO(&allset);
  FD_SET(socketfd,&allset);

  while(1)
  {
    int nready;
    struct sockaddr_in clientaddr,srvaddr;

    unsigned int addrlen = sizeof(clientaddr);

    nready = select(socketfd+1,&readfds,NULL,NULL,&timeout);
    if (nready<0) {
      handle_errormsg("select failed");
    } 

    if (FD_ISSET(socketfd, &readfds)) //if set to read
    { 
	FD_CLR(socketfd, &readfds);

	//block call, will wait till client enters something, before proceeding
	int bytesread = recvfrom(socketfd,recvbuffer,MAXLENGTH,0,
				 (struct sockaddr *)&clientaddr, &addrlen);
 
	recvbuffer[bytesread] = '\0'; //add null to the end of the buffer

	printf("\n(%s , %d) said: %s\n",inet_ntoa(clientaddr.sin_addr),
	       ntohs(clientaddr.sin_port),
	       recvbuffer);
          
    }
  }

}
