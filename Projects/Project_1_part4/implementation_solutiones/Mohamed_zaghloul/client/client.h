/*
 * client.h
 *
 *  Created on: Dec 27, 2019
 *      Author: embedded_system_ks
 */

#ifndef CLIENT_H_
#define CLIENT_H_
/*
 *                 Function to receive data from the server
 * The function will open a socket and connect to a server and read the data in a global buffer.
 *
 * @param  : The function will take nothing .
 * @return : The function will return (0) if every thing done correctly and (-1) otherwise .
 *
 */
int recieve_data(void);

int write_data(char *data);

void* recieve_data_from_server(void *arg);
void* write_data_in_afile(void *arg);
int client_init(void);
void signal_handler(int );


#endif /* CLIENT_H_ */
