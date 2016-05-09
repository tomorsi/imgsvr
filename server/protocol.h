#ifdef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <time.h>

/*
 * Define the  udp protocol for requesting and 
 * delivering a security camera image. 
 *
 */


/* request images that were taken at or 
 * near timestamp and the maximum amount 
 * of images that should be returned. 
 */
struct request
{
  time_t timestamp;
  unsigned short count;
};

/* Status code from request */
enum response_status { FAILED, SUCCEED, EMPTYSET };

struct response
{
  /* status code from request */
  response_status status;
  
  /* image count returned and raw image data */
  unsigned short count;
  void *images[];
};

#endif
 
