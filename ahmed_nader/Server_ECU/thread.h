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

#include "serial.h"
#include "ethernet_socket.h"
#include "signal_handling.h"

#define TIME_SIZE 		25
#define DATA_MAX_SIZE 	64
/*********************** Prototypes **********************************/
void * serial_read(void * arg);
void * data_validation(void * arg);
void * socket_server(void *arg);

/*********************** Definitions **********************************/
#define TIME_SIZE 		24
#define DATA_MAX_SIZE 	64

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

extern pthread_mutex_t serialData_mutex;
extern pthread_mutex_t dataValidation_mutex;

#endif /* HEADER_THREAD_H_ */
