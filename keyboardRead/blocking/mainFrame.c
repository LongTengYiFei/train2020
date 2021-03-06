#include <stdio.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEV_PATH "/dev/input/event2"
char keys1[10] = {'q','w','e','r','t','y','u','i','o','p'};//16 -25
char keys2[9] = {'a','s','d','f','g','h','j','k','l'};//30 - 38
char keys3[7] = {'z','x','c','v','b','n','m'};//44 - 50
int main()
{
	int fd;
	struct input_event t;
	fd=open(DEV_PATH, O_RDONLY);
	if(fd <= 0)
	{
		printf("open device error!\n");
		return -1;
	}

	while(1)
	{
		if(read(fd, &t, sizeof(t)) == sizeof(t))
		{
			if(t.type==EV_KEY)
				if(t.value==0 || t.value==1)
				{	
					if(t.code <= 25 && t.code >=16)
						printf("key %c %s\n", keys1[t.code - 16], (t.value) ? "down" : "up");
					if(t.code <= 38 && t.code >=30)
						printf("key %c %s\n", keys2[t.code - 30], (t.value) ? "down" : "up");
					if(t.code <= 50 && t.code >=44)
						printf("key %c %s\n", keys3[t.code - 44], (t.value) ? "down" : "up");
					if(t.code == KEY_ESC)
						break;
				}

		}
	}
	close(fd);
	return 0;
}


