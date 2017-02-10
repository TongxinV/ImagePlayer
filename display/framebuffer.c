/**
 *@Description:<p>framebuffer������������</p>
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

#include <framebuffer.h>

int fb_open(struct framebuffer *fb)
{
	int ret = -1;
	 
	struct fb_fix_screeninfo finfo = {0};
	struct fb_var_screeninfo vinfo = {0};
	 
	// ��1�������豸
	fb->fd = open(FBDEVICE, O_RDWR);
	if (fb->fd < 0){
		perror("open");
		return -1;
	}
	printf("open %s success.\n", FBDEVICE);
	 
	// ��2������ȡ�豸��Ӳ����Ϣ
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
	// �޸���������Ļ�ķֱ���
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

	// �ٴζ���������һ��
	ret = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
	if (ret < 0){
		perror("ioctl");
		return -1;
	}
	printf("�޸Ĺ�֮��Ĳ�����\n");
	printf("xres = %u, yres = %u.\n", vinfo.xres, vinfo.yres);
	printf("xres_virtual = %u, yres_virtual = %u.\n", vinfo.xres_virtual, vinfo.yres_virtual);
	printf("bpp = %u.\n", vinfo.bits_per_pixel);
#endif

	// ��3��������mmap
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
	printf("close %s success.\n", FBDEVICE);
}
 
 
void fb_draw_back(struct draw_info *draw_info, struct framebuffer *fb)
{
	unsigned int x, y;

	for (y=0; y<draw_info->height; y++)
	{
		for (x=0; x<draw_info->width; x++)
		{
			*(fb->pfb + y * WIDTH + x) = draw_info->color;
		}
	}
}
 

 
 
 
 
 
 
 
 
 
 
 
 
 





























