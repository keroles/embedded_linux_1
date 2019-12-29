/*
 * main.c
 *
 *  Created on: Dec 23, 2019
 *      Author: Ahmed Nader
 */

#include "serial.h"
#include "thread.h"
#include "signal_handling.h"
#include "ethernet_socket.h"

canPacket recievedPacket;

int main(int argc, char * argv[]) {

	pthread_t serial_thread;
	pthread_t dataValidation_thread;
	pthread_t socketServer_thread;

	serial_init(argv[1]);

	pthread_mutex_lock(&serialData_mutex);
	pthread_mutex_lock(&dataValidation_mutex);

	signal(SIGINT, int_signal_handler);

	if ((pthread_create(&serial_thread, NULL, serial_read, NULL)) < 0) {
		perror("serial_thread_create");
		exit(0);
	}
	if ((pthread_create(&dataValidation_thread, NULL, data_validation, NULL))
			< 0) {
		perror("dataValidation_thread_create");
		exit(0);
	}
	if ((pthread_create(&socketServer_thread, NULL, socket_server, NULL)) < 0) {
		perror("server_thread_create");
		exit(0);
	}
	pthread_join(serial_thread, NULL);
	pthread_join(dataValidation_thread, NULL);
	pthread_join(socketServer_thread, NULL);

}

