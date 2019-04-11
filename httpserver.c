#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void cleanExit(){
	//for rough exit(^C)
	exit(0);
}

char * parse(char buffer[]){		
	//parses request file from request message
	char *result = strchr(buffer, '/');
	if (result == NULL) 				//get message error
		error("ERROR");
	char *result2 = strtok(result, " ");
	if (strcmp("/", result2)==0) 	//ex. localhost:8000
		return "main.html";
	return result2+1;				//ex. localhost:8000/index.html --> index.html
}

void send_html(int socket, char* file){		
	//open and send file to client
	FILE *html_data;
	html_data = fopen(file, "r");
	if (html_data != NULL){
		char buffer[128];							//buffer for html file
		char response_data[2048]={'\0'};	
		while (fgets(buffer, sizeof(buffer), html_data)){	
			//for multi-line HTML file
			strcat(response_data, buffer);
		}

		//response message
		char http_header[4096] = "HTTP/1.1 2OO OK\r\n"
		"Connection:keep-alive\r\n"
		"Content-Type : text/html\r\n\n";
		strcat(http_header, response_data);

		//sends http header to client
		write(socket, http_header, sizeof(http_header));
	}
	else{	//no such html file, 404 ERROR
		html_data = fopen("404.html", "r");
		char buffer[128];	//buffer for html file
		char response_data[2048]={'\0'};	
		while (fgets(buffer, sizeof(buffer), html_data)){	//404 file
			strcat(response_data, buffer);
		}
		char http_header[4096] = "HTTP/1.1 404 Not Found\n\n";
		strcat(http_header, response_data);
		write(socket, http_header, sizeof(http_header));
	}
	fclose(html_data);
}

int main(int argc, char *argv[]){

	char buff_rcv[2048];		//buffer to receive message

	if (argc<2){		//check portnumber
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	//port number
	int portno;
	portno = atoi(argv[1]);

	//create server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket<0){
		error("ERROR opening socket");
	}

	//specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(portno);
	server_address.sin_addr.s_addr  = INADDR_ANY;

	//binding address to server socket
	if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0){
		error("ERROR bindng");
	}

	//listen connection message from client. Backlog queue is 5
	if (listen(server_socket, 5) == -1){
		error("listen");
	}

	//open client socket
	int client_socket;
	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);
	

	while(1){

		printf("\n------------Waiting for new concection------------\n\n");

		//creates client socket
		client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);
		if (client_socket == -1){
			perror("accept");
			continue;
		}
		//prints client IP address
		printf("server : got connection from : %s\n\n",inet_ntoa(client_address.sin_addr));

		//reads request message
		recv(client_socket, buff_rcv, sizeof(buff_rcv), 0);
		printf("%s", buff_rcv);

		//parses request message
		char * file = parse(buff_rcv);

		//sends requested file and response message
		if (file != "favicon.ico"){ 	// ignore favicon.ico
			send_html(client_socket, file);
		}

		signal(SIGINT, cleanExit);
		signal(SIGTERM, cleanExit);			//release port in rough exit
		close(client_socket);					//close client socket

	}

	return 0;
}

//Things to Do
//Report
//HTML files