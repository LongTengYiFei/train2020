#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/time.h>
#include<sys/types.h>
#include<pthread.h>
// one cpu, one thread, 4G file, 4096 block size, cost 275s
const int block_size = 4096;
const int thread_capacity = 128 * 1024 * 1024;

int fileCopy(char *file1, char* file2){
	struct stat stat_buf;
	lstat(file1, &stat_buf);
	printf("best io block size = %d\n",stat_buf.st_blksize);
	printf("number of disk blocks allocated = %d\n",stat_buf.st_blocks);
	printf("file size = %d\n",stat_buf.st_size);

	DIR * p_DIR;  
    	struct dirent * p_dirent;  
	//dir detect
	if(S_ISDIR(stat_buf.st_mode)){
		printf("can not copy dir\n");
		return 0;
	}
	
	//file copy
	int fd1 = open(file1, O_RDONLY);//src
	int fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC);//dest
	char *cp_buf = (char *)malloc(sizeof(char) *block_size);
	int len = 0;

	//time cost	
	struct timeval start, end;
    	gettimeofday( &start, NULL );
	printf("start : %d.%d\n", start.tv_sec, start.tv_usec);

	float progress_maxLen = 40;//max number of #
	int progress_len = 0;//show number of #
	float copied_len = 0;
	float file_size = stat_buf.st_size;
	while((len = read(fd1, cp_buf, block_size)) > 0)
	{
		copied_len +=len;
		progress_len = (copied_len/file_size) * progress_maxLen;
		write(fd2, cp_buf, len);
		printf("\rNow progress:");
		while(progress_len --)
			printf("#");
	}
	printf("\n");

	gettimeofday( &end, NULL );
	printf("end   : %d.%d\n", end.tv_sec, end.tv_usec);
	int time_cost = end.tv_sec - start.tv_sec;
	int time_cost_u = end.tv_usec - start.tv_usec;
	//not very good
	printf("time cost %d s and %d us\n",time_cost, time_cost_u);
	printf("%s has been copied\n",file1);
	return 0;
}

int main(int argc, char* argv[]){
	int copyed_num = 0;
	int block_size;
	//my linux block size is 4096

	int c;
	char file1[100];
	char file2[100];
	strcpy(file1, argv[1]);
	strcpy(file2, argv[2]);

	fileCopy(file1, file2);
	return 0;
}