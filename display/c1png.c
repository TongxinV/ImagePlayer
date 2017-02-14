/**
 *@Description:<p>PNG Decode and Encode</p>
 *@author TongxinV
 *@time 2017-02-11 13:20:49 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>

#include <c1png.h>


#define PNG_BYTES_TO_CHECK 4



//这个函数u虽然没用到，但使用了FILE **fp，测试了一下，使用FILE *fp可以
//函数内部做相应修改
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

	FILE * infile;
	
	pngImg= (C1Image*)malloc(sizeof(C1Image));
	infile = fopen(path, "rb");
	if(!infile){
		fprintf(stderr, "file %s open fail!\n", path);
		free(pngImg);
		return NULL;
	}
	fprintf(stdout, "file %s open success..\n", path);


	if(check_if_png(path, &infile)){
		fprintf(stderr, "file %s open fail!\n", path);
		free(pngImg);
		return NULL;
	}
	fprintf(stdout, "file %s is png picture.\n", path);

	
	return NULL;
}






















