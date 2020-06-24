#include<fcntl.h>
#include<unistd.h>
int main(){
	int fd = open("./testFile1", O_WRONLY | O_APPEND);
	char a =1;
	for(int i=1;i<=65536;i++)
		write(fd, &a, 1);	

	return 0;
}
