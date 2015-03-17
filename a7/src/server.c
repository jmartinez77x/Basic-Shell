//Programmer's Name: Joe Martinez

#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char buf[80];
	int result, srvrFd, srvrLen;
	struct hostent *host;
	struct sockaddr_in srvrAddr;

	srvrFd = socket(AF_INET, SOCK_STREAM, 0);
	/*SET UP TCP SERVER'S ADDRESS*/
	srvrLen = sizeof(srvrAddr);
	memset(&srvrAddr, 0, srvrLen);
	srvrAddr.sin_port = htons(6060);
	if((host = gethostbyname("athena.ecs.csus.edu")) == NULL){
		printf("%s\n", "Host athena.ecs.csus.edu not found\n");
		exit(1);
	}
	srvrAddr.sin_addr = *(struct in_addr*) (host->h_addr);
	srvrAddr.sin_family = AF_INET;
	do{
		printf("%s\n", "Program runs to line 28...won't connect");
		printf("%s\n", "Waiting for connection...");
		result = connect(srvrFd, (struct sockaddr*) &srvrAddr, srvrLen);
		printf("%s\n", "Program runs to line 30");
		if(result == -1){
			sleep(1);
		}
	} while(result == -1);
	send(srvrFd, "Hello", strlen("Hello") + 1, 0);
	recv(srvrFd, buf, sizeof(buf), 0);
	printf("Client received %s\n", buf);
	close(srvrFd);
	
	return 0;
}