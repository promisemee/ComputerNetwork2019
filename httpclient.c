//https://www.youtube.com/watch?v=mStnzIEprH8&feature=youtu.be

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
	
	char *address;		//server address
	address = argv[1];
	int portno;		//port number
	portno = atoi(argv[2]);
	if (argc<3){
		printf("ERROR, WRONG FORMAT	./httpclient IP_address port_number\n");
		exit(1);
	}

	//creates client socket
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address for server socket
	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(portno);
	inet_aton(address, &remote_address.sin_addr);

	//connecting to server client
	if (connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address))<0){
		error("ERROR connecting");		//wrong address
	}

	char request[] = "GET  /  HTTP/1.1\r\n\r\n";		//request message
	char response[4096];		//array to message from server

	send(client_socket, request, sizeof(request), 0);			//sends request to server
	recv(client_socket, &response, sizeof(response), 0);		//receives response from server

	printf("response from the server \n %s\n", response);		//prints response
	close(client_socket);											//close client socket

	return 0;
}