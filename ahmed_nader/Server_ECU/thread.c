/*
 * thread.c
 *
 *  Created on: Dec 23, 2019
 *      Author: Ahmed Nader
 */

#include "thread.h"

pthread_mutex_t serialData_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t dataValidation_mutex = PTHREAD_MUTEX_INITIALIZER;

static unsigned int bytes_read = 0;

void * serial_read(void * arg) {

	while (1) {
		printf(".....Inside serial_read thread.....\n");

		bytes_read = read(serial_fd, (char *) recievedPacket.packetInBytes,
				sizeof(recievedPacket.packetInBytes));
		//clear buffer
		memset(recievedPacket.packetInBytes + bytes_read, 0x00,
				sizeof(recievedPacket.packetInBytes) - bytes_read);
		//Echo received bytes again
		write(serial_fd, recievedPacket.packetInBytes, strlen(recievedPacket.packetInBytes));

		printf("received packet is = %s\nand number of bytes are %d\n",
				recievedPacket.packetInBytes, bytes_read);

		pthread_mutex_unlock(&serialData_mutex);
	}
}

void * data_validation(void * arg) {

	time_t Epoch_date = 0;

	while (1) {

		pthread_mutex_lock(&serialData_mutex);

		printf(".....Inside data_validation thread.....\n");

		if (((recievedPacket.packetInBytes[2] - '0')
				== strlen(recievedPacket.packetInBytes) - 3)
				&& ((recievedPacket.packetInBytes[2] - '0') == bytes_read - 3)) {

			printf("received data is valid\n");

			Epoch_date = time(NULL);

			memcpy(recievedPacket.packet.data + strlen(recievedPacket.packet.data),
					ctime(&Epoch_date), TIME_SIZE);

			pthread_mutex_unlock(&dataValidation_mutex);

		} else {

			printf("received data is not valid\nPlease try again\n");

		}

	}

}

void * socket_server(void *arg) {

	ethernetSocketServer_init();

	while (1) {

		pthread_mutex_lock(&dataValidation_mutex);

		printf("packet to be sent = %s\n", recievedPacket.packetInBytes);
		write(new_socket, recievedPacket.packetInBytes, strlen(recievedPacket.packetInBytes));

		printf("\n\n");

	}

}

