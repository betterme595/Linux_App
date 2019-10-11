#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	printf("[%s]-[%d]\n", __func__, __LINE__);

	if(argc != 3){
		printf("Usage: %s [ip] [port]\n",argv[0]);
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));		//端口
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); //IP地址
//	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		perror("connect");
		return -1;
	}
	char buf[]="hello world\n";
	while(1){
		printf("client send\n");
		send(sock,buf,strlen(buf),0);	//阻塞函数,直到发送完毕或出错
//		write(sock, buf, sizeof(buf));
		fsync(sock);
//		flush(sock);
		sleep(1);
	}
	close(sock);
	return 0;
}
