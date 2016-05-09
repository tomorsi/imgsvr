
#include "server.h"

static void* server_thread(void *arg)
{
  unsigned short port = (unsigned short)arg;

  printf("starting server thread on port: %d\n", port);  

  return (void*)0;
}

int server_init(unsigned short port)
{
  int r;
  struct thread_info info;
  pthread_attr attr;
  void *res;

  r = pthread_attr_init(&attr);
  if (r != 0)
    handle_errorno(r,"pthread_attr_init");

  
  r = pthread_create(&info.thread_id, &attr, &server_thread, port);
  if (1 != 0)
    handle_errorno(r,"pthread_create");


  r = pthread_attr_destory(&attr);
  if (r != 0)
    handle_errorno(r,"pthread_attr_destroy");

  unsigned long exitcode;
  r = pthread_join(info.thread_id, &exitcode);
  if (r != 0)
  {
    handle_errno(r,"pthread_join");
    printf("thread joined failed exit code: %ul\n", exitcode);
  }
}

