#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>		//Linux C  下面读取文件夹要用到结构体struct dirent
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "img_manager.h"



#define MAX_IMG_CNT 100



/* 定义存储图片的数组
 * IMG数组本来是空的，   在程序初始化时会在一个事先约定好的目录
 * 递归检索所有的文件及文件夹将所有的图片格式收集并记录在数组中
 * 而且它有自己的内存空间和在mian定义一个数组一样的生命周期，不同的是作用域不同
 */
static FileManageinfo images[MAX_IMG_CNT];
static unsigned int   image_index = 0;		//记录存在的图片数量
static unsigned int   image_count = 0;		//当前显示的图片序号


static int recodnise_add_image(const char * path)
{

	FILE * pFile;
	char type_buffer[8] = {0};
	
	if((pFile=fopen(path, "rb"))==NULL){
		fprintf(stderr, "file %s open fail!\n", path);
		return -1;
	}
	fprintf(stdout, "file %s open success..\n", path);


	if(fread(type_buffer, 1, 8, pFile)!=8){
		fprintf(stderr, "file read fail!\n");
		return -1;
	}

	if((0xff == type_buffer[0]) && (0xd8 == type_buffer[1]))
	{
		strcpy(images[image_index].pathname, path);
		images[image_index].Type = IMG_TYPE_JPEG;
		image_index++;
	}
	
	else if((0x42 == type_buffer[0]) && (0x4d == type_buffer[1]))
	{
		strcpy(images[image_index].pathname, path);
		images[image_index].Type = IMG_TYPE_BMP;
		image_index++;
	}
	
	else if((0x89 == type_buffer[0]) && (0x50 == type_buffer[1]))
	{
		strcpy(images[image_index].pathname, path);
		images[image_index].Type = IMG_TYPE_PNG;
		image_index++;
	}
	
	fclose(pFile);
	
	return 0;
	
}

/* 扫描已存在的图片，将信息保存到数组
 * readdir函数每调用一次就会返回opendir打开的basepath目录下的一个文件，直到
 * basepath目录下所有文件都被读完之后，就会返回NULL(readdir不支持nfs文件系统)
 */
void manager_init(const char * basepath)
{
	DIR* dir_point;
	struct dirent * dirent_point;
	char base[1024];

	if ((dir_point = opendir(basepath)) == NULL){
		fprintf(stderr, "Open dir %s error...", basepath);
		exit(1);
	}

	while ((dirent_point = readdir(dir_point)) != NULL)
	{
		if(strcmp(dirent_point->d_name, ".")==0 || strcmp(dirent_point->d_name, "..")==0)    ///current dir OR parrent dir
			continue;
			
		switch (dirent_point->d_type)
		{
			case DT_REG:			// 普通文件
			
				fprintf(stdout, "pathname = %s/%s\n",basepath, dirent_point->d_name);
				/* 处理 */
				recodnise_add_image(base);
				break;
				
			case DT_DIR:			// 文件夹
			
				memset(base,'\0',sizeof(base));
				strcpy(base,basepath);
				strcat(base,"/");
				strcat(base,dirent_point->d_name);
				manager_init(base);
				
				break;
				
			case DT_UNKNOWN:		// 不识别的文件格式
			
				fprintf(stdout, "unknown file type.\n");
				break;
				
			default:
				break;
		}
	}

}



// 用lstat来读取文件属性并判断文件类型
void manager_init2(const char * basepath)
{
	
	DIR* dir_point;
	struct dirent * dirent_point;
	char base[1024];
	struct stat sta;
	
	if ((dir_point = opendir(basepath)) == NULL){
		fprintf(stderr, "Open dir %s error...", basepath);
		exit(1);
	}

	while ((dirent_point = readdir(dir_point)) != NULL)
	{
		if(strcmp(dirent_point->d_name, ".")==0 || strcmp(dirent_point->d_name, "..")==0)    ///current dir OR parrent dir
			continue;

		//补齐当前打开文件路径
		memset(base,'\0',sizeof(base));
		strcpy(base,basepath);
		strcat(base,"/");
		strcat(base,dirent_point->d_name);
		
		lstat(base, &sta);

		if (S_ISREG(sta.st_mode))
		{	
			recodnise_add_image(base);
			
		}
		if (S_ISDIR(sta.st_mode))
		{
			manager_init2(base);
		}
	}
	
}









//扫描数组得到某一图片信息
FileManageinfo* ExtractImgfile(unsigned int index)
{	
	FileManageinfo* pInfo;
	
	if(index > image_index )
	{
		pInfo = &images[image_index];
	}
	else 
	{
		pInfo = &images[index];
	}

	return pInfo;
}

//得到下一张图片的信息
FileManageinfo* get_next_imgfile(void)
{
	if(image_count == (image_index-1))
		return ExtractImgfile(image_count-1);
	
	return ExtractImgfile(image_count++);
}


//得到上一张图片的信息
FileManageinfo* get_last_imgfile(void)
{

	if(image_count == 0)
		return ExtractImgfile(image_count);
	
	return ExtractImgfile(image_count--);
}









