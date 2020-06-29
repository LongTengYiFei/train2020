#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen){
	int n;
	socklen_t len;
	char mesg[256];

	for(;;){
		bzero(mesg, 256);
		len = clilen;
		n = recvfrom(sockfd, mesg, 256, 0, pcliaddr, &len);
		strcat(mesg, ":come from server\n");
		sendto(sockfd, mesg, strlen(mesg), 0, pcliaddr, len);
	}
}

int main(){
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);	
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = 50000;

	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
	return 0;
}
