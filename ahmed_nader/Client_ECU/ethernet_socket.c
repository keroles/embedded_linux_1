/*
 * ethernet_socket.c
 *
 *  Created on: Dec 27, 2019
 *      Author: root
 */

#include "ethernet_socket.h"

int client_fd = -1;

void ethernetSocketClient_init(const  char *IP) {

	struct sockaddr_in serv_addr;

	//set server parameters
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	// Create client socket
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket Creation:");
		exit(0);
	}
	printf("Socket no=%d\n", client_fd);
	if (connect(client_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
			< 0) {
		perror("Socket Connection:");
		exit(0);
	}
	printf("Connection established!!\n ");
}
