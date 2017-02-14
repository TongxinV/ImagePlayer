/**
 *@Description:<p>PNG Decode and Encode</p>
 *@author TongxinV
 *@time 2017-02-11 13:20:49 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
#include <pngstruct.h>
#include <pnginfo.h>

#include <c1png.h>


#define PNG_BYTES_TO_CHECK 4

//这个函数u虽然没用到，但使用了FILE **fp，测试了一下，使用FILE *fp可以
//但是fopen要在函数外使用，函数内部做相应修改
static int check_if_png(char *file_name, FILE **fp)
{
	char buf[PNG_BYTES_TO_CHECK];
	/* Open the prospective PNG file. */
	if ((*fp = fopen(file_name, "rb")) == NULL)
		return 0;
	
	/* Read in some of the signature bytes */
	if (fread(buf, 1, PNG_BYTES_TO_CHECK, *fp) != PNG_BYTES_TO_CHECK)
		return 0;
	
	/* Compare the first PNG_BYTES_TO_CHECK bytes of the signature.
	Return nonzero (true) if they match */
	return(png_sig_cmp(buf, (png_size_t)0, PNG_BYTES_TO_CHECK));
}



C1Image* ReadPNGFile2Img(const char* path)
{
	C1Image* pngImg;
	int w, h, c;
	int i, j;
	int pos=0;
	
	png_structp *png_ptr;
	png_infop info_ptr;

	/* More stuff */
	FILE * infile;
	png_bytep * row_pointers;	/* Output all iamge data buffer point  */
	int row_stride;				/* physical row width in output buffer */
	png_byte color_type;		/* RGB24位真彩色对应 PNG_COLOR_TYPE_RGB*/

	
	pngImg= (C1Image*)malloc(sizeof(C1Image));
	infile = fopen(path, "rb");
	if(!infile){
		fprintf(stderr, "file %s open fail!\n", path);
		free(pngImg);
		return NULL;
	}
	fprintf(stdout, "file %s open success..\n", path);

#if 0
	if(check_if_png(path, &infile)){
		fprintf(stderr, "file %s open fail!\n", path);
		free(pngImg);
		return NULL;
	}
	fprintf(stdout, "file %s is png picture.\n", path);
#endif


	//第1步: 相关数据结构实例化
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if (png_ptr == 0){
		fclose(infile);
		return NULL;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == 0){
		png_destroy_read_struct(&png_ptr, 0, 0);
		fclose(infile);
		return NULL;
	}


	//第2步: 设置错误处理函数
	if (setjmp(png_jmpbuf(png_ptr))){
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		fclose(infile);
		return NULL;
	}

	//第3步: 将要解码的png图片的文件指针和png解码器绑定起来
	png_init_io(png_ptr, infile);


	//第4步: 读取png图片信息(忽略透明度alpha)
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_STRIP_ALPHA, 0);


	//第5步: 相关图片信息打印出来看一看
	color_type = info_ptr->color_type;
	
	pngImg->width   = w = info_ptr->width;
	pngImg->height  = h = info_ptr->height;
	pngImg->channels= c = info_ptr->channels;
	pngImg->imageData= (unsigned char*)malloc(sizeof(unsigned char)*w*c*h);

	fprintf(stdout, "color_type = %d.\n", color_type);
	fprintf(stdout, "width    = %u.\n", pngImg->width);
	fprintf(stdout, "height   = %u.\n", pngImg->height);
	fprintf(stdout, "channels = %u.\n", pngImg->channels);


	// 第6步: 读取真正的图像信息(读出整个图像数据而不是一行)
	row_pointers = png_get_rows(png_ptr,info_ptr);
	row_stride   = info_ptr->width * info_ptr->height * info_ptr->channels;

	
	// 第7步: 图像数据移动到我们自己的buff中(只处理RGB24位真彩色图片，其他格式的图片不管)
	if(color_type == PNG_COLOR_TYPE_RGB)
  	{
   		//memcpy(pngImg->imageData, row_pointers, row_stride);
#if 1
		for(i=0; i<h; i++)
		{
			for(j=0; j<3*w; j+=3)
			{
				pngImg->imageData[pos++] = row_pointers[i][j+0];		
				pngImg->imageData[pos++] = row_pointers[i][j+1];		
				pngImg->imageData[pos++] = row_pointers[i][j+2];		
			}
		}
#endif
  	}
	
	// 第8步: 收尾处理
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);

	fclose(infile);
	
	return pngImg;
}






















