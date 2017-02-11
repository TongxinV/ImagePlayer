/**
 *@Description:<p>ImagePlayer</p>
 *@author TongxinV
 *@time 2017-02-10 09:26:09 
 */

#include <stdio.h>

#include <framebuffer.h>
//#include "display/Image_001.h"
//#include "display/Image_002.h"
#include "display/Image_003.h"


int main(void)
{
	struct framebuffer fb0;

	fb0.fd = -1;
	fb0.pfb= NULL;
	fb0.open  = fb_open;
	fb0.close = fb_close;

	struct draw_info draw_info0;

	draw_info0.x0    =  100;
	draw_info0.y0    =  100;
	draw_info0.width = 1024;
	draw_info0.height=  720;
	draw_info0.color =  RED;
	draw_info0.pic   = Image_003;
	
	printf("hello world.\n");

	fb0.open(&fb0);

	draw_info0.pstar = fb0.pfb;

	//fb_draw_back(&draw_info0);

	fb_show_image(&draw_info0);

	fb0.close(&fb0);
	
	return 0;
}



























