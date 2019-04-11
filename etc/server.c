//https://www.youtube.com/watch?v=LtXEMwSG5-8&feature=youtu.be

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){

	char server_msg[255] = "You have reached the server\n";

	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	//int socket(int domain, int type, int protocol)
	//creates an endpoint for communication and returns a file descriptor
	//AF_INET == IPv4 protocols
	//SOCK_STREAM == Provides sequenced, reliable, two-way connection-based byte streams.
	//protocol specifies a particular protocol to be used with the socket
	//returns new socket, or else return -1

	//define server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;		//specifies which address family is being used
	server_address.sin_port = htons(9001);	//htons() : convets integer from host byte to network byte order
	server_address.sin_addr.s_addr = INADDR_ANY;	//IP address

	//bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
	//assigns the address 'addr' to 'sockfd'
	//"assigning a name to a socket"

	listen(server_socket, 5);	
	//int listen(sockfd, int backlog)
	//socket 'sockfd' will accpet incoming connection requests
	//backlog defines max length to queue of pending connections If full, client may receives error
	//returns success : zero else -1, errno

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	//int accept(int sockfd, struct sockaddr * addr, socklen_t *addrlen)
	//extracts the first connection request on the queue of pending connections, creates a new connected socket,
	//returns the a new file descriptor referring to the socket
	//blocks the caller until a connection is present

	//send the message
	send(client_socket, server_msg, sizeof(server_msg), 0);
	printf("%s", "Connected!\n");

	//close the socket
	close(server_socket);

	return 0;
}