/**
 *@Description:<p>framebuffer基本操作代码</p>
 *@author TongxinV
 *@time 2017-02-10 09:26:09 
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <c1config.h>
#include "framebuffer.h"



DECLARE_FBDEVICE(fb, FBDEVICE);


void fb_init(void){ fb_open(&fb); }

void fb_release(void){ fb_close(&fb); }

int fb_open(struct framebuffer *fb)
{
	int ret = -1;
	 
	struct fb_fix_screeninfo finfo = {0};
	struct fb_var_screeninfo vinfo = {0};
	 
	// 第1步：打开设备
	fb->fd = open(fb->path, O_RDWR);
	if (fb->fd < 0){
		perror("open");
		return -1;
	}
	printf("open %s success.\n", fb->path);
	 
	// 第2步：获取设备的硬件信息
	ret = ioctl(fb->fd, FBIOGET_FSCREENINFO, &finfo);
	if (ret < 0){
		perror("ioctl");
		return -1;
	}
	printf("smem_start = 0x%lx, smem_len = %u.\n", finfo.smem_start, finfo.smem_len);
	 
	ret = ioctl(fb->fd, FBIOGET_VSCREENINFO, &vinfo);
	if (ret < 0)
	{
		perror("ioctl");
		return -1;
	}
	printf("xres = %u, yres = %u.\n", vinfo.xres, vinfo.yres);
	printf("xres_virtual = %u, yres_virtual = %u.\n", vinfo.xres_virtual, vinfo.yres_virtual);
	printf("bpp = %u.\n", vinfo.bits_per_pixel);
 
#if 0	 
	// 修改驱动中屏幕的分辨率
	vinfo.xres = 1024;
	vinfo.yres = 600;
	vinfo.xres_virtual = 1024;
	vinfo.yres_virtual = 1200;
	ret = ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo);
	if (ret < 0)
	{
		perror("ioctl");
		return -1;
	}

	// 再次读出来检验一下
	ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	if (ret < 0){
		perror("ioctl");
		return -1;
	}
	printf("修改过之后的参数：\n");
	printf("xres = %u, yres = %u.\n", vinfo.xres, vinfo.yres);
	printf("xres_virtual = %u, yres_virtual = %u.\n", vinfo.xres_virtual, vinfo.yres_virtual);
	printf("bpp = %u.\n", vinfo.bits_per_pixel);
#endif

	// 第3步：进行mmap
	unsigned long len = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
	printf("len = %ld\n", len);
	fb->pfb = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fb->fd, 0);
	if (NULL == fb->pfb){
		perror("mmap");
		return -1;
	}
	printf("fb mmap success. pfb = %p.\n", fb->pfb);

	return 0;
}
 
void fb_close(struct framebuffer *fb)
{
	close(fb->fd);
	printf("close %s success.\n", fb->path);
}
 
 
void fb_draw_back(struct draw_info *draw_info)
{
	unsigned int *p = fb.pfb;
	
	unsigned int x, y;

	for (y=0; y<draw_info->height; y++)
	{
		for (x=0; x<draw_info->width; x++)
		{
			*(p + y * X210_WIDTH + x) = draw_info->color;
		}
	}
}
 
void fb_show_image(struct draw_info *draw_info)
{
	unsigned int *p = fb.pfb;
	const unsigned char *img = draw_info->pic;
	
	unsigned int x, y;
	unsigned int cnt ;

	for (y=draw_info->y0; (y<draw_info->height)&&(y<X210_HEIGHT); y++)
	{
		for (x=draw_info->x0; (x<draw_info->width)&&(x<X210_WIDTH); x++)
		{
			cnt = (draw_info->width)*y+x;
			cnt*=3;
			*(p + y * X210_WIDTH + x) = ((img[cnt+0] << 16) | (img[cnt+1] << 8) | (img[cnt+2] << 0));//byte[0-2]:R G B
		}
	}
}





























