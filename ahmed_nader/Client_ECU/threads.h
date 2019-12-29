/*
 * threads.h
 *
 *  Created on: Dec 24, 2019
 *      Author: embedded_system_ks
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

#define FILE_PATH "/home/nader/dataLog.txt"
/*********************** Decelerations ***********************/

#pragma pack(push,1)
struct packet_struct {
	unsigned short ID;
	unsigned char DLC;
	char data[DATA_MAX_SIZE + 2*TIME_SIZE];

}packet;
#pragma pack(pop)

typedef struct packet_struct packet_t;

typedef union {
	packet_t packet;
	char packetInBytes[sizeof(packet)];
} canPacket;

extern pthread_mutex_t recvMutex;
extern int file_fd;
extern canPacket receivedPacket;

/*********************** Prototypes **********************************/
void * Thread_WriteFile(void * arg);
void * Thread_SocketClient(void * arg);
void write_in_file(void);

#endif /* THREADS_H_ */
