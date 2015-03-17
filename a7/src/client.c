//Programmer's Name: Joe Martinez

#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int srvrFd, clntFd, clntAdrLen, i;
	struct sockaddr_in srvrAddr, clntAddr;
	char buf[256];

	srvrFd = socket(AF_INET, SOCK_STREAM, 0);
	if(srvrFd < 0){
		perror("socket");
		exit(1);
	}

	srvrAddr.sin_family = AF_INET;
	srvrAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvrAddr.sin_port = htons(6060);

	if(bind(srvrFd, (struct sockaddr *) &srvrAddr, sizeof(srvrAddr)) < 0){
		perror("bind");
		exit(1);
	}

	listen(srvrFd, 5);
	clntAdrLen = sizeof(clntAddr);
	while(1){
		printf("%s\n", "Program runs to line 37.....won't connect");
		printf("%s\n", "Waiting for connection...");
		clntFd = accept(srvrFd, (struct sockaddr*) &clntAddr, &clntAdrLen);
		printf("%s\n", "Program runs to line 39");
		if(fork() == 0){ //MAIN WORK IS DONE HERE
			i = recv(clntFd, buf, sizeof(buf), 0);
			send(clntFd, buf, i, 0);
			printf("%s\n", buf);
			close(clntFd);
			exit(0);
		}
		else{
			close(clntFd);
		}
	}
}