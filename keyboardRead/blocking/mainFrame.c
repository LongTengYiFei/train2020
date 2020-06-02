#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#define CHECK_POINT
int main(){
	int fd = open("/dev/input/event2",O_RDONLY | O_NONBLOCK);
	#ifdef CHECK_POINT
	printf("fd = %d\n",fd);
	#endif
	
	struct input_event t;
	printf("size of t = %d\n",sizeof(t));
	while(1){	
		int len = read(fd, &t, sizeof(t));
		#ifdef CHECK_POINT
		printf("len = %d\n",len);
		#endif
	}
	
	close(fd);
	return 0;
}
