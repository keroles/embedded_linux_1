/*
 * server.h
 *
 *  Created on: Dec 27, 2019
 *      Author: Mohamed Abo Raia
 */

#ifndef SERVER_H_
#define SERVER_H_

/*
 *        Function to send data to client
 *        
 * The function will open a socket and wait for a client to connect 
 * and send the data to him .
 *
 * @param  : char *data  The data to be sent .
 * @return : The function will return 0 if every thing done correctly 
 * and -1 otherwise.
 *
 */
int send_data(char *data);
/*
 *   Thread for reading data from the terminal
 *   
 * This thread will just acquire mutex will read the data from the terminal
 * then release the mutex and do it again and again .
 *  
 * @param  : pointer to void .
 * @return : pointer to void . 
 */
void* read_data_from_terminal(void*);
/*
 *   Thread for sending data to the client
 *   
 * This thread will just call the function send data and it will do the whole work .
 *  
 * @param  : pointer to void .
 * @return : pointer to void . 
 */
void* send_data_to_client(void *x);
/*
 *    Function to intilalize the server socket
 * 
 * The function will open a socket and bind the address and port number
 * to it and will go into listening state waiting for a client request   
 * 
 * @param  : The function will take nothing .
 * @return : The function will return the socket id .
 * 
 */
int* server_init(void) ;


#endif /* SERVER_H_ */
