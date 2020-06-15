#include<fcntl.h>
#include<stdio.h>
int lock(int fd, int cmd, int type, int offset, int whence, off_t len){
	struct flock lock;

	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	return (fcntl(fd, cmd, &lock));
}
int main(){
	char filePath[] = "./testFile";
	int fd = open(filePath, O_RDWR);

	int rt_lock = lock(fd, F_SETLKW, F_RDLCK, 0, SEEK_SET, 0);
	if(rt_lock == 0)
		printf("read lock success!\n");

	int wait = 10;
	sleep(wait);
		
	return 0;
}
