/*
 * thread.c
 *
 *  Created on: Dec 23, 2019
 *      Author: Ahmed Nader
 *      Modified by:Ahmed Gad
 */

#include "thread.h"

unsigned char canPacketBuffer[PACKET_MAX_SIZE]={0};
unsigned char bufferIndex=0;

void * input_read(void * arg) {
	time_t Epoch_date = 0;
	printf(".....Inside input_read thread.....\n");
	while (1) {
		printf("\nID:");

		scanf("%d", &recievedPacket.packet.ID);
		if (recievedPacket.packet.ID > 2047) // means if ID large than 11 bit
				{
			printf("Invalid MSG ID");
			exit(0);
		}
		printf("DLC:");
		scanf("%d", &recievedPacket.packet.DLC);

		if (recievedPacket.packet.DLC > 64) // means if DLC large than 64
				{

			printf("Invalid DLC");
			exit(0);
		}
		printf("Data:");
		getc(stdin);// to skip new line
		scanf("%s",recievedPacket.packet.data);

		if(strlen(recievedPacket.packet.data)!=recievedPacket.packet.DLC){

					printf("Invalid data must be equal length of DLC\n DLC=%d and data length=%d",recievedPacket.packet.DLC,strlen(recievedPacket.packet.data));
					printf("\ndata:%s\n",recievedPacket.packet.data);
					exit(0);
				}
		recievedPacket.packet.data[strlen(recievedPacket.packet.data)]='|';
		//clear buffer
				memset(
						recievedPacket.packetInBytes
								+recievedPacket.packet.DLC+4, 0x00,
						sizeof(recievedPacket.packetInBytes)
								- recievedPacket.packet.DLC+4);



		// add Tx time to our packet
		Epoch_date = time(NULL);

		memcpy(recievedPacket.packet.data + recievedPacket.packet.DLC+1,
				ctime(&Epoch_date), TIME_SIZE);
		// make packet contains only assci
		itos(canPacketBuffer,recievedPacket.packet.ID);
		bufferIndex=strlen(canPacketBuffer);
		canPacketBuffer[bufferIndex++]='|';// seperate between ID and DLC

		itos(canPacketBuffer+bufferIndex,recievedPacket.packet.DLC);
		bufferIndex=strlen(canPacketBuffer);
		canPacketBuffer[bufferIndex++]='|';// seperate between DLC and data

		memcpy(canPacketBuffer+bufferIndex,recievedPacket.packet.data ,recievedPacket.packet.DLC+TIME_SIZE);
		bufferIndex=strlen(canPacketBuffer);
				canPacketBuffer[bufferIndex]='|';// seperate between Tx Time and Rx Time



		pthread_mutex_unlock(&inputData_mutex);
	}
}

void * socket_server(void *arg) {

	ethernetSocketServer_init();

	while (1) {

		pthread_mutex_lock(&inputData_mutex);
		write(new_socket, canPacketBuffer,
				strlen(canPacketBuffer));
	}

}
void itos(unsigned char * s, int number) {
	unsigned char index = 0, s_index = 0;
	if (!number) {
		s[index++] = '0';
		s[index] = 0;
		return;
	}
	if (number < 0) {
		s[index++] = '-';
		s_index++;
		number *= -1;
	}
	while (number > 0) {
		s[index++] = (number % 10) + 48;
		number /= 10;
	}
	if (index != 1) // to not call fn if number is only one digit
		REVERSE(s, s_index, index); //reverse(s, index, s_index);
	s[index] = 0;
}
