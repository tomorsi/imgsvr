#ifndef __SERVER_H__
#define __SERVER_H__

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern int server_init(unsigned short port);

#define handle_errorno(err, msg) \
  do { errno = err; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_errormsg(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

#endif
 


