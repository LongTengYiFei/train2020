#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include <string.h>
void travel(char *path){
	DIR *dp;
	struct dirent *dirp;

	if((dp = opendir(path)) == NULL)
		printf("can not open %s\n",path);

	struct stat buf;
        char * fileType;
	char *entry_name = (char*)malloc(sizeof(char) *100);	
	while((dirp = readdir(dp)) != NULL){
		if(strcmp(dirp->d_name, ".") == 0)
			continue;
		if(strcmp(dirp->d_name, "..") == 0)
			continue;
		printf("name:%s\n", dirp->d_name);
		//entry_name = path + dirp_name
		//absolate path
		strcpy(entry_name, path);
		strcat(entry_name, "/");
		strcat(entry_name, dirp->d_name);
                if(stat(entry_name, &buf) < 0)
                {
                        printf("error\n");
                        printf("----------\n");
                        continue;
                }
		int dir_flag = 0;
                if(S_ISREG(buf.st_mode))
                        fileType = "regular";
                else if(S_ISLNK(buf.st_mode))
                        fileType = "symbolic link";
                else if(S_ISDIR(buf.st_mode))
		{
                        fileType = "directory";
			dir_flag = 1;
		}
                else fileType = "unknown mode";
                printf("%s\n",fileType);
                printf("inode = %d\n",buf.st_ino);
                printf("device number = %d\n",buf.st_dev);
                printf("user ID of owner = %d\n",buf.st_uid);
                printf("size = %d\n",buf.st_size);
                printf("----------\n");
		
		if(dir_flag == 1)
			travel(entry_name);
			
	}

	return ;
}
int main(int argc, char *argv[]){
	//a directory
	if(argc != 2)
		printf("need arg\n");

	travel(argv[1]);	
	return 0;
}
