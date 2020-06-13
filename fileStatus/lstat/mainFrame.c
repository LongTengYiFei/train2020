#include<sys/stat.h>
#include<stdio.h>
int main(int argc, char *argv[]){
	struct stat buf;
	char * fileType;

	for(int i=0; i<=argc -1; i++){
		printf("%s:\n",argv[i]);	
		if(lstat(argv[i], &buf) < 0)
		{
			printf("error\n");
			printf("----------");
			continue;
		}
		if(S_ISREG(buf.st_mode))
			fileType = "regular";
		else if(S_ISLNK(buf.st_mode))
			fileType = "symbolic link";
		else fileType = "unknown mode";
		printf("%s\n",fileType);
		printf("inode = %d\n",buf.st_ino);
		printf("device number = %d\n",buf.st_dev);
		printf("user ID of owner = %d\n",buf.st_uid);
		printf("size = %d\n",buf.st_size);
		printf("----------\n");
	}


	return 0;
}
