/*
 * utils.c

 *
 *  Created on: Dec 26, 2019
 *      Author: Hesham Noureldin
 */
#include <time.h>
#include "utils.h"
#include <string.h>



pthread_mutex_t data_mutex;
pthread_cond_t mutex_lock_cond = PTHREAD_COND_INITIALIZER;


char SendBuffer[BUFFER_SIZE];
char Temp[25];
char Tx_Time[25] ={0};
int DLC;

//socket parameters definition
int sockfd;
int bind_ret;
int clientSocket = 0;
struct sockaddr_in serv_addr;
struct sockaddr_in clint_addr;
socklen_t addr_size;

void Server_Socket_Connection_Establish()
{
	     memset(&serv_addr,'0', sizeof(serv_addr));

		/*==== step 1:create Server socket ====*/

		if((sockfd = socket(AF_INET,SOCK_STREAM,0)) <0)
		{
			printf( "[-] Error in creating socket. \n");
			exit(EXIT_FAILURE);
		}
		printf("[+] Server socket is created. \n");


		/*==== step 2:Binding  Server to the port and IP ====*/
		serv_addr.sin_family =AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(PORT);

		bind_ret = bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
		if(bind_ret <0){
			printf( "[-] Error in binding. \n");
			exit(EXIT_FAILURE);
		}
		printf( "[+] Bind server to port %d. \n",PORT);

		/*==== step 3:Listening to Clients ====*/
		if(listen(sockfd,10)==0){
			printf( "[+] Listening ............ \n");
		}
		else{
			printf( "[-] Error in Listening .\n");
			exit(EXIT_FAILURE);
		}

		/*==== step 4:Accept connection from client ====*/
		clientSocket = accept(sockfd,(struct sockaddr*)&clint_addr,&addr_size);
	    if(clientSocket <0)
	    {
			printf( "[-] Error in accepting connection  .\n");
			exit(EXIT_FAILURE);
	    }
	    printf("[+] Connection accepted from %s:%d \n",inet_ntoa(clint_addr.sin_addr),ntohs(clint_addr.sin_port));

}

void kill_Process_Handller()
{
	 printf(" [-] Session Terminated From Server Side !! \n");
	 memset(Temp,0,sizeof(Temp));
	 strcpy(Temp,"exit");
	 send(clientSocket,Temp,strlen(Temp),0);
	 memset(Temp,0,sizeof(Temp));
	 sleep(3);
	 //close sockets
	 close(clientSocket);
	(void) signal(SIGINT,SIG_DFL);
}


void Get_Tx_Time(){
    time_t rawtime = time (NULL );
    snprintf( Tx_Time, sizeof(Tx_Time),"%24s\r\n",ctime(&rawtime));
}

void * Collect_Data()
{
	while(1)
	{

	   printf("\n \n --> Please Insert CAN Frame ID : \n");
	   scanf("%s" , &Temp[0]);
	   strcat(SendBuffer,Temp);
	   printf("--> Please Insert Data Length from (1 to 64):\n");
	   scanf("%d" , &DLC);
	   while((DLC < 1)||(DLC >64))
	   {
		   printf("[-] Invalid Data Length , Please Try Again .\n");
		   scanf("%d" , &DLC);
	   }
	   snprintf (Temp, sizeof(Temp), "%d",DLC);
	   strcat(SendBuffer,",");
	   strcat(SendBuffer,Temp);
	   strcat(SendBuffer,",");

	   //Insert Data Frame
	   for(int i =0 ; i< DLC ;i++)
	   {
		 printf("--> please Insert byte #: %d \n ",i+1);
		 scanf("%s",&Temp[0]);
		 strcat(SendBuffer,Temp);
		 sleep(1);
	   }
	   strcat(SendBuffer,",");
	   printf( "[+] SendData = %s . \n",SendBuffer);
	   pthread_mutex_lock (&data_mutex);
	   pthread_cond_signal(&mutex_lock_cond);
	   pthread_mutex_unlock(&data_mutex);
	}

}

void * Send_Data()
{
	while(1)
	{

   (void) Get_Tx_Time();
   pthread_mutex_lock (&data_mutex);
   pthread_cond_wait(&mutex_lock_cond,&data_mutex);
   strcat(SendBuffer,Tx_Time);
   //send data
   send(clientSocket,SendBuffer,strlen(SendBuffer),0);
   memset(SendBuffer,0,sizeof(SendBuffer));
   pthread_mutex_unlock(&data_mutex);
	}
}
