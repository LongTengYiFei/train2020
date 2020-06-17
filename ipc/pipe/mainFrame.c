#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main(){
	int read_num;
	int fd[2];
	int pid;
	char line[100];

	if(pipe(fd) < 0){
		printf("build pipe error\n");
	}
	//parent --> pipe --> child
	if((pid = fork()) > 0)//parent
	{	
		printf("come into parent\n");
		close(fd[0]);//close read
		char buf[] = "hehe";
		write(fd[1], buf, strlen(buf)+1);	
		printf("parent has wrote data\n");
	}else{//child
		int wait = 5;
		printf("come into child,child will wake up after %d seconds\n",wait);
		sleep(wait);
		close(fd[1]);//close write
		read_num = read(fd[0], line, 100);	
		printf("child read content:%s\n",line);
	}

	return 0;
}
