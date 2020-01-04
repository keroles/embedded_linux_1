/*

 * server_main.c
 *
 *  Created on: Dec 26, 2019
 *      Author: embedded_system_ks
 */

#include <sys/types.h>
#include <unistd.h>
#include "utils.h"


int ret;
void *res;
pthread_t data_thread;
pthread_t server_thread;

int main(int argc , char * argv[])
{
	printf(">>>>>>>>>>>>>>>>>>>> Start Server Side <<<<<<<<<<<<<<<<<<<< \n \n");

	(void) signal(SIGINT,kill_Process_Handller);

	//Socket connection establish
	Server_Socket_Connection_Establish();

    //create Threads
	ret = pthread_create(&data_thread,NULL,&Collect_Data,NULL);
	ret = pthread_create(&server_thread,NULL,&Send_Data,NULL);


    pthread_join(data_thread,&res);
    pthread_join(server_thread,&res);

	return 0;
}

