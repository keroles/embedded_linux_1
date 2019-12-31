/*
 * main.c
 *
 *  Created on: Dec 23, 2019
 *      Author: Ahmed Nader
 */

#include"pthread.h"
#include "thread.h"
#include "signal_handling.h"
#include "ethernet_socket.h"

canPacket recievedPacket;

pthread_mutex_t inputData_mutex;
int main(int argc, char * argv[]) {

	pthread_t input_thread;
	pthread_t socketServer_thread;


	pthread_mutex_lock(&inputData_mutex);

	(void) signal(SIGINT, int_signal_handler);

	if ((pthread_create(&input_thread, NULL, input_read, NULL)) < 0) {
		perror("input_thread_create");
		exit(0);
	}

	if ((pthread_create(&socketServer_thread, NULL, socket_server, NULL)) < 0) {
		perror("server_thread_create");
		exit(0);
	}
	pthread_join(input_thread, NULL);
	pthread_join(socketServer_thread, NULL);

}

