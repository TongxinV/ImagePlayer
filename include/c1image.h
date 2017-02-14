#ifndef _C1IMAGE_H_
#define _C1IMAGE_H_


#include <framebuffer.h>


typedef struct tagImage
{
	unsigned short fileType;
    int width;  
    int height;  
    int channels;  
    unsigned char* imageData;  
}C1Image; 



int ImageDispaly(struct framebuffer * fb, const char * path);




#endif











