#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
sem_t sem;
 
void *thread1()
{
	char msg[100] = {0};
	while (1)
	{
        	sem_wait(&sem);
        	strcat(msg, "a");
		printf("%s\n",msg);
	}
}
 
int main()
{
	pthread_t t1;
	int ret=sem_init(&sem, 0, 0);
	if (ret == -1) 
	{
        	printf("sem_init failed \n");
		return -1;
	}
	
	ret=pthread_create(&t1, NULL, thread1, NULL);
	if (ret != 0) 
	{
        	printf("pthread_create failed \n");
		return -1;
	}
	int sem_val = 0;
	while (1) 
	{
		for(int i=1;i<=3;i++){
			int wait = sem_getvalue(&sem, &sem_val);
			printf("sema_val = %d\n",sem_val);
			sleep(1);
		}	
		sem_post(&sem);
	}
	return 0;
}
