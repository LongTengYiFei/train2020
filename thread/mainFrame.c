/*************************************************************************
1. Use the pthread library to complete multithreaded programming
2. Thread callback function, parameter passing, creating, waiting, ending
3. Communication between threads: mutual unlocking, semaphores, global variables
4. Thread priority
4. Thread local storage
Each thread can only print out some information at regular intervals, and observe the final output information of the process.
Adjust the thread priority and observe the process output information. 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void print_message (void *ptr);
__thread int tls_var1 = 0;
int var2 = 0;
pthread_t thread1, thread2;
int main()
{
    void *retval;
    char *message1 = "thread1";
    char *message2 = "thread2";

    int ret_thrd1, ret_thrd2;
	pthread_attr_t attr1;
	pthread_attr_t attr2;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
    ret_thrd1 = pthread_create(&thread1, &attr1, (void *)&print_message, (void *) message1);
    ret_thrd2 = pthread_create(&thread2, &attr2, (void *)&print_message, (void *) message2);

    if (ret_thrd1 != 0) {
        printf("thread1 create fail\n");
    } else {
        printf("thread1 create success\n");
    }
    if (ret_thrd2 != 0) {
        printf("thread2 create fail\n");
    } else {
        printf("thread2 create success\n");
    }

	//retval is **
	int j1 = pthread_join(thread1, &retval);
	printf("thread1 return value(retval) is %d\n", (int)retval);
	printf("thread1 return value(join) is %d\n", j1);
	if (j1 != 0) {
        	printf("cannot join with thread1\n");
	}
	printf("thread1 end\n");
	sleep(2);

	int j2 = pthread_join(thread2, &retval);
	printf("thread2 return value(retval) is %d\n", (int)retval);
	printf("thread2 return value(join) is %d\n", j2);
	if (j2 != 0) {
        	printf("cannot join with thread2\n");
	}
	printf("thread2 end\n");
   
	sleep(2);
	return 0;
}

void print_message( void *ptr ) {
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu,tid %lu\n",ptr, pid, tid);
    int i = 0;
    for (i; i<5; i++) {
        printf("%s:tls:%d\n", (char *)ptr, tls_var1++);//thread local storage
        printf("%s:%d\n", (char *)ptr, var2++);//normal
	sleep(1);
    }
	if(pthread_equal(tid, thread1))
		return (1);
	else if(pthread_equal(tid, thread2))
		pthread_exit(2);
	else 
		printf("not t1 or t2\n");
	
}
