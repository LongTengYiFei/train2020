#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main(){
	int listen_fd;
	struct sockaddr_in server_socket_address;
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_fd == -1)
	{
		printf("socket build error\n");
		return 0;
	}
	printf("socket build success.\n");

	server_socket_address.sin_family = AF_INET;//ipv4
	server_socket_address.sin_addr.s_addr = htonl(INADDR_ANY);//host to net
	server_socket_address.sin_port = 50000;

	if(bind(listen_fd, (struct sockaddr *)&server_socket_address, sizeof(server_socket_address)) == -1){
		printf("bind error\n");
		return 0;
	}
	printf("bind success\n");

	int backlog = 1;
	if(listen(listen_fd, backlog) == -1){
		printf("listen error\n");
		return 0;
	}
	printf("listen success\n");
	char buf[100];
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	int connection_fd = accept(listen_fd, (struct sockaddr *)&cliaddr, &len);
	if(connection_fd == -1){
		printf("accept error\n");
		return 0;
	}
	int num = 0;
	while(1){
		const char *client_ip = inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)); 
		uint16_t client_port = ntohs(cliaddr.sin_port);
		printf("connection from ip: %s, port: %d\n",client_ip, client_port);	
		sprintf(buf, "Hello,this is server!%d\n",num++);
		sleep(1);
		write(connection_fd, buf, strlen(buf));
	}
	return 0;
}
