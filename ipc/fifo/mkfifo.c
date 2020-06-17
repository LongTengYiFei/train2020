#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
//this is named pipe
int main(){
	char path[] = "./testFifo";
	if(mkfifo(path, 0777) < 0){
		printf("mkfifo error\n");
	}
	return 0;
}
