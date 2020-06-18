#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
int main(){
	int mem_key = 	IPC_PRIVATE;
	int mem_size = 4096;
	int mem_id = shmget(mem_key, mem_size, 0666 | IPC_CREAT);
	if(mem_id == -1)
		printf("shmget error\n");
	printf("mem_id = %d\n",mem_id);

	void * mem_addr = shmat(mem_id, 0, SHM_RND);
	printf("the shared mem = %p\n", mem_addr);

	char buf[] = "hello";
	while(1){
		memcpy(mem_addr, buf, strlen(buf)+1);	
		sleep(1);
	}
	if(shmdt(mem_addr) == 0)
		printf("delete mem success\n");
	else 
		printf("delete mem fail\n");
	return 0;
}
