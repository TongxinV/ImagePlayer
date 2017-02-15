

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <framebuffer.h>
#include <c1image.h>

#include <c1bitmap.h>
#include <c1jpeg.h>
#include <c1png.h>

#define IMGJPEG 0x01
#define IMGBMP  0x02
#define IMGPNG  0x03


static int recodniseType(FILE * pFile)
{
	char type_buffer[8] = {0};

	if(fread(type_buffer, 1, 8, pFile)!=8){
		fprintf(stderr, "file read fail!\n");
		return -1;
	}

	
	if((0xff == type_buffer[0]) && (0xd8 == type_buffer[1]))
	{
		return IMGJPEG;
	}
	
	else if((0x42 == type_buffer[0]) && (0x4d == type_buffer[1]))
	{
		return  IMGBMP;
	}
	//89 50 4E 47 0D 0A 1A 0A
	else if((0x89 == type_buffer[0]) && (0x50 == type_buffer[1]))
	{
		return  IMGPNG;
	}

	return 0;
	
}



int ImageDispaly(const char * path)
{
	FILE * imgFile;
	C1Image* pImag;
	draw_info_t* p_draw_info;
	unsigned int IMGTYPE = 0;

	
 	p_draw_info = (draw_info_t*)malloc(sizeof(draw_info_t));
	
	if((imgFile=fopen(path, "rb"))==NULL){
		fprintf(stderr, "file %s open fail!\n", path);
		free(p_draw_info);
		return -1;
	}
	fprintf(stdout, "file %s open success..\n", path);


	IMGTYPE = recodniseType(imgFile);

	switch (IMGTYPE){
    	case IMGJPEG:
			fprintf(stdout, "file %s is jpeg picture.\n", path);
			
			pImag = ReadJPEGFile2Img(path);
			
			p_draw_info->x0	 =	0;
			p_draw_info->y0	 =	0;
			p_draw_info->width = pImag->width;
			p_draw_info->height= pImag->height;
			p_draw_info->color = RED;
			p_draw_info->pic   = pImag->imageData;
			
			fb_show_image(p_draw_info);
			
			free(pImag->imageData);
			free(pImag);


			break;
			
        case  IMGBMP:
			fprintf(stdout, "file %s is  BMP picture.\n", path);

			pImag = Read24BitBmpFile2Img(path);
			
			p_draw_info->x0	 =	0;
			p_draw_info->y0	 =	0;
			p_draw_info->width = pImag->width;
			p_draw_info->height= pImag->height;
			p_draw_info->color = RED;
			p_draw_info->pic   = pImag->imageData;
			
			fb_show_image(p_draw_info);
			
			free(pImag->imageData);
			free(pImag);

			break;

		case  IMGPNG:
			fprintf(stdout, "file %s is  PNG picture.\n", path);

			pImag = ReadPNGFile2Img(path);

			p_draw_info->x0  =	0;
			p_draw_info->y0  =	0;
			p_draw_info->width = pImag->width;
			p_draw_info->height= pImag->height;
			p_draw_info->color = RED;
			p_draw_info->pic   = pImag->imageData;
						
			fb_show_image(p_draw_info);
						
			free(pImag->imageData);
			free(pImag);
			
			break;
		
        default:fprintf(stderr, "file %s not image file!\n", path);
    }



	free(p_draw_info);
	
	fclose(imgFile);

	return 0;
	
}



















