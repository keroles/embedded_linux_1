/*
 * threads.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Ahmed Nader
 */
#include "threads.h"

pthread_mutex_t recvMutex;

int received_bytes = 0;
int file_fd = -1;

void * Thread_WriteFile(void *arg) {

	time_t Epoch_date = 0;

	file_fd = open(FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, 0744);

	if (file_fd == -1) {
		perror("File Open");
		exit(0);
	}
	while (1) {

		pthread_mutex_lock(&recvMutex);

		printf("File Opened waiting data...... \n");

		Epoch_date = time(NULL);

		memcpy(receivedPacket.packet.data + strlen(receivedPacket.packet.data),
				ctime(&Epoch_date), TIME_SIZE);

		printf("writing : %s\n\n",receivedPacket.packetInBytes);


		 write_in_file();
	}
}

void * Thread_SocketClient(void * arg) {

	 ethernetSocketClient_init((char *)arg) ;

	while (1) {
		while (!received_bytes) {
			received_bytes = read(client_fd, receivedPacket.packetInBytes,
					sizeof(receivedPacket.packetInBytes));
		}
		memset(receivedPacket.packetInBytes + received_bytes, 0,
				sizeof(receivedPacket.packetInBytes) - received_bytes);

		printf("received packet: %s\nand number of bytes are %d\n",
				receivedPacket.packetInBytes, received_bytes);

		received_bytes = 0;

		//release mutex
		pthread_mutex_unlock(&recvMutex);
	}
}
void write_in_file(void){


	write(file_fd ,"ID = ",strlen("ID = "));
	write(file_fd, &receivedPacket.packet.ID,sizeof(receivedPacket.packet.ID));
	write(file_fd, "\n", strlen("\n"));

	write(file_fd ,"DLC = ",strlen("DLC = "));
	write(file_fd, &receivedPacket.packet.DLC,sizeof(receivedPacket.packet.DLC));
	write(file_fd, "\n", strlen("\n"));

	write(file_fd ,"data = ",strlen("data = "));
	write(file_fd, receivedPacket.packet.data,receivedPacket.packet.DLC -'0'	);
	write(file_fd, "\n", strlen("\n"));

	write(file_fd ,"TX time = ",strlen("TX time = "));
	write(file_fd, receivedPacket.packet.data+receivedPacket.packet.DLC -'0'	,TIME_SIZE	);
	write(file_fd, "\n", strlen("\n"));


	write(file_fd ,"RX time = ",strlen("RX time = "));
	write(file_fd, receivedPacket.packet.data+receivedPacket.packet.DLC -'0'+TIME_SIZE,TIME_SIZE	);
	write(file_fd, "\n", strlen("\n"));

	write(file_fd, "=======================================", strlen("======================================="));
	write(file_fd, "\n", strlen("\n"));
}
