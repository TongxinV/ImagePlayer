/**
 *@Description:<p>ImagePlayer</p>
 *@author TongxinV
 *@time 2017-02-10 09:26:09 
 */

#include <stdio.h>
#include <stdlib.h>

#include <framebuffer.h>
#include <Bitmap.h>
//#include "display/Image_001.h"
//#include "display/Image_002.h"
#include "display/Image_003.h"


int main(void)
{
	DECLARE_FBDEVICE(fb0, "/dev/fb0");

	struct draw_info draw_info0;

	draw_info0.x0    =  100;
	draw_info0.y0    =  100;
	draw_info0.width = 1024;
	draw_info0.height=  720;
	draw_info0.color =  RED;
	draw_info0.pic   = Image_003;
	
	printf("hello world.\n");

	fb_open(&fb0);

	draw_info0.pstar = fb0.pfb;
	
	fb_show_image(&draw_info0);

	C1Image* img0;
	
	img0 = Read24BitBmpFile2Img("tu004.bmp");

	draw_info0.x0    =  0;
	draw_info0.y0    =  0;
	draw_info0.width = img0->width;
	draw_info0.height= img0->height;
	draw_info0.color = RED;
	draw_info0.pic   = img0->imageData;

	fb_show_image(&draw_info0);
	
	free(img0->imageData);
	free(img0);
	
	fb_close(&fb0);
	
	return 0;
}



























