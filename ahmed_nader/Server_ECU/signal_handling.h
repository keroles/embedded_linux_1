/*
 * signal_handling.h
 *
 *  Created on: Dec 24, 2019
 *      Author: root
 */

#ifndef SIGNAL_HANDLING_H_
#define SIGNAL_HANDLING_H_

/*********************** includes **********************************/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "serial.h"
#include "ethernet_socket.h"

/*********************** Prototypes **********************************/
void int_signal_handler(void *arg);

#endif /* SIGNAL_HANDLING_H_ */
