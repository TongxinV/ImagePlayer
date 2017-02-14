#ifndef _C1IMAGE_H_
#define _C1IMAGE_H_


#include <framebuffer.h>


typedef struct tagImage
{
	unsigned short fileType;
    unsigned int    width;  
    unsigned int   height;  
    unsigned int channels;	/* number of data channels per pixel (1, 2, 3, 4) c=b/8 */
	unsigned int   bpp;		/* number of bits per pixel */
    unsigned char* imageData;  
}C1Image; 



int ImageDispaly(struct framebuffer * fb, const char * path);




#endif











