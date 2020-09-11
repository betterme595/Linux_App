#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <getopt.h>

#include "Serial_Port.h"

#include <string.h>
#include <errno.h>
extern int errno;

static const char *short_opts = "p:b:h?";
static const struct option longOpts[] = {
	{ "port", required_argument, NULL, 'p' },
	{ "baud", required_argument, NULL, 'b' },
	{ "help", no_argument, NULL, 'h' },
	{ NULL, no_argument, NULL, 0 }
};

void print_usage(char *file)
{
	printf("Usage:\n");
	printf("%s -p /dev/ttyPS0 -b 115200 \r\n", file);
}

int main(int argc, char *argv[])
{
	int opt = -1;
	int tty_fd = -1;
	char port[50];
	int baud = 115200;
	unsigned char flag = 0;
	unsigned char value = 20;
	char read_buffer[100];
	while( ( opt = getopt_long( argc, argv, short_opts, longOpts, NULL ) )!= -1 ) {
		switch( opt ) {
			case 'p':
				flag = 1;
				snprintf(port,sizeof(port), "%s",optarg);
				break;
			case 'b':
				baud = atoi(optarg);
				break;		
			case 'h':
					print_usage(argv[0]);
				break;	
			default:
				/* You won't actually get here. */
				break;
		}
	}	
	if (!flag){
		print_usage(argv[0]);
		return -1;
	}
	printf("port:%s baud:%d\r\n", port, baud);
	
	if( SerialPortOpen(port, baud, SERIAL_PORT_PARITY_NONE, &tty_fd) == 0){
		printf("[%s]-[%d]:SerialPortOpen\r\n", __func__, __LINE__ );
	}else{
		printf("[%s]-[%d]:mmap %s\r\n", __func__, __LINE__ ,strerror(errno));
	}
	
	SerialPortWriteByte(tty_fd, value);
	SerialPortWriteBuffer(tty_fd, "SerialPortWriteBuffer hello\r\n", sizeof("SerialPortWriteBuffer hello\r\n"));
	
	SerialPortReadBuffer(tty_fd, read_buffer,20);
	printf("%s\r\n",read_buffer);
	
	SerialPortClose(tty_fd);
}