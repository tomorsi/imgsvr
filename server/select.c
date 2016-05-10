
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


void read_select(unsigned short port)
{
  int r;
  fd_set readfds, allset;
  int socketfd;
  char recvbuffer[MAXLENGTH],sendbuffer[MAXLENGTH];
  struct timeval timeout;
  struct sockaddr_in clientaddr,srvaddr;

  timeout.tv_sec = 4;
  timeout.tv_usec = 150000; 

  if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
  {
    handle_errormsg("socket()");
  }

  memset((char *)&srvaddr, 0, sizeof(srvaddr));
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  /* Using port 0 allows OS to choose port. */
  srvaddr.sin_port = htons(port); 
  r = bind(socketfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
  if (r < 0)
  {
    handle_errorno(r,"bind()");
  }

  int flags = fcntl(socketfd, F_GETFL);
  flags |= O_NONBLOCK;
  fcntl(socketfd, F_SETFL, flags);

  FD_ZERO(&allset);
  FD_SET(socketfd,&allset);

  // Use a condition variable here to indicate end.
  while(1)
  {
    int nready;

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
