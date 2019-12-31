/*
 * main.c
 *
 *  Created on: Dec 23, 2019
 *      Author: embedded_system_ks
 */
#include "threads.h"
#include "my_signals.h"


int main(int argc, char * argv[]) {

	pthread_t clientSocket_thread;
	pthread_t dumpFile_thread;

	//acquire mutex
	pthread_mutex_lock(&recvMutex);
	//Create threads
	signal(SIGINT, int_Signal_handler);

	if (pthread_create(&clientSocket_thread, NULL, Thread_SocketClient, argv[1])
			< 0) {
		perror("clientSocket_thread");
		exit(0);
	}
	if (pthread_create(&dumpFile_thread, NULL, Thread_WriteFile, NULL) < 0) {
		perror("dumpFile_thread");
		exit(0);
	}

//join threads
	pthread_join(clientSocket_thread, NULL);
	pthread_join(dumpFile_thread, NULL);
}
