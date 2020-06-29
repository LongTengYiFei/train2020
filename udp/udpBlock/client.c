#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include <arpa/inet.h>
void dg_cli(int sockfd, const struct sockaddr *pservaddr, socklen_t servlen){
	int n;
	char sendline[256], recvline[256];
	
	for(;;){
		printf("Please input your data:");
		scanf("%s",sendline);
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		n = recvfrom(sockfd, recvline, 256, 0, NULL, NULL);
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}

int main(){
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);	
	bzero(&servaddr, sizeof(servaddr));

	printf("Please input the server ip:");
	char server_ip[4*3+ 3+ 1];
	scanf("%s",server_ip);
	printf("server ip is %s\n",server_ip);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = 50000;
	inet_pton(AF_INET, server_ip, &servaddr.sin_addr);


	dg_cli(sockfd, (struct sockaddr *)&servaddr, sizeof(cliaddr));
	return 0;
}
