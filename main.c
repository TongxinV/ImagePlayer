/**
 *@Description:<p>ImagePlayer</p>
 *@author TongxinV
 *@time 2017-02-10 09:26:09 
 */

#include <stdio.h>
#include <stdlib.h>

#include <framebuffer.h>
#include "manager_pic/img_manager.h"
#include "mainloop/loop.h"
#include "input/c1input.h"


//#include <c1image.h>
//#include "display/Image_001.h"
//#include "display/Image_002.h"
//#include "display/Image_003.h"


int main(void)
{
	fb_init();

	manager_init2("./picture");

	touchscreen_init();

	mainloop();

	touchscreen_close();
	
	fb_release();
	
	return 0;
}



























