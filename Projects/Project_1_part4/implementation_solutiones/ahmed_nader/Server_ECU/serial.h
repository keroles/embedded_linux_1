
/*
 * serial.h
 *
 *  Created on: Jul 25, 2018
 *      Author: root
 */

#ifndef SERIAL_H_
#define SERIAL_H_

/*********************** includes **********************************/

#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <errno.h>   /* ERROR Number Definitions           */
#include <string.h>
#include <stdlib.h>


/*********************** Prototypes **********************************/
void serial_init(const char *serial_path);

/*********************** Decelerations ***********************/
extern int serial_fd; // file descriptor for serial



#endif /* SERIAL_H_ */
