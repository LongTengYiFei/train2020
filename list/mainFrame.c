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
	struct A* pA2 = malloc(sizeof(struct A));	
	pA->key = 1;
	pA->value = 2;

	pB->a = '0';
	pB->b = '1';
	pB->c = '2';

	pC->ID = 123;
	
	pA2->key = 2;
	pA2->value = 4;
	//head add
	//tou cha fa	
	list_add(&pA->list, &A_list);
	list_add(&pB->list, &A_list);
	list_add(&pC->list, &A_list);
	list_add(&pA2->list, &A_list);

	list_for_each_entry(pA, &A_list, list)
	{
    		printf("value = %d\n",pA->value);
	}

	//remove all
	struct A *next;
	list_for_each_entry_safe(pA, next, &A_list, list) 
	{
    		free(pA);
	} 

	//will segment fault
	list_for_each_entry(pA, &A_list, list)
	{
    		printf("value = %d\n",pA->value);
	}


	printf("offsetof(A,key) = %ld\n",offsetof(struct A,key));
	printf("offsetof(A,value) = %ld\n",offsetof(struct A,value));
	return 0;
}
