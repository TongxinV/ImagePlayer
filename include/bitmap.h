#ifndef _BITMAP_H_
#define _BITMAP_H_


#include <c1image.h>

typedef unsigned char BYTE;  
typedef unsigned short WORD;  
typedef unsigned long DWORD;  
typedef long LONG; 

//λͼ�ļ�ͷ��Ϣ�ṹ����  
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��  
  
typedef struct tagBITMAPFILEHEADER {  
	//BYTE  bfType[2];			//�ļ����ͣ�"BM"(0x4D42)
	DWORD bfSize;           	//�ļ���С  
	WORD  bfReserved1;      	//�����֣�������  
	WORD  bfReserved2;      	//�����֣�ͬ��  
	DWORD bfOffBits;        	//ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��  
} BITMAPFILEHEADER;

//��ϢͷBITMAPINFOHEADER��Ҳ��һ���ṹ���䶨�����£�  
  
typedef struct tagBITMAPINFOHEADER{  
//public:  
	DWORD   biSize;             //ָ���˽ṹ��ĳ��ȣ�Ϊ40  
	LONG    biWidth;            //λͼ��  
	LONG    biHeight;           //λͼ��  
	WORD    biPlanes;           //ƽ������Ϊ1  
	WORD    biBitCount;         //������ɫλ����������1��2��4��8��16��24���µĿ�����32  
	DWORD   biCompression;      //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��  
	DWORD   biSizeImage;        //ʵ��λͼ����ռ�õ��ֽ���  
	LONG    biXPelsPerMeter;    //X����ֱ���  
	LONG    biYPelsPerMeter;    //Y����ֱ���  
	DWORD   biClrUsed;          //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)  
	DWORD   biClrImportant;     //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��  
} BITMAPINFOHEADER;



//��ɫ��Palette����Ȼ�������Ƕ���Щ��Ҫ��ɫ���λͼ�ļ����Եġ�24λ��32λ�ǲ���Ҫ��ɫ��ġ�  
//���ƺ��ǵ�ɫ��ṹ���������ʹ�õ���ɫ������  

typedef struct tagRGBQUAD {   
//public:  
	BYTE     rgbBlue; 			//����ɫ����ɫ����  
	BYTE     rgbGreen; 			//����ɫ����ɫ����  
	BYTE     rgbRed; 			//����ɫ�ĺ�ɫ����  
	BYTE     rgbReserved; 		//����ֵ  
} RGBQUAD;



void showBmpHead(BITMAPFILEHEADER* pBmpHead); 
void showBmpInfoHead(BITMAPINFOHEADER* pBmpInfoHead);
void showRgbQuan(RGBQUAD* pRGB);

int OpenBmpfile(const char* path);

C1Image* Read24BitBmpFile2Img(const char* path);

C1Image* SaveImage(char* path);

#endif
















