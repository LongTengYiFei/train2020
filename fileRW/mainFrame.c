#include<sys/mman.h>
#include<stdio.h>
#include<fcntl.h>
#include<assert.h>
#include<stdlib.h>


#define MAX_LENGTH 100
int printFile(const char *path){
	int fd = open(path, O_RDONLY);
	char *buf = (char *)malloc(MAX_LENGTH *sizeof(char));
	if(fd == -1)
	{
		printf("open file error\n");
	}else if(fd == 0)
	{	
		printf("open file,the file has reach the end\n");
	}
	else if(fd > 0)
	{	
		lseek(fd, 0, SEEK_SET);
		int length = read(fd, buf, MAX_LENGTH);
		printf("The file content:");
		for(int i = 0; i<= length-1; i++)
			printf("%c",buf[i]);
		printf("\n");	
	}else assert(0);
	

	return 0;
}
int main(){
	//1.open flag test
	int fd;
	char filePath[] = "./testFile";

	fd = open(filePath, O_WRONLY);
	char testStr[] = "123";
	write(fd, testStr, sizeof(testStr));
	close(fd);
	printFile(filePath);

	fd = open(filePath, O_WRONLY);
	char testStr2[] = "234";
	write(fd, testStr2, sizeof(testStr2));
	close(fd);
	printFile(filePath);
		
	fd = open(filePath, O_WRONLY | O_APPEND);
	char testStr3[] = "345";
	write(fd, testStr3, sizeof(testStr3));
	close(fd);
	printFile(filePath);

	remove(filePath);
	printf("the file %s has been removed\n", filePath);	
	
	printf("now to test creat flag. ");
	fd = open(filePath, O_WRONLY | O_CREAT, O_WRONLY);
	char testStr4[] = "12345";
	write(fd, testStr4, sizeof(testStr4));
	close(fd);
	printFile(filePath);

	printf("now to test truncate flag. ");
	fd = open(filePath, O_WRONLY | O_TRUNC);
	char testStr5[] = "345";
	write(fd, testStr5, sizeof(testStr5));
	close(fd);
	printFile(filePath);
	//2.according to command line argument ,to write the specific position of file
	
	//3.use mmap to read or write the file
	//
	printf("now to test mmap.\n");
	fd = open(filePath, O_RDWR);
	char *buf;
	int mmap_length = 100;
	//shared flag test
        buf = (char *)mmap((void *) NULL, mmap_length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	buf[0] = 'b';
	buf[1] = 'a';
	buf[2] = 'a';
	munmap(buf, mmap_length);
	
	//private flag test
        buf = (char *)mmap((void *) NULL, mmap_length, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	buf[0] = 'a';
	buf[1] = 'b';
	buf[2] = 'c';
	return 0;
}
