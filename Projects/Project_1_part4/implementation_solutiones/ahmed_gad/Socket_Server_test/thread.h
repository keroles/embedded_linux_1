/*
 * thread.h
 *
 *  Created on: Dec 23, 2019
 *      Author: root
 */

#ifndef HEADER_THREAD_H_
#define HEADER_THREAD_H_

/*********************** includes **********************************/
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <errno.h>

#include "ethernet_socket.h"
#include "signal_handling.h"
/*********************** Definitions **********************************/
#define TIME_SIZE 		24
#define DATA_MAX_SIZE 	64
#define ID_MAX_SIZE     4
#define DLC_MAX_SIZE	2
#define PACKET_MAX_SIZE ID_MAX_SIZE+DLC_MAX_SIZE+DATA_MAX_SIZE + TIME_SIZE
#define REVERSE(ARR_NAME,ARR_INDX,ARR_LEN) for(uint8_t j = ARR_LEN - 1, idx=ARR_INDX,temp = 0;idx<j;idx++,j--){temp = ARR_NAME[j];ARR_NAME[j]=ARR_NAME[idx];ARR_NAME[idx]=temp;}

/*********************** Prototypes **********************************/
void * input_read(void * arg);
void * socket_server(void *arg);
void itos(unsigned char * s, int number);
/*********************** Decelerations *******************************/
#pragma pack(push,1)
struct packet_t {
	unsigned short ID;
	unsigned char DLC;
	char data[DATA_MAX_SIZE + TIME_SIZE];

} packet;
#pragma pack(pop)

typedef union {
	struct packet_t packet;
	char packetInBytes[sizeof(packet)];
} canPacket;

/****************************** externs *******************************/

extern canPacket recievedPacket;

extern pthread_mutex_t inputData_mutex;

extern unsigned char canPacketBuffer[PACKET_MAX_SIZE];
#endif /* HEADER_THREAD_H_ */
