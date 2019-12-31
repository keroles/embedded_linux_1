/*
 * threads.h
 *
 *  Created on: Dec 24, 2019
 *      Author: Ahmed Gad
 */

#ifndef THREADS_H_
#define THREADS_H_

/*********************** includes **********************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

#include "ethernet_socket.h"


/*********************** Definitions ***********************/
#define TIME_SIZE 		24
#define DATA_MAX_SIZE 	64
#define ID_MAX_SIZE     4
#define DLC_MAX_SIZE	2
#define PACKET_MAX_SIZE ID_MAX_SIZE+DLC_MAX_SIZE+DATA_MAX_SIZE + (TIME_SIZE*2)
#define FILE_PATH "/home/embedded_system_ks/labs/Socket_Client_ECUB/Can_Log.txt"
/*********************** Decelerations ***********************/

extern pthread_mutex_t recvMutex;
extern int file_fd;
extern unsigned char canPacketBuffer[PACKET_MAX_SIZE];
/*********************** Prototypes **********************************/
void * Thread_WriteFile(void * arg);
void * Thread_SocketClient(void * arg);
void write_in_file(void);

#endif /* THREADS_H_ */
