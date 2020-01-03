/*
 * client_utils.h
 *
 *  Created on: Dec 27, 2019
 *      Author: embedded_system_ks
 */

#ifndef CLIENT_UTILS_H_
#define CLIENT_UTILS_H_


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 1024


void * Dump_Data();
void * Receive_Data();
void Get_Rx_Time();
void kill_Process_Handller();
void Write_Data_To_File();
void get_path();
void Client_Socket_Connection_Establish();


extern char IP_Address[25];

#endif /* CLIENT_UTILS_H_ */
