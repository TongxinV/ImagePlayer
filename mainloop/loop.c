



#include "loop.h"

#include <c1image.h>
#include "../manager_pic/img_manager.h"


void mainloop(void)
{
	FileManageinfo* point;
	int i;	
	
	while(1)
	{
		for(i = 0; i< 10; i++){
			point = ExtractImgfile(i);
			ImageDispaly(point->pathname);
			sleep(2);
		}
	}

	ImageDispaly("tu006.png");
}















