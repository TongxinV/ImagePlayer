#ifndef _IMG_MANAGER_H_
#define _IMG_MANAGER_H_


#define LENPATHNAME 256

typedef enum tagfileType
{
	IMG_TYPE_JPEG,
	IMG_TYPE_BMP,
	IMG_TYPE_PNG,
	IMG_TYPE_UNKN,
}fileType_e;




typedef struct tagFileManageinfo{
	char pathname[LENPATHNAME];
	fileType_e Type;
}FileManageinfo;



void manager_init(const char * basepath);

void manager_init2(const char * basepath);

FileManageinfo* ExtractImgfile(int index);



#endif

















