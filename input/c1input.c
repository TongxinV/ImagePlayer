#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




#include <c1config.h>
#include "c1input.h"

DECLARE_INPUT_DEVICE(ts, DEVICE_TOUCH);



int input_device_open(C1Input * input)
{
	// 第1步：打开设备文件
	input->fd = open(input->path, O_RDONLY);
	if (input->fd < 0){
		perror("open");
		return -1;
	}

	input->event= (struct input_event *)malloc(sizeof(struct input_event));
	if(input->event== NULL){
		perror("malloc");
		close(input->fd);
		return -1;
	}

	return 0;
}


//must after input_device_open(.. have be done
struct input_event* read_input_event(C1Input * input)
{
	int ret = -1;

	if(input->fd == -1){
		fprintf(stderr, "input device %s is not open.\n", input->path);
		return NULL;
	}

	// 第2步：读取一个event事件包
	memset(input->event, 0, sizeof(struct input_event));

	ret = read(input->fd, input->event, sizeof(struct input_event));
	if (ret != sizeof(struct input_event)){
		perror("read");
		return NULL;
	}
	
	return input->event;
}


void input_device_close(C1Input * input)
{
	if(input->event!=NULL)
		free(input->event);
	close(input->fd);
}


int touchscreen_init(void)
{
	if(input_device_open(&ts)<0){
		fprintf(stderr, "touchscreen init fail!.\n");
		return -1;
	}
	return 0;
}	

void touchscreen_close(void)
{
	input_device_close(&ts);
}

struct input_event* capture_ev_ts(void)
{
	
	return read_input_event(&ts);
}


