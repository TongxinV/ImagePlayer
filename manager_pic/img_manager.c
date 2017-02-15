#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>		//Linux C  �����ȡ�ļ���Ҫ�õ��ṹ��struct dirent
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "img_manager.h"



#define MAX_IMG_CNT 100



/* ����洢ͼƬ������
 * IMG���鱾���ǿյģ�   �ڳ����ʼ��ʱ����һ������Լ���õ�Ŀ¼
 * �ݹ�������е��ļ����ļ��н����е�ͼƬ��ʽ�ռ�����¼��������
 * ���������Լ����ڴ�ռ����mian����һ������һ�����������ڣ���ͬ����������ͬ
 */
static FileManageinfo images[MAX_IMG_CNT];
static unsigned int   image_index = 0;		//��¼���ڵ�ͼƬ����
static unsigned int   image_count = 0;		//��ǰ��ʾ��ͼƬ���


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

/* ɨ���Ѵ��ڵ�ͼƬ������Ϣ���浽����
 * readdir����ÿ����һ�ξͻ᷵��opendir�򿪵�basepathĿ¼�µ�һ���ļ���ֱ��
 * basepathĿ¼�������ļ���������֮�󣬾ͻ᷵��NULL(readdir��֧��nfs�ļ�ϵͳ)
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
			case DT_REG:			// ��ͨ�ļ�
			
				fprintf(stdout, "pathname = %s/%s\n",basepath, dirent_point->d_name);
				/* ���� */
				recodnise_add_image(base);
				break;
				
			case DT_DIR:			// �ļ���
			
				memset(base,'\0',sizeof(base));
				strcpy(base,basepath);
				strcat(base,"/");
				strcat(base,dirent_point->d_name);
				manager_init(base);
				
				break;
				
			case DT_UNKNOWN:		// ��ʶ����ļ���ʽ
			
				fprintf(stdout, "unknown file type.\n");
				break;
				
			default:
				break;
		}
	}

}



// ��lstat����ȡ�ļ����Բ��ж��ļ�����
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

		//���뵱ǰ���ļ�·��
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









//ɨ������õ�ĳһͼƬ��Ϣ
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

//�õ���һ��ͼƬ����Ϣ
FileManageinfo* get_next_imgfile(void)
{
	if(image_count == (image_index-1))
		return ExtractImgfile(image_count-1);
	
	return ExtractImgfile(image_count++);
}


//�õ���һ��ͼƬ����Ϣ
FileManageinfo* get_last_imgfile(void)
{

	if(image_count == 0)
		return ExtractImgfile(image_count);
	
	return ExtractImgfile(image_count--);
}









