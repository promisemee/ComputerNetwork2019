//https://www.youtube.com/watch?v=LtXEMwSG5-8&feature=youtu.be

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){

	//creates server socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9001);
	server_address.sin_addr.s_addr  = INADDR_ANY;

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	//int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	//connects the socket referred by sockfd to addr
	//returns zero / -1, errno

	//check for error with the connection
	if (connection_status == -1){
		printf("Error\n");
	}
	else{
		//receive data from the server
		char server_response[256];
		recv(network_socket, &server_response, sizeof(server_response), 0);
		
		//print out the server's response
		printf("The server sent the data. %s", server_response);


	}
	
	//and then close the socket
	close(network_socket);

	return 0;
}