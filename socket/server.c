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

	bind(socket_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	return ret;
}

int main(int argc, char *argv[])
{
	int server_socket_fd;
	struct sockaddr_in client_addr;
	printf("[%s]-[%d]\n", __func__, __LINE__);
	InitSocket(&server_socket_fd);

	listen(server_socket_fd, 20);

	socklen_t client_addr_size = sizeof(client_addr);

	int client_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_addr_size);

	close(server_socket_fd);
	close(client_addr_size);
	return 0;
}
