#ifndef _IMG_MANAGER_H_
#define _IMG_MANAGER_H_

#include <linux/list.h>



#define LENPATHNAME 256

typedef enum tagfileType
{
	IMG_TYPE_JPEG,
	IMG_TYPE_BMP,
	IMG_TYPE_PNG,
	IMG_TYPE_UNKN,
}fileType_e;




typedef struct tagFileManageinfo{
	struct list_head list;
	char pathname[LENPATHNAME];
	fileType_e Type;
}FileManageinfo;



void manager_init(const char * basepath);

void manager_init2(const char * basepath);

FileManageinfo* ExtractImgfile(unsigned int index);


//FileManageinfo* get_next_imgfile(void);

//FileManageinfo* get_last_imgfile(void);

FileManageinfo* get_first_imgfile();

FileManageinfo* get_next_imgfile(FileManageinfo * c);

FileManageinfo* get_last_imgfile(FileManageinfo * c);


#endif

















