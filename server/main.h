#ifndef __MAIN_H__
#define __MAIN_H__

#define DEFAULT_PORT 2048

extern unsigned short verbose;

int process_arguments(int argc, char *argv[]);  
void usage(void);

#endif
