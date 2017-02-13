/**
 *@Description:<p>JPEG Decode and Encode</p>
 *@author TongxinV
 *@time 2017-02-11 13:20:49 
 */

#include <stdio.h>
#include <stdlib.h>

#include <jerror.h>
#include <jpeglib.h>
#include <setjmp.h>

#include <c1jpeg.h>

//extern JSAMPLE * image_buffer;	/* Points to large array of R,G,B-order data */
//extern int image_height;		/* Number of rows in image */
//extern int image_width;			/* Number of columns in image */


struct my_error_mgr{
	struct jpeg_error_mgr pub;	/* "public" fields */
	jmp_buf setjmp_buffer;	/* for return to caller */
};
typedef struct my_error_mgr* my_error_ptr;

void put_scanline_someplace(JSAMPROW buffer, int row_stride)
{
	
}



METHODDEF(void)
my_error_exit(j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */  
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	
	/* Always display the message. */  
	(*cinfo->err->output_message) (cinfo);
	
	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}

//GLOBAL;从名称看应该是把这个函数声明为全局
//GLOBAL(int)
//read_JPEG_file(char * filename)
C1Image* ReadJPEGFile2Img(const char* path)
{
	C1Image* jpgImg;
	
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	/* More stuff */  
	FILE * infile;			/* source file */
	JSAMPARRAY buffer;		/* Output row buffer point */
	int row_stride; 		/* physical row width in output buffer */

	jpgImg = (C1Image*)malloc(sizeof(C1Image));
	infile = fopen(path, "rb");
	if(!infile){
		fprintf(stderr, "file %s open fail!\n", path);
		free(jpgImg);
		return NULL;
	}
	fprintf(stdout, "file %s open success..\n", path);

	/* Step 1: allocate and initialize JPEG decompression object */
	
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;	

	if (setjmp(jerr.setjmp_buffer)){
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return 0;
	}

	jpeg_create_decompress(&cinfo);


	/* Step 2: specify data source (eg, a file) */

	jpeg_stdio_src(&cinfo, infile);


	/* Step 3: read file parameters with jpeg_read_header() */

	(void) jpeg_read_header(&cinfo, TRUE);
	

	/* Step 4: set parameters for decompression */

	//使用默认配置


	/* Step 5: Start decompressor */

	(void) jpeg_start_decompress(&cinfo);

	//Add by TongxinV
	jpgImg->width = cinfo.output_width;
	jpgImg->height= cinfo.output_height;

	
	row_stride = cinfo.output_width * cinfo.output_components;	
	buffer = (*cinfo.mem->alloc_sarray)\
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);/* JSAMPLEs per row in output buffer */

	
	/* Step 6: while (scan lines remain to be read) */

	while (cinfo.output_scanline < cinfo.output_height){
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		put_scanline_someplace(buffer[0], row_stride);
	}


	/* Step 7: Finish decompression */

	(void)jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);


	/* Step 8: Release JPEG decompression object */
	fclose(infile);

	
	return jpgImg;
}

















