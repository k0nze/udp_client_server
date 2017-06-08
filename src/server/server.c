// UDP server

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>

int main() {
	int udp_socket, n_bytes;
	char buffer[1024];
	struct sockaddr_in server_addr, client_addr;
	struct sockaddr_storage server_storage;
	socklen_t addr_size, client_addr_size;
	int i;

	// create UDP socket
	udp_socket = socket(PF_INET, SOCK_DGRAM, 0);

	// configure settings in address struct
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(7891);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);  

	// bind socket with address struct
	bind(udp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

	// initialize size variable to be used later on
	addr_size = sizeof(server_storage);

	while(1) {
		/* try to receive any incoming UDP datagram. Address and port of 
		   requesting client will be stored on serverStorage variable 
		*/
		n_bytes = recvfrom(udp_socket, buffer, 1024, 0, (struct sockaddr *)&server_storage, &addr_size);

		// convert message received to uppercase
		for(i = 0; i < n_bytes-1; i++) {
			buffer[i] = toupper(buffer[i]);
		}

		// send uppercase message back to client, using serverStorage as the address
		sendto(udp_socket, buffer, n_bytes, 0, (struct sockaddr *)&server_storage, addr_size);
	}

	return 0;
}
