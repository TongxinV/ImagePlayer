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
	printf("λͼ�ļ�ͷ:\n");  
	printf("�ļ���С:%ld\n",pBmpHead->bfSize);  
	printf("������:%d\n",pBmpHead->bfReserved1);  
	printf("������:%d\n",pBmpHead->bfReserved2);  
	printf("ʵ��λͼ���ݵ�ƫ���ֽ���:%ld\n",pBmpHead->bfOffBits); 
}  


void showBmpInfoHead(BITMAPINFOHEADER* pBmpInfoHead)  
{  
	printf("λͼ��Ϣͷ:\n");  
	printf("�ṹ��ĳ���:%ld\n",pBmpInfoHead->biSize);  
	printf("λͼ��:%ld\n",pBmpInfoHead->biWidth);  
	printf("λͼ��:%ld\n",pBmpInfoHead->biHeight);  
	printf("biPlanesƽ����:%d\n",pBmpInfoHead->biPlanes);  
	printf("biBitCount������ɫλ��:%d\n",pBmpInfoHead->biBitCount);  
	printf("ѹ����ʽ:%ld\n",pBmpInfoHead->biCompression);  
	printf("biSizeImageʵ��λͼ����ռ�õ��ֽ���:%ld\n",pBmpInfoHead->biSizeImage);  
	printf("X����ֱ���:%ld\n",pBmpInfoHead->biXPelsPerMeter);  
	printf("Y����ֱ���:%ld\n",pBmpInfoHead->biYPelsPerMeter);  
	printf("ʹ�õ���ɫ��:%ld\n",pBmpInfoHead->biClrUsed);  
	printf("��Ҫ��ɫ��:%ld\n",pBmpInfoHead->biClrImportant);  
} 


void showRgbQuan(RGBQUAD* pRGB)  
{   
	printf("(%-3d,%-3d,%-3d)   ",pRGB->rgbRed,pRGB->rgbGreen,pRGB->rgbBlue);  
}  



int OpenBmpfile(const char* path)
{
	FILE* pfile = NULL;  

	pfile = fopen("tu004.bmp","rb");//��һ���������ļ����ļ�������ڣ�ֻ�����

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
		printf("��λͼΪ24λ���ɫ\n\n");

		bmpImg->width    = w = bmpInfoHeader.biWidth;
		bmpImg->height   = h = bmpInfoHeader.biHeight;
		bmpImg->channels = c = 3;
		bmpImg->imageData= (unsigned char*)malloc(sizeof(unsigned char)*w*3*h);

		/*û�����´���ֱ�Ӷ�������ͼƬ�ǵߵ���*/
		fseek(pFile,bmpFileHeader.bfOffBits,SEEK_SET);

		for(i=0;i<h;i++)  
        {
            if(fread(bmpImg->imageData+(h-1-i)*w*3,sizeof(BYTE),w*3,pFile)!=w*3)  
            {   
                fclose(pFile);
                free(bmpImg);   
                return NULL;  
            }  
            fseek(pFile,(3*w+3)/4*4-3*w,SEEK_CUR);   //��֪������Ϊ�Ρ�ȥ��Ҳ����ȷִ��
        }
	}

	
	fclose(pFile);
	
	return bmpImg;
}



C1Image* SaveImage(char* path)
{
	return NULL;
}

















