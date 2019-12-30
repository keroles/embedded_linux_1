/*
 * server.h
 *
 *  Created on: Dec 27, 2019
 *      Author: embedded_system_ks
 */

#ifndef SERVER_H_
#define SERVER_H_

/*
 *        Function to send data to client
 * The function will open a socket and wait for a client to connect and send the data to him .
 *
 * @param  : char *data  The data to be sent .
 * @return : The function will return 0 if every thing done correctly an -1 otherwise.
 *
 */
int send_data(char *data);
/*
 *       Function to read data from the terminal
 * The function will get a string from the terminal and store it in a buffer
 *
 * @param  : The function will take nothing.
 * @return : The function will return 0 if every thing done correctly and -1 otherwise.
 *
 */
int read_data(void);

void* read_data_from_terminal(void *x);
void* send_data_to_client(void *x);
int* server_init(void) ;


#endif /* SERVER_H_ */
