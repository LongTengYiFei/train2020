#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
	printf("Please input the server ip:");
	char server_ip[4*3+ 3+ 1];
	scanf("%s",server_ip);
	printf("server ip is %s\n",server_ip);
	
	//ipv4, bytes stream 
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		printf("socket build error\n");
		return 0;
	}
	printf("socket build success.\n");

	struct sockaddr_in server_socket_address;
	bzero(&server_socket_address, sizeof(server_socket_address));
	server_socket_address.sin_family = AF_INET;
	uint16_t server_port = 50000;
	server_socket_address.sin_port = server_port;
	
	//presentation to numeric
	int pton_rt = inet_pton(AF_INET, server_ip, &server_socket_address.sin_addr);
	if(pton_rt == 0)
	{
		printf("your ip format is not valid\n");
		return 0;
	}else if(pton_rt == -1)
	{
		printf("pton error\n");
		return 0;
	}
	printf("pton success\n");	
	//the second pointer must trans to general sockett address
	//here is ipv4 to general
	if(connect(socket_fd, (struct sockaddr *)&server_socket_address, sizeof(server_socket_address)) == -1)
	{
		printf("connect error\n");
		return 0;
	}
	printf("connection success!\n");
	char receive_buff[200];
	int n = read(socket_fd, receive_buff, 200);
	while(n >= 0){
		receive_buff[n] = '\0';
		sleep(5);
		printf("receive_buff:%s",receive_buff);	
		n = read(socket_fd, receive_buff, 200);
	
	}
	if(n < 0)
		printf("read socket error\n");
	return 0;
}
