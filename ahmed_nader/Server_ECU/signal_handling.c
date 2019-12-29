/*
 * signal_handling.c
 *
 *  Created on: Dec 24, 2019
 *      Author: root
 */

#include "signal_handling.h"

void int_signal_handler(void *arg) {

	printf("Alert !!!!\n");
	printf("Closing serial reading and socket server\n");

	close(server_fd);
	close(serial_fd);

	exit(0);
}
