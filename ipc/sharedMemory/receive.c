#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
int main(){
	int mem_size = 0;
	int mem_id;
	printf("Please input mem_id:");
	scanf("%d",&mem_id);

	void * mem_addr = shmat(mem_id, 0, 0);
	printf("the shared mem = %p\n", mem_addr);

	char buf[100];
	while(1){
		memcpy(buf, mem_addr, strlen(mem_addr) +1);	
		printf("buf:%s\n",buf);
		sleep(1);
	}
	return 0;
}
