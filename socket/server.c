#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

typedef enum{
	PROCESS_OK  =  0,
	PROCESS_ERR = -1,
}ResultNum;

static int InitSocket(int *socket_fd_p)
{
	int ret = PROCESS_ERR;
	int socket_fd = -1;
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1234);		//端口
//	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP地址
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址

//	serv_addr.sin_family = AF_INET;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);//创建ipv4的socket,protocol=0:自动选择
	if( PROCESS_ERR == socket_fd ){
		printf("socket_fd:[%d]\n",socket_fd);
		return PROCESS_ERR;
	}

	*socket_fd_p = socket_fd;

	bind(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	return ret;
}

int main(int argc, char *argv[])
{
	int server_socket_fd;
	int read_size = 0;
	char read_buf[1024];
	char write_buf[]="test send";

	struct sockaddr_in client_addr;
	printf("[%s]-[%d]\n", __func__, __LINE__);
	InitSocket(&server_socket_fd);

	listen(server_socket_fd, 20);

	socklen_t client_addr_size = sizeof(client_addr);

	int client_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_addr_size);
	if( -1 == client_socket_fd){
		printf("client_socket_fd:[%d]\n",client_socket_fd);
	}
	printf("get a client,ip:[%s] , port:[%d]\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

	while(1){
		read_size = read(client_socket_fd, read_buf, sizeof(read_buf));
		if(read_size > 0){
			printf("client:%s",read_buf);
		}
		write(client_socket_fd,write_buf,sizeof(write_buf));
		sleep(1);
	}

	close(server_socket_fd);
	close(client_addr_size);
	return 0;
}
