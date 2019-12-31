/*
 * ethernet_socket.c
 *
 *  Created on: Dec 23, 2019
 *      Author: Ahmed Nader
 */
#include "ethernet_socket.h"

int new_socket;
int server_fd;

void ethernetSocketServer_init(void) {

	struct sockaddr_in address;

	memset(&address, 0x00, sizeof(address));

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port
	if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 10) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, NULL, NULL)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
}

