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
	while(1){
		printf("Please input data:");
		scanf("%s",buf);
		data.mytype = 2;
		strcpy(data.mtext, buf);
		if(msgsnd(msgid, &data, MAX_SIZE, IPC_NOWAIT) == -1){
			printf("message send error\n");
			return 0;
		}
	}
	return 0;
}
