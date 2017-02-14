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

//�������u��Ȼû�õ�����ʹ����FILE **fp��������һ�£�ʹ��FILE *fp����
//����fopenҪ�ں�����ʹ�ã������ڲ�����Ӧ�޸�
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
	png_byte color_type;		/* RGB24λ���ɫ��Ӧ PNG_COLOR_TYPE_RGB*/

	
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


	//��1��: ������ݽṹʵ����
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


	//��2��: ���ô�������
	if (setjmp(png_jmpbuf(png_ptr))){
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		fclose(infile);
		return NULL;
	}

	//��3��: ��Ҫ�����pngͼƬ���ļ�ָ���png������������
	png_init_io(png_ptr, infile);


	//��4��: ��ȡpngͼƬ��Ϣ(����͸����alpha)
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_STRIP_ALPHA, 0);


	//��5��: ���ͼƬ��Ϣ��ӡ������һ��
	color_type = info_ptr->color_type;
	
	pngImg->width   = w = info_ptr->width;
	pngImg->height  = h = info_ptr->height;
	pngImg->channels= c = info_ptr->channels;
	pngImg->imageData= (unsigned char*)malloc(sizeof(unsigned char)*w*c*h);

	fprintf(stdout, "color_type = %d.\n", color_type);
	fprintf(stdout, "width    = %u.\n", pngImg->width);
	fprintf(stdout, "height   = %u.\n", pngImg->height);
	fprintf(stdout, "channels = %u.\n", pngImg->channels);


	// ��6��: ��ȡ������ͼ����Ϣ(��������ͼ�����ݶ�����һ��)
	row_pointers = png_get_rows(png_ptr,info_ptr);
	row_stride   = info_ptr->width * info_ptr->height * info_ptr->channels;

	
	// ��7��: ͼ�������ƶ��������Լ���buff��(ֻ����RGB24λ���ɫͼƬ��������ʽ��ͼƬ����)
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
	
	// ��8��: ��β����
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);

	fclose(infile);
	
	return pngImg;
}






















