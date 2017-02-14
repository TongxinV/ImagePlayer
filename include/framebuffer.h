#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_



// 宏定义
#define WIDTH		1024	
#define HEIGHT		600
 
 
#define WHITE		0xffffffff			// test ok
#define BLACK		0x00000000
#define RED			0xffff0000
#define GREEN		0xff00ff00			// test ok
#define BLUE		0xff0000ff			

#define GREENP		0x0000ff00			// 一样，说明前2个ff透明位不起作用
 

struct framebuffer{
	const char	*path;
	int fd;
	unsigned int *pfb;
};

typedef struct draw_info{
	unsigned int *pstar;
	unsigned int x0;
	unsigned int y0;
	unsigned int width;
	unsigned int height;
	unsigned int color;
	const unsigned char *pic;
}draw_info_t;

// 函数声明
int  fb_open(struct framebuffer *fb);
void fb_close(struct framebuffer *fb);
void fb_draw_back(struct draw_info *draw_info);
void fb_show_image(struct draw_info *draw_info);


#define DECLARE_FBDEVICE(name, path) \
struct framebuffer name = {path, -1, NULL}



#endif /*_FRAMEBUFFER_H_*/





















