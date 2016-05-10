
#include "server.h"

static void* server_thread(void *arg)
{
  unsigned short *port = (unsigned short*)arg;

  printf("starting server thread on port: %d\n", *port);  

  return (void*)0;
}

int server_init(unsigned short port)
{
  int r;
  pthread_t id;
  pthread_attr_t attr;

  r = pthread_attr_init(&attr);
  if (r != 0)
    handle_errorno(r,"pthread_attr_init");

  
  r = pthread_create(&id, &attr, &server_thread, &port);
  if (r != 0)
    handle_errorno(r,"pthread_create");


  r = pthread_attr_destroy(&attr);
  if (r != 0)
    handle_errorno(r,"pthread_attr_destroy");

  unsigned long exitcode;
  r = pthread_join(id, (void**)&exitcode);
  if (r != 0)
  {
    handle_errorno(r,"pthread_join");
    printf("thread joined failed exit code: %lu\n", exitcode);
  }
  else
  {
    printf("thread joined return code: %lu\n", exitcode);
  }

  return r;
}

