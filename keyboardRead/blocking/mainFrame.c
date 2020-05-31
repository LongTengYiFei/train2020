#include<stdio.h>
#include<string.h>
#include"cyf_kbRead.h"
#include<fcntl.h>
#include<linux/input.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#define CHECK_POINT
int main(){
	int fd = open("/dev/input/event2",O_RDONLY);
	#ifdef CHECK_POINT
	printf("fd = %d\n",fd);
	#endif
	struct input_event t;
	printf("size of t = %d\n",sizeof(t));
	while(1)
	{
		printf("while -\n");
		sleep(1);	
		int len = read(fd, &t, sizeof(t));
		if(len == sizeof(t))
		{	
			printf("read over\n");
			if(t.type==EV_KEY)
				if(t.value==0 || t.value==1)
				{
					printf("key %d %s\n", t.code, (t.value) ? "Pressed" : "Released");
					if(t.code == KEY_ESC)
						break;
				}
		}
		#ifdef CHECK_POINT
		printf("len = %d\n",len);
		#endif
	}
	return 0;
}