
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "Server.h"

unsigned short verbose = 0;
unsigned short port = 2048;

void usage(void)
{
}

int process_arguments(int argc, char *argv[])
{
  int c;
  int r = 0;
  while((c = getopt(argc, argv,"vp:")) != -1)
  {
    switch(c)
    {
      case 'v':
        verbose = 1;
        break;
      case 'p':
        port = atoi(optarg);
	if (!port)
	  r = -1;
        break;  
      default:
        usage();
        break;
    }
  }
  return r;
}

/*
 * The lifetime of argv, env is the program cant
 * be use in atext routine. 
 */

int main(int argc, char *argv[], char **env)
{
  int r = 0;

  if (process_arguments(argc,argv)>-1)
  {
      Server server(port);
      server.Start();
  }
  else 
  {
    r = -1;  
    usage();
  }

  return r;
}

