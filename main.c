/**
 *@Description:<p>ImagePlayer</p>
 *@author TongxinV
 *@time 2017-02-10 09:26:09 
 */

#include <stdio.h>
#include <stdlib.h>

#include <framebuffer.h>
#include <c1image.h>

//#include "display/Image_001.h"
//#include "display/Image_002.h"
//#include "display/Image_003.h"


int main(void)
{
	DECLARE_FBDEVICE(fb0, "/dev/fb0");

	fb_open(&fb0);

	printf("hello world.\n");

	ImageDispaly(&fb0, "tu005.bmp");

	
#if 0
	C1Image* img0;
	
	img0 = Read24BitBmpFile2Img("tu005.bmp");

	draw_info0.x0    =  0;
	draw_info0.y0    =  0;
	draw_info0.width = img0->width;
	draw_info0.height= img0->height;
	draw_info0.color = RED;
	draw_info0.pic   = img0->imageData;

	fb_show_image(&draw_info0);
	
	free(img0->imageData);
	free(img0);
#endif

#if 0
	C1Image* img1;

	img1 = ReadJPEGFile2Img("tu001.jpg");

	draw_info0.x0    =  0;
	draw_info0.y0    =  0;
	draw_info0.width = img1->width;
	draw_info0.height= img1->height;
	draw_info0.color = RED;
	draw_info0.pic   = img1->imageData;

	fb_show_image(&draw_info0);

	free(img1->imageData);
	free(img1);
#endif

	fb_close(&fb0);
	
	return 0;
}



























