#ifndef _C1INPUT_H_
#define _C1INPUT_H_


#include <linux/input.h>



typedef struct tagInputInfo{
	const char	*path;
	int fd;
	struct input_event * event;
}C1Input;


#define DECLARE_INPUT_DEVICE(name, path) \
struct tagInputInfo name = {path, -1, NULL}


int input_device_open(C1Input * input);

struct input_event* read_input_event(C1Input * input);

void input_device_close(C1Input * input);


//touchscreen input device 
int touchscreen_init(void);

void touchscreen_close(void);

struct input_event* capture_ev_ts(void);




#endif






















