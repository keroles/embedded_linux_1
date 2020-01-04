/*

 * client_main.c
 *
 *  Created on: Dec 27, 2019
 *      Author: embedded_system_ks
 */

#include <sys/types.h>
#include <unistd.h>
#include "client_utils.h"


int ret;
void *res;
pthread_t dumpfile_thread;
pthread_t client_thread;

int main(int argc , char * argv[])
{
	printf(">>>>>>>>>>>>>>>>>>>>> Start Client Side <<<<<<<<<<<<<<<<<<<<<< \n \n");

	(void) signal(SIGINT,kill_Process_Handller);

    printf("-> Please Enter Server IP \n");
    scanf("%s",&IP_Address[0]);

    //Socket connection establish
    Client_Socket_Connection_Establish ();

    //create Threads
	ret = pthread_create(&dumpfile_thread,NULL,&Dump_Data,NULL);
	ret = pthread_create(&client_thread,NULL,&Receive_Data,NULL);


    pthread_join(dumpfile_thread,&res);
    pthread_join(client_thread,&res);

	return 0;
}

