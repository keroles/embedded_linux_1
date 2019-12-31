/*
 * main.c
 *
 *  Created on: Dec 26, 2019
 *      Author: Mohamed Abo Raia
 */




#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sched.h>
#include <pthread.h>
#include "server.h"



// buffer to hold the data
static char data[100] ;

pthread_mutex_t  mutex_1;



int main(void)
{

	pthread_t thread_1_id ;
	pthread_t thread_2_id ;

	// create two threads
	pthread_create(&thread_1_id, NULL, read_data_from_terminal, NULL);
    pthread_create(&thread_2_id, NULL, send_data_to_client, NULL);

    // join two the two threads to main
	pthread_join(thread_1_id, NULL);
	pthread_join(thread_2_id, NULL);


	// success
	return 0;
}


// send data to a client
int send_data(char *data)
{
	int temp ;
	int *socket_id ;
	int socket_cl ;

	time_t tx_time = 0;

	// initialize the server
	socket_id = server_init() ;

	socket_cl = *socket_id ;

	while (1)
	{
		sleep(2);
		
		// Acquire mutex
		pthread_mutex_lock(&mutex_1);
		
	    // calculate the tx time
	    tx_time = time(NULL);
	    
	    // send data to client
	    temp = write(socket_cl, data, strlen(data));
	    
	    // check for error
	    if (temp <= 0)
	    {
	      	perror("write");
	       	return -1;
	    }
	    
	    // release mutex
	    pthread_mutex_unlock(&mutex_1);


	}


    // success
	return 0;

}


// thread for reading data from the terminal
void* read_data_from_terminal(void *arg)
{
	while (1)
	{
		sleep(1) ;
		
		// Acquire mutex
		pthread_mutex_lock(&mutex_1);

	    // read the data from the terminal
		printf("Enter the data (max 100 char) : ");
		fgets(data, sizeof(data), stdin) ;
		
		// release the mutex
		pthread_mutex_unlock(&mutex_1);


	}

	return NULL;
}

// thread to send data to client
void* send_data_to_client(void *x)
{
    // send the data to the client
    send_data(data) ;

    return NULL ;

}

// function to initialize the server socket
int* server_init(void)
{

	int socket_id ;                       // to hold the socket id
    struct sockaddr_in server, client ;   // two structs to hold the data of the server and client
    int temp  = 0;
    static int socket_cl ;
    int len ;

    // acquire mutex
	pthread_mutex_lock(&mutex_1);

    // open a socket
    socket_id = socket(AF_INET, SOCK_STREAM, 0);

    // check if there is an error when openning the socket
    if (socket_id == -1)
    {
    	perror("socket");

    	return NULL;
    }

    printf("Server Starting..............\n");

    // initialize the struct with zero
    memset(&server, '0', sizeof(server));
    // initialize the struct with zero
    memset(&client, '0', sizeof(client));

    // calculate the size of client structure
    len = sizeof(client);

    // communication domain (Internet)
    server.sin_family = PF_INET ;
    // Attach a port number 500 to the socket
    server.sin_port = htons(9000);
    // make the socket available for all addresses
    server.sin_addr.s_addr = htonl(INADDR_ANY);



    // attach the the address an port number to the socket
    temp = bind(socket_id, (struct sockaddr *) &server, sizeof(server));

    //check for error
    if(temp < 0)
    {
    	perror("bind");

    	return NULL;
    }

    printf("Binding..............\n");

    // listen  for connections
    temp = listen(socket_id, 10);

    // check for error
    if (temp < 0)
    {
    	perror("listen");

    	return NULL;
    }

    printf("Listening..............\n");

    // accept connection from the client
    socket_cl = accept(socket_id, (struct sockaddr *) &client, &len);

    // check for error
    if (socket_cl < 0)
    {
      	perror("accept");

      	return NULL;
    }

    printf("Connection Established\n") ;
    
    // release mutex
    pthread_mutex_unlock(&mutex_1);
    // succcess
    return &socket_cl;

}
