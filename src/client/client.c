// UDP client

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
	int client_socket, port_num, n_bytes;
	char buffer[1024];
	struct sockaddr_in server_addr;
	socklen_t addr_size;

	// create UDP socket
	client_socket = socket(PF_INET, SOCK_DGRAM, 0);

	// configure settings in address struct
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(7891);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);  

	// initialize size variable to be used later on
	addr_size = sizeof server_addr;

	while(1) {
		printf("Type a sentence to send to server:\n");
		fgets(buffer, 1024, stdin);
		printf("You typed: %s", buffer);

		n_bytes = strlen(buffer) + 1;

		// send message to server
		sendto(client_socket, buffer, n_bytes, 0, (struct sockaddr *)&server_addr, addr_size);

		// receive message from server
		n_bytes = recvfrom(client_socket, buffer, 1024, 0, NULL, NULL);

		printf("Received from server: %s\n",buffer);
	}

	return 0;
}
