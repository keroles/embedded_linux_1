/*
 * ethernet_socket.h
 *
 *  Created on: Dec 23, 2019
 *      Author: Ahmed Nader
 */

#ifndef ETHERNET_SOCKET_H_
#define ETHERNET_SOCKET_H_

/*********************** includes **********************************/
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

/****************************** Definitions *******************************/
#define PORT 5454

/*********************** Prototypes **********************************/
void ethernetSocketServer_init(void);

/****************************** externs *******************************/
extern int new_socket;
extern int server_fd;
#endif /* ETHERNET_SOCKET_H_ */
