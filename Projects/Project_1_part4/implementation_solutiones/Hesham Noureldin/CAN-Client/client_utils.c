/*
 * client_utils.c
 *
 *  Created on: Dec 27, 2019
 *      Author: Hesham Noureldin
 */


/*
 * utils.c

 *
 *  Created on: Dec 26, 2019
 *      Author: Hesham Noureldin
 */
#include <time.h>
#include "client_utils.h"
#include <string.h>
#include <limits.h>



pthread_mutex_t data_mutex;
pthread_cond_t mutex_lock_cond = PTHREAD_COND_INITIALIZER;

char Rx_Time[25] ={0};
char IP_Address[25]={0};
char RecvBuffer[BUFFER_SIZE];
char path[PATH_MAX];
char *logfile = "can_log.txt";

//socket parameters definitions
int sockfd = 0;
int fd_out = -1;
struct sockaddr_in serv_addr; //server structure


void Client_Socket_Connection_Establish()
{

	memset(&serv_addr,'0', sizeof(serv_addr));

	/*==== step 1:create client socket ====*/

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) <0)
	{
		printf( "[-] Error in creating socket. \n");
		exit(EXIT_FAILURE);
	}
	printf("[+] Client socket is created. \n");

	serv_addr.sin_family =AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_Address);
	serv_addr.sin_port = htons(PORT);

	/*==== step 2:connect to server ====*/
    if( connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
    	printf("[-] Error in connection. \n");
    	exit(EXIT_FAILURE);
    }
    printf("[+] Connected to server. \n");


}


void kill_Process_Handller()
{
	  printf("[-] Session Terminated From Client Side !!. \n ");
	 //close sockets
	   close(sockfd);
	 //close file handler
	   close(fd_out);
	 //open log file
	   char *args [] = {"gedit",logfile,NULL};
	   int ret = execvp(args[0],args);
	   if((int)ret<0)
	   {
	    perror("[-] Error opening log file. \n");
	   }

	(void) signal(SIGINT,SIG_DFL);
}


void Get_Rx_Time(){
    time_t rawtime = time (NULL );
    snprintf( Rx_Time, sizeof(Rx_Time),"%24s\r\n",ctime(&rawtime));
}

void * Dump_Data()
{
   while(1)
   {
       pthread_mutex_lock (&data_mutex);
       pthread_cond_wait(&mutex_lock_cond,&data_mutex);
       //get data from structure && dump to file
       if(strstr(RecvBuffer, "exit") == NULL) {
		   strcat(RecvBuffer,",");
		   strcat(RecvBuffer,Rx_Time);
    	   Write_Data_To_File();
       }
       memset(RecvBuffer,0,sizeof(RecvBuffer));
       pthread_mutex_unlock(&data_mutex);
       sleep(1);
   }

}

void * Receive_Data()
{
	while(1)
	{
           (void) Get_Rx_Time();
           if(strcmp(RecvBuffer,"exit")== 0)
           {
        	   close(sockfd );
        	   printf("[-] Disconnect from Server. \n");
        	   //open log file
        	   char *args [] = {"gedit",logfile,NULL};
        	   int ret = execvp(args[0],args);
        	   if((int)ret<0)
        	   {
        	   	perror("[-] Error opening log file. \n");
        	   }
        	   exit(EXIT_FAILURE);
           }
		   if(recv(sockfd,RecvBuffer,sizeof(RecvBuffer),0)<0)
		   {
			   printf("[-] Error in Receiving Data. \n");
			   exit(EXIT_FAILURE);

		   }

		   printf("[+] Received Data From Server: %s. \n",RecvBuffer);
		   //fill structure
		   pthread_mutex_lock (&data_mutex);
		   pthread_cond_signal(&mutex_lock_cond);
		   pthread_mutex_unlock(&data_mutex);

	}
}

void Write_Data_To_File()
{
   get_path();
   char * OUTPUT_FILEPATH = path ;
   int retw =0;

   fd_out = open(OUTPUT_FILEPATH ,O_RDWR | O_CREAT |O_APPEND, 0744);
   if(fd_out == -1)
   {
	   printf("[-] Error in opening the output file. \n");
	   exit(EXIT_FAILURE);
   }
   strcat(RecvBuffer,"\n");

   retw = write(fd_out,RecvBuffer,strlen(RecvBuffer));
   //write(fd_out," \n");
   if(retw != strlen(RecvBuffer))
   {
	   printf("[-] Error in writing complete data to the output file. \n");
	   close(fd_out);
	   exit(0);
   }
   printf("[+] Write Data Successfully to log file . \n");
   close(fd_out);

}

void get_path()
{
	   if (getcwd(path, sizeof(path)) != NULL) {
	       strcat(path,"/");
	       strcat(path,logfile);
	       //printf("[+] Current working directory: %s .\n", path);
	   } else {
	       perror("[-] Error getting current working directory. \n ");
	   }
}
