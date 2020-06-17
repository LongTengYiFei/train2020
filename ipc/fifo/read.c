#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
//this is named pipe
int main(){
	char path[] = "testFifo";
	int fd = open(path, O_RDONLY);
	char buf[100];
	read(fd, buf, 100);
	printf("read:%s\n",buf);	
	return 0;
}
