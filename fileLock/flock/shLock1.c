/****************
SYNOPSIS
       #include <sys/file.h>
       int flock(int fd, int operation);

RETURN VALUE
       On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

       Apply  or  remove  an advisory lock on the open file specified by fd.  The argument operation is one of the
       following:

           LOCK_SH  Place a shared lock.  More than one process may hold a shared lock for a given file at a given
                    time.

           LOCK_EX  Place  an  exclusive  lock.  Only one process may hold an exclusive lock for a given file at a
                    given time.

           LOCK_UN  Remove an existing lock held by this process.

****************/
#include <sys/file.h>
#include <stdio.h>
#include<unistd.h>
int main(){
	char filePath[] = "./testFile";
	int fd = open(filePath, O_RDWR);

	printf("come into sh1.\n");
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
