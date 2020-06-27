#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static pthread_mutex_t lock1;
static int g_count = 0;

void *thread_fun_1(void *data)
{
    pthread_mutex_lock(&lock1);
    g_count++;
    printf("%s g_count: %d\n", __func__, g_count);
	//sleep(3);
    pthread_mutex_unlock(&lock1);
}

void *thread_fun_2(void *data)
{
	pthread_mutex_lock(&lock1);
    g_count++;
    printf("%s g_count: %d\n", __func__, g_count);
	//sleep(3);
	pthread_mutex_unlock(&lock1);
}

void *thread_fun_3(void *data)
{
    pthread_mutex_lock(&lock1);
    g_count++;
    printf("%s g_count: %d\n", __func__, g_count);
	//sleep(3);
    pthread_mutex_unlock(&lock1);
}

int main()
{
    int ret;
    pthread_t pid[3];

    ret = pthread_mutex_init(&lock1, NULL);
    if (ret != 0) {
        printf("mutex init failed\n");
        return -1;
    }

    pthread_create(&pid[0], NULL, thread_fun_1, NULL);
    pthread_create(&pid[1], NULL, thread_fun_1, NULL);
    pthread_create(&pid[2], NULL, thread_fun_1, NULL);
	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);
	pthread_join(pid[2], NULL);
       	pthread_mutex_destroy(&lock1);
    return 0;
}

