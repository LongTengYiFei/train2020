#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <assert.h>

void show_policy (int policy)
{

    switch (policy)
    {
        case SCHED_FIFO:
            printf ("current policy = SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf ("current policy = SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf ("current policy = SCHED_OTHER\n");
            break;
        default:
            printf ("policy = UNKNOWN\n");
            break; 
    }
}

void show_priority (pthread_attr_t *attr,int policy)
{
    int priority = sched_get_priority_max (policy);
    assert (priority != -1);
    printf ("max_priority = %d\n", priority);
    priority = sched_get_priority_min (policy);
    assert (priority != -1);
    printf ("min_priority = %d\n", priority);
}

static int get_priority (pthread_attr_t *attr)
{
    struct sched_param param;
    int rs = pthread_attr_getschedparam (attr, &param);
    assert (rs == 0);
    printf ("priority = %d\n", param.__sched_priority);
    return param.__sched_priority;
}
int count = 0;
void test_fun1( void *ptr ) {
	for(int i=1;i<=5;i++)
	{
		count++;
		printf("%s count: %d\n", __func__, count);
		sleep(1);
	}
}
void test_fun2( void *ptr ) {
	for(int i=1;i<=5;i++)
	{
		count++;
		printf("%s count: %d\n", __func__, count);
		sleep(1);
	}
}
void test_fun3( void *ptr ) {
	for(int i=1;i<=5;i++)
	{
		count++;
		printf("%s count: %d\n", __func__, count);
		sleep(1);
	}
}
//pthread_attr_getschedpolicy()
//pthread_attr_setschedpolicy()
//
//
//need root to exec the program
int main(void)
{
	pthread_attr_t attr1;       
	pthread_attr_t attr2;       
	pthread_attr_t attr3;       
	struct sched_param sched;
	int rs;

	rs = pthread_attr_init (&attr1);
	assert (rs == 0);
	rs = pthread_attr_init (&attr2);
	assert (rs == 0);
	rs = pthread_attr_init (&attr3);
	assert (rs == 0);
	get_priority(&attr1);
	get_priority(&attr2);
	get_priority(&attr3);
	//------
	int inher = PTHREAD_EXPLICIT_SCHED; 
	pthread_attr_setinheritsched(&attr1, inher);  
	pthread_attr_setinheritsched(&attr2, inher);  
	pthread_attr_setinheritsched(&attr3, inher);  
	//------
	int policy;
	policy = SCHED_FIFO;
	pthread_attr_setschedpolicy(&attr1, policy);
	pthread_attr_setschedpolicy(&attr2, policy);
	pthread_attr_setschedpolicy(&attr3, policy);
	show_policy(policy);

	struct sched_param sp1;
	struct sched_param sp2;
	struct sched_param sp3;
	sp1.sched_priority = 99;
	sp2.sched_priority = 50;
	sp3.sched_priority = 1;

	pthread_attr_setschedparam(&attr1, &sp1);
	pthread_attr_setschedparam(&attr2, &sp2);
	pthread_attr_setschedparam(&attr3, &sp3);
	get_priority(&attr1);
	get_priority(&attr2);
	get_priority(&attr3);

	pthread_t pid[3];
	pthread_create(&pid[0], &attr1, test_fun1, NULL);
	pthread_create(&pid[1], &attr2, test_fun2, NULL);
	pthread_create(&pid[2], &attr3, test_fun3, NULL);
	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);
	pthread_join(pid[2], NULL);
	return 0;
}
