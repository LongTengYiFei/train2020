#include<pthread.h>
#include<stdio.h>
#include<assert.h>
int i = 1;
void thread1(void * data){
	printf("%s\n",__func__);
	i++;
}
void thread2(void * data){
	printf("%s\n",__func__);
	i--;
}
int main(){
	pthread_t t[2];
	pthread_create(&t[0], NULL, thread1, NULL);
	pthread_create(&t[1], NULL, thread2, NULL);
	usleep(1);
	printf("i = %d\n",i);
	printf("the i will vary among 0 or 1 or 2\n");
	return 0;
}
