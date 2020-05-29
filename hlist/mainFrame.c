#include<stdio.h>
#include<stdlib.h>
#include"cyf_hlist.h"
#include<string.h>
struct A
{
        int key;
        int value;
        struct hlist_node list;  //this is the hash list 
};

static struct hlist_head A_list[16]; //16 entries
static unsigned int A_list_mask = 0x0F;

int main(){
	struct A * pA;
	int i;
	int j;
        memset(A_list, 0, sizeof(A_list));

	int num;
	//printf("Please input the num:");
	//scanf("%d",&num);
	num = 32;//default
        for(i = 0; i < num; i++)
        {
                pA = malloc(sizeof(struct A));
                pA->key = i;
                pA->value = 100 + i;
                hlist_add_head(&pA->list, &A_list[i & A_list_mask]);
        }
	//hash list address the same hash index confict
	//because this is head add, tou cha fa
	//first output key=16,then key=0,they are both hash index 0
	//the hash index 1,key=17 then key=1 and so on
        //Traverse the list
        printf("traverse the hash list\n");
        i = 0;
        j = 0;
        for( i = 0; i <= A_list_mask; i++)
        hlist_for_each_entry(pA, &A_list[i], list)
        {
                printf("num:%d\t,hash index:%d\t,key:%d\t,value:%d\t\n", j++, i, pA->key, pA->value);

        }

        //remove all items
        struct hlist_node *next;
        for( i = 0; i <= A_list_mask; i++)
        hlist_for_each_entry_safe(pA, next, &A_list[i], list)
        {
                printf("delete item: key: %d, value: %d\n", pA->key, pA->value);
                hlist_del_init(&pA->list); // put null to two pointers
                free(pA);
        }
}
