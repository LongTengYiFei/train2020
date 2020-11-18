#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/time.h>
#include<sys/types.h>
#include<pthread.h>
//version:multi process
const int block_size = 128 * 1024;

int fileCopy(char *file1, char* file2, int p_num){
	struct stat stat_buf;
	lstat(file1, &stat_buf);

	DIR * p_DIR;  
    	struct dirent * p_dirent;  
	//dir detect
	if(S_ISDIR(stat_buf.st_mode)){
		printf("can not copy dir\n");
		return 0;
	}
	
	//
	int fd1 = open(file1, O_RDONLY);//src
	int fd2 = open(file2, O_WRONLY | O_CREAT);//dest
	float file_size = stat_buf.st_size;
	ftruncate(fd2, file_size);	
	//two process , eazy model
	//offset compute
	int offset = 0;
	if(p_num==0){
		offset = 0;
	}else{
		offset = file_size/2;
	}

	//set open file pointer
	lseek(fd1, offset, SEEK_SET);	
	lseek(fd2, offset, SEEK_SET);	

	int len = 0;
	float progress_maxLen = 10;//max number of #
	int progress_len = 0;//show number of #
	float copied_len = 0;
	
	char *cp_buf = (char *)malloc(sizeof(char) *block_size);
	
	//如果是从中间开始读取文件的，采用read 0 则结束的判断方式没问题
	//可是如果是从0开始读取文件，我们只需要读取一半的文件
	//则不能采用read 0结束
	if(p_num==0){
		//compute copy number
		int copy_num = file_size/block_size/2;
		while(copy_num>0){
			read(fd1, cp_buf, block_size);
			copied_len +=len;
			progress_len = (copied_len/file_size) * progress_maxLen;
			write(fd2, cp_buf, len);
			printf("\rNow progress:");
			while(progress_len --)
				printf("#");
		}		
	}else{	
		while((len = read(fd1, cp_buf, block_size)) > 0)
		{
			copied_len +=len;
			progress_len = (copied_len/file_size) * progress_maxLen;
			write(fd2, cp_buf, len);
			printf("\rNow progress:");
			while(progress_len --)
				printf("#");
		}
	}	
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]){
	char file1[100];
	char file2[100];
	char p_num[1];
	strcpy(file1, argv[1]);
	strcpy(file2, argv[2]);
	strcpy(p_num, argv[3]);

	fileCopy(file1, file2, p_num[0]-'0');
	return 0;
}
