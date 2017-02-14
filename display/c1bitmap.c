/**
 *@Description:<p>BMP Analyze</p>
 *@author TongxinV
 *@time 2017-02-11 13:20:49 
 */


#include <stdio.h>
#include <stdlib.h>

#include <c1bitmap.h>



void showBmpHead(BITMAPFILEHEADER* pBmpHead)  
{  
	printf("位图文件头:\n");  
	printf("文件大小:%ld\n",pBmpHead->bfSize);  
	printf("保留字:%d\n",pBmpHead->bfReserved1);  
	printf("保留字:%d\n",pBmpHead->bfReserved2);  
	printf("实际位图数据的偏移字节数:%ld\n",pBmpHead->bfOffBits); 
}  


void showBmpInfoHead(BITMAPINFOHEADER* pBmpInfoHead)  
{  
	printf("位图信息头:\n");  
	printf("结构体的长度:%ld\n",pBmpInfoHead->biSize);  
	printf("位图宽:%ld\n",pBmpInfoHead->biWidth);  
	printf("位图高:%ld\n",pBmpInfoHead->biHeight);  
	printf("biPlanes平面数:%d\n",pBmpInfoHead->biPlanes);  
	printf("biBitCount采用颜色位数:%d\n",pBmpInfoHead->biBitCount);  
	printf("压缩方式:%ld\n",pBmpInfoHead->biCompression);  
	printf("biSizeImage实际位图数据占用的字节数:%ld\n",pBmpInfoHead->biSizeImage);  
	printf("X方向分辨率:%ld\n",pBmpInfoHead->biXPelsPerMeter);  
	printf("Y方向分辨率:%ld\n",pBmpInfoHead->biYPelsPerMeter);  
	printf("使用的颜色数:%ld\n",pBmpInfoHead->biClrUsed);  
	printf("重要颜色数:%ld\n",pBmpInfoHead->biClrImportant);  
} 


void showRgbQuan(RGBQUAD* pRGB)  
{   
	printf("(%-3d,%-3d,%-3d)   ",pRGB->rgbRed,pRGB->rgbGreen,pRGB->rgbBlue);  
}  



int OpenBmpfile(const char* path)
{
	FILE* pfile = NULL;  

	pfile = fopen("tu004.bmp","rb");//打开一个二进制文件，文件必须存在，只允许读

	if(NULL==pfile){ 
		printf("file %s open fail!\n", path);
		return -1;
	}
	printf("file %s open success..\n", path);

	fclose(pfile);

	printf("file %s close success..\n", path);

	return 0;
}



C1Image* Read24BitBmpFile2Img(const char* path)
{
	FILE* pFile;
	C1Image* bmpImg;
	unsigned short   fileType;  
	BITMAPFILEHEADER bmpFileHeader;  
	BITMAPINFOHEADER bmpInfoHeader;
	int c = 1;  	//channel
	int w = 0;  	//width
	int h = 0;  	//height
	int i = 0;
//	int offset = 0;
//	unsigned char pixVal;  
//	RGBQUAD* quad;  
	
	bmpImg = (C1Image*)malloc(sizeof(C1Image)); 
	/* Step 1 ...*/
	pFile = fopen(path, "rb");	
	if (!pFile){ 
		fprintf(stderr, "file %s open fail!\n", path);
		free(bmpImg);  
		return NULL;  
	}
	fprintf(stdout, "file %s open success..\n", path);

	/* Step 2.1 ...read file Type*/
	fread(&fileType, sizeof(unsigned short), 1, pFile);
	if (fileType != 0x4D42){
		printf("It's not bmp file! \n");
	}
	printf("It's bmp file! \n");	

	/* Step 2.2 ...read file Head*/
	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
	printf("=============================================\n"); 
	showBmpHead(&bmpFileHeader);

	/* Step 2.3 ...read info Head*/
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
	printf("=============================================\n");
	showBmpInfoHead(&bmpInfoHeader);

	if (bmpInfoHeader.biBitCount == 24)
	{
		printf("该位图为24位真彩色\n\n");

		bmpImg->width    = w = bmpInfoHeader.biWidth;
		bmpImg->height   = h = bmpInfoHeader.biHeight;
		bmpImg->channels = c = 3;
		bmpImg->imageData= (unsigned char*)malloc(sizeof(unsigned char)*w*3*h);

		/*没有以下处理，直接读出来的图片是颠倒的*/
		fseek(pFile,bmpFileHeader.bfOffBits,SEEK_SET);

		for(i=0;i<h;i++)  
        {
            if(fread(bmpImg->imageData+(h-1-i)*w*3,sizeof(BYTE),w*3,pFile)!=w*3)  
            {   
                fclose(pFile);
                free(bmpImg);   
                return NULL;  
            }  
            fseek(pFile,(3*w+3)/4*4-3*w,SEEK_CUR);   //不知其作用为何。去掉也能正确执行
        }
	}

	
	fclose(pFile);
	
	return bmpImg;
}



C1Image* SaveImage(char* path)
{
	return NULL;
}

















