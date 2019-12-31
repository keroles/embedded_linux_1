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
 * The function will open a socket and connect to a server and 
 * read the data in a global buffer.
 *
 * @param  : The function will take nothing .
 * @return : The function will return (0) if every thing done correctly 
 * and (-1) otherwise .
 *
 */
int recieve_data(void);
/*
 *                 Function to write data to an output file
 * The function will take a data from a buffer and 
 * write this data into an output file
 *
 * @param  : The function will take the address of the data .
 * @return : The function will return (0) if every thing done correctly 
 * and (-1) otherwise .
 *
 */
int write_data(char *data);
/*
 *   Thread for recieving data from the server
 *   
 * This thread will just call the function recieve_data().
 *  
 * @param  : pointer to void .
 * @return : pointer to void . 
 */

void* recieve_data_from_server(void *arg);
/*
 *   Thread for writing data into a file
 *   
 * This thread will just call the function write_data();
 *  
 * @param  : pointer to void .
 * @return : pointer to void . 
 */
void* write_data_in_afile(void *arg);
/*
 *   Function to intialize the client socket
 *   
 * The function will open a socket and add the information of the socket like 
 * port number and IP address and connect to the server.
 *  
 * @param  : The function will take nothing.
 * @return : The function will return (0) if every thing done correctly 
 * and (-1) otherwise .. 
 */
int client_init(void);
/*
 *   Function that will replace the default handler of SIGINT (quit signal)
 *   
 * This function will be invoked when the client quit with quit signal .
 * when the function invoked it will create a child process , in this child process
 * it will close the socket and the file and open the output file with gedit .
 * and the parent process will terminated. 
 *  
 * @param  : The function an integer.
 * @return : The function will return nothing to the caller.
 */
void signal_handler(int );


#endif /* CLIENT_H_ */
