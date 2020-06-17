#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
//this is named pipe
int main(){
	char path[] = "testFifo";
	int fd = open(path, O_WRONLY);
	char buf[] = "hello";
	write(fd, buf, strlen(buf) + 1);
	return 0;
}
