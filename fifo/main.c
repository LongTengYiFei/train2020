#include<stdio.h>
#include"fifo.h"
struct SA{
	char a;
	char b;
	char c;
};
struct SB{
	char a;
	char b;
};
struct SC{
	char a;
};
int main(){
	int length = 20;
	struct FIFO f1;
	fifo_init(&f1, length);

	struct SA sa1;
	struct SB sb1;
	struct SC sc1;

	f1.set_item_length(&f1,sizeof(sa1));
	f1.in(&f1, &sa1);
	printf("used = %d\n",f1.used(&f1));	
	printf("avail = %d\n",f1.avail(&f1));	
	
	f1.set_item_length(&f1,sizeof(sb1));
	f1.in(&f1, &sb1);
	printf("used = %d\n",f1.used(&f1));	
	printf("avail = %d\n",f1.avail(&f1));

	f1.set_item_length(&f1,sizeof(sc1));
	f1.in(&f1, &sc1);
	printf("used = %d\n",f1.used(&f1));	
	printf("avail = %d\n",f1.avail(&f1));	
	return 0;
}
