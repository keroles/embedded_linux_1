/*
 * threads.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Ahmed Gad
 */
#include "threads.h"

pthread_mutex_t recvMutex;

unsigned char canPacketBuffer[PACKET_MAX_SIZE]={0};
int received_bytes = 0;
int file_fd = -1;

void * Thread_WriteFile(void *arg) {

	time_t Epoch_date = 0;

	file_fd = open(FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, 0774);

	if (file_fd == -1) {
		perror("File Open");
		exit(0);
	}
	while (1) {

		pthread_mutex_lock(&recvMutex);

		printf("File Opened waiting data...... \n");

		Epoch_date = time(NULL);

		memcpy(canPacketBuffer + strlen(canPacketBuffer),
				ctime(&Epoch_date), TIME_SIZE);

		write_in_file();
	}
}

void * Thread_SocketClient(void * arg) {

	ethernetSocketClient_init((char *) arg);

	while (1) {
		while (!received_bytes) {
			received_bytes = read(client_fd,canPacketBuffer,
					sizeof(canPacketBuffer));
		}
		memset(canPacketBuffer+ received_bytes, 0,
				sizeof(canPacketBuffer) - received_bytes);

		received_bytes = 0;

		//release mutex
		pthread_mutex_unlock(&recvMutex);
	}
}

void write_in_file(void) {


	int bufferIndex=0,tempIndex=0;
	//get ID
	for(bufferIndex=tempIndex+1;canPacketBuffer[bufferIndex]!='|';bufferIndex++);
	write(file_fd, "ID:", strlen("ID:"));
	write(file_fd,canPacketBuffer, bufferIndex+1);
	tempIndex=bufferIndex;

	//get DLC
	for(bufferIndex=tempIndex+1;canPacketBuffer[bufferIndex]!='|';bufferIndex++);
	write(file_fd, "DLC:", strlen("DLC:"));
	write(file_fd,canPacketBuffer+(tempIndex+1), bufferIndex-(tempIndex));
	tempIndex=bufferIndex;


	//get date
	for(bufferIndex=tempIndex+1;canPacketBuffer[bufferIndex]!='|';bufferIndex++);
	write(file_fd, "data:", strlen("data:"));
	write(file_fd,canPacketBuffer+(tempIndex+1), bufferIndex-(tempIndex));
	tempIndex=bufferIndex;

	//get Tx time
	for(bufferIndex=tempIndex+1;canPacketBuffer[bufferIndex]!='|';bufferIndex++);
	write(file_fd, "TX time:", strlen("TX time:"));
	write(file_fd,canPacketBuffer+(tempIndex+1), bufferIndex-(tempIndex));
	tempIndex=bufferIndex;

	//get Rx time
	write(file_fd, "RX time:", strlen("RX time:"));
	write(file_fd,canPacketBuffer+(tempIndex+1),TIME_SIZE);
	write(file_fd, "\n", strlen("\n"));
	write(file_fd,
			"----------------------------------------------------------------------------------------------",
			strlen(
					"----------------------------------------------------------------------------------------------"));
	write(file_fd, "\n", strlen("\n"));
}
