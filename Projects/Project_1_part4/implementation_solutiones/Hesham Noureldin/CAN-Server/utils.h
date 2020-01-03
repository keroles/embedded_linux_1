/*
 * utils.h
 *
 *  Created on: Dec 26, 2019
 *      Author: embedded_system_ks
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024



void * Collect_Data();
void * Send_Data();
void Get_Tx_Time();
void kill_Process_Handller();
void Server_Socket_Connection_Establish();


#endif /* UTILS_H_ */
