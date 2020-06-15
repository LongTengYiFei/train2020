
#include <sys/file.h>
#include <stdio.h>
#include<unistd.h>
int main(){
	char filePath[] = "./testFile";
	int fd = open(filePath, O_RDWR);

	printf("come into sh2.\n");
	int wait = 10;
	int rt_lock;
	rt_lock = flock(fd, LOCK_SH);
	if(rt_lock == 0)
		printf("sh lock success!\n");
	else 
		printf("sh lock fail!\n");
	
	sleep(wait);
		
	return 0;
}
