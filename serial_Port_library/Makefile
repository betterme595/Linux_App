CC :=arm-linux-gnueabihf-gcc

source:=Serial_test.c Sources/Serial_Port_Linux.c 

CFLAG += -I./Includes


all:
	$(CC) $(CFLAG) $(source) -o linux-serial-test

clean:
	rm  linux-serial-test
