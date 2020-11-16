#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	int fd = open("./testFile1", O_CREAT | O_WRONLY);
	//test 128MB file
	char *a = malloc(1024);
	for(int i=0;i<=1023;i++){
		a[i] = 't';
	}
	printf("%d\n", sizeof(a));
	for(int i=1;i<=128*1024;i++)
		write(fd, a, 1024);	

	return 0;
}
