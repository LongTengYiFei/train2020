#include<stdio.h>
#include"fifo.h"
struct test{
	char a;
	char b;
	char c;
};
int main(){
	int length = 20;
	struct FIFO f1;
	fifo_init(&f1, length);
	f1.set_item_length(&f1, sizeof(struct test));

	struct test t1;
	struct test t2;

	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));

	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.in(&f1,&t1));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	printf("%d\n",f1.out(&f1,&t2));
	printf("used bytes = %d\n",f1.used(&f1));
	printf("avail bytes = %d\n",f1.avail(&f1));
	//printf("%d\n",sizeof(struct test));
	return 0;
}
