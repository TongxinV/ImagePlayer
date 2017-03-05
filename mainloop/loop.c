
#include <stdio.h>
#include <unistd.h> 

#include "loop.h"
#include <c1config.h>
#include "../input/c1input.h"
#include "../manager_pic/img_manager.h"
#include <c1image.h>



void mainloop(void)
{
	struct input_event * ev;
	FileManageinfo * Info;

	
	Info = get_first_imgfile();//打开图片管理器显示第一张图片
	ImageDispaly(Info->pathname);
	
	while(1)
	{
		ev = capture_ev_ts();
		printf("1.\n");
		if ((ev->type == EV_ABS) && (ev->code == ABS_X))
		{
			printf("2.\n");
			if ((ev->value >= 0) && (ev->value < 100))
			{
				//Info = get_last_imgfile();
				Info = get_last_imgfile(Info);
				printf("pathname = %s.\n", Info->pathname);
				ImageDispaly(Info->pathname);
			}

			else if((ev->value > X210_WIDTH-100) && (ev->value <= X210_WIDTH))
			{
				//Info = get_next_imgfile();
				Info = get_next_imgfile(Info);
				printf("pathname = %s.\n", Info->pathname);
				ImageDispaly(Info->pathname);
			}

			else
			{
				// 不翻页
			}
			
		}
			
		//sleep(2);
		
	}
}

