#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/time.h>
#include<sys/types.h>
#include<pthread.h>
#include<signal.h>
#include <sys/stat.h>
// one cpu, one thread, 4G file, 4096 block size, cost 275s
const int block_size = 4096;
long long int_pos;
//version:interruptable file copy


//signal handler,write interrupt position to file
void sig_int(){
	printf("\n");
	printf("capture interrupt signal\n");
	printf("int_pos is%d\n", int_pos);
	int fd = open("./int_pos", O_WRONLY | O_CREAT | O_TRUNC);
	fchmod(fd, S_IRUSR | S_IWUSR | S_IXUSR);
	write(fd, &int_pos, sizeof(int_pos));

	exit(0);
}
//when file copy
//first search int_pos file
//if not exist,so this time is copy from start of src file
//if find int_pos file, read the int_pos,and lseek the src file
//and append write to the dest file
int fileCopy(char *file1, char* file2){
	signal(SIGINT, sig_int);
	struct stat stat_buf;
	lstat(file1, &stat_buf);

	DIR * p_DIR;  
    	struct dirent * p_dirent;  
	//dir detect
	if(S_ISDIR(stat_buf.st_mode)){
		printf("can not copy dir\n");
		return 0;
	}
	
	//file copy
	int fd_int_pos = open("./int_pos", O_RDONLY);
	long long this_int_pos;
	if(fd_int_pos== -1){
		printf("this is first copy this file!\n");
		this_int_pos = 0;
	}else{
		printf("continue to copy file!\n");
		read(fd_int_pos,&this_int_pos,sizeof(this_int_pos));	
	}

	int fd1 = open(file1, O_RDONLY);//src
	lseek(fd1, this_int_pos, SEEK_SET);

	int fd2 = open(file2, O_WRONLY | O_CREAT | O_APPEND);//dest
	fchmod(fd2, S_IRUSR | S_IWUSR | S_IXUSR);
	
	char *cp_buf = (char *)malloc(sizeof(char) *block_size);
	int len = 0;
	//time cost	
	float copied_len = this_int_pos;
	float file_size = stat_buf.st_size;
	while((len = read(fd1, cp_buf, block_size)) > 0)
	{
		write(fd2, cp_buf, len);
		copied_len +=len;
		int_pos = copied_len;//record interrupt position
	}
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]){
	//my linux block size is 4096

	char file1[100];
	char file2[100];
	strcpy(file1, argv[1]);
	strcpy(file2, argv[2]);

	fileCopy(file1, file2);
	return 0;
}
