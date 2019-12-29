/*
 * my_signals.c

 *
 *  Created on: Dec 24, 2019
 *      Author: embedded_system_ks
 */
#include "my_signals.h"

void int_Signal_handler(int signum) {

	pid_t pid = fork();

	if (pid > 0) {
		//parent code
		printf("Parent Process has been Killed\n");
		exit(1);

	} else if (!pid) {
		//child code
		printf("Closing Files and open Can Log file by Child Process!");

		close(file_fd);
		close(client_fd);
		execl("/usr/bin/gedit", "gedit", FILE_PATH, NULL);

		while (1) {
		}

	} else {
		perror("Fork:");
	}

}

