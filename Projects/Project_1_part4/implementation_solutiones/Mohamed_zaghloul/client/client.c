/*
 * main.c
 *
 *  Created on: Dec 26, 2019
 *      Author: Mohamed Abo Raia
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sched.h>
#include <pthread.h>
#include "client.h"
#include <signal.h>

// buffer to hold the data
static char data[100] = {'0'} ;

pthread_mutex_t  mutex_1;
static int socket_id ;
static int output_file_id;




int main(int argc, char *argv[])
{

	pthread_t thread_1_id ;
	pthread_t thread_2_id ;

	// create two threads
	pthread_create(&thread_1_id, NULL, recieve_data_from_server, NULL);
    pthread_create(&thread_2_id, NULL, write_data_in_afile, NULL);

    // change the default signal handler
    signal(SIGINT, signal_handler);

    // join two the two threads to main
	pthread_join(thread_1_id, NULL);
	pthread_join(thread_2_id, NULL);




    // success
    return 0;
}



// function to receive data from server
int recieve_data(void)
{

    int temp  = 0;
    time_t rx_time ;


    client_init();



    while (1)
    {

    	pthread_mutex_lock(&mutex_1);

        // receive data from server
        temp = read(socket_id, data, sizeof(data) -1);

       /* printf("%s\n", data);

	    rx_time = time(NULL);

	    printf("time : %s",  ctime(&rx_time));*/

        pthread_mutex_unlock(&mutex_1);

        sleep(1);


    }


    // check for error
    if (temp < 0)
    {
    	perror("read");

    	return -1;
    }

    //close the socket
    close(socket_id);


    // success
	return 0;

}

// function to store data in a file
int write_data(char *data)
{

	int ret_2 ;


    // open the output file
    output_file_id = open("output_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0744);

    // check for error
    if (output_file_id == -1)
    {
    	perror("output file open");
    	return -1;
    }

    while (1)
    {
        sleep(2);

    	pthread_mutex_lock(&mutex_1);
        // write data in the file
        ret_2 = write(output_file_id, (void *) data, strlen(data));

        //memset(&data, '0', sizeof(data));

        pthread_mutex_unlock(&mutex_1);

    }



	// check for error
	if (-1 == ret_2)
	{
		perror("write");

		close(output_file_id);

		return -1 ;
	}


	// close the output file
	close(output_file_id);


	//success
	return 0;
}

void* recieve_data_from_server(void *arg)
{

	int temp ;


    // Receive data from the server
    temp = recieve_data() ;


    // check for error
    if (temp == -1)
    {
        perror("Receive data");
        return NULL;
    }


    return NULL ;


}

void* write_data_in_afile(void *arg)
{

	// store the data in a file
	write_data(data);

	return NULL;
}

int client_init(void)
{

    struct sockaddr_in client ;
    int temp  = 0;

    // open a socket
    socket_id = socket(PF_INET, SOCK_STREAM, 0);

    // check if there is an error when opening the socket
    if (socket_id == -1)
    {
    	perror("socket");

    	return -1;
    }

    // initialize the struct with zero
    memset(&client, '0', sizeof(client));

    printf("Client starting......\n");



    // communication domain (Internet)
    client.sin_family = AF_INET ;
    // Attach a port number 500 to the socket
    client.sin_port = htons(9000);
    // add the client IP
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect to the server
    temp = connect(socket_id, (struct sockaddr *) &client, sizeof(client)) ;

    // check for error
    if (temp < 0)
    {
    	perror("connect");

    	return -1;
    }

    printf("Connected\n");


    printf("Receiving data.........\n");

    // success
    return 0;

}

void signal_handler(int arg)
{
	int temp = 0;

	pid_t pid ;

	pid = fork() ;

	// for the parent process
	if (pid > 0)
	{
		// exit
		exit(0);
	}
	// for the child process
	else if (pid == 0)
	{
	    //close the socket
	    close(socket_id);

		// close the output file
		close(output_file_id);



		temp = execl("/usr/bin/gedit", "gedit", "output_file.txt", NULL); ;

		if (temp < 0)
		{
			perror("execl");
		}

	}

	else
	{
		perror("fork");
	}


}
