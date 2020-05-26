#include"cyf_list.h"
#include<stdio.h>
#include<stdlib.h>
struct A{
	//data area
	int key;    
	int value;

	//pointer area
	struct list_head list;
};

struct B{
	//data area
	char a;
	char b;
	char c;    

	//pointer area
	struct list_head list;
};

struct C{
	//data area
	int ID;

	//pointer area
	struct list_head list;
};
int main(){
	struct list_head A_list = {&A_list, &A_list};
	struct A* pA = malloc(sizeof(struct A));	
	struct B* pB = malloc(sizeof(struct B));
	struct C* pC = malloc(sizeof(struct C));
	pA->key = 1;
	pA->value = 2;

	pB->a = '0';
	pB->b = '1';
	pB->c = '2';

	pC->ID = 123;
	//head add
	//tou cha fa	
	list_add(&pA->list, &A_list);
	list_add(&pB->list, &A_list);
	list_add(&pC->list, &A_list);
	
	printf("offsetof(A,key) = %ld\n",offsetof(struct A,key));
	printf("offsetof(A,value) = %ld\n",offsetof(struct A,value));
	return 0;
}
