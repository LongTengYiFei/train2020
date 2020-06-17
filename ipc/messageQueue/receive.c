#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
#define MAX_SIZE 512
struct mymesg{
	long mytype;
	char mtext[MAX_SIZE];
};
int main(){
	char buf[100] = {0};
	struct mymesg data;
	int msgid = msgget(111,0777 | IPC_CREAT);
	if(msgid == -1){
		printf("msgget error\n");
		return 0;
	}
	int msg_type = 2;
	while(1){
		if(msgrcv(msgid, &data, MAX_SIZE, msg_type, IPC_NOWAIT) == -1){
			printf("message receive error\n");
			sleep(1);
		}
		printf("type = %ld\n",data.mytype);
		printf("content: %s\n",data.mtext);
	}
	return 0;
}
