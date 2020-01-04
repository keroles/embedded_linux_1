#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>





#include "server.h"
#include "client.h"

packet p;
char x[100];
int fd_out;
int confd;
pthread_mutex_t fill_mutex;
pthread_cond_t cond_var;
void my_signal_handler(int signum);
void *server_thread(void *data){
	runserver();
}

void *client_thread(void *data)
{
	
	runclient();
}
int main(int argc, char* argv[])
{
	(void) signal(SIGINT,my_signal_handler);
	pthread_t th1,th2;
	int ret;
	void *res;
	pthread_create(&th1, NULL, &server_thread , NULL);
	pthread_create(&th1, NULL, &client_thread , NULL);
	
	pthread_join(th1,&res);
	pthread_join(th2,&res);


	while(1){}
}

void my_signal_handler(int signum)
{
	printf("i am handling the signal %d \n",signum);
	close(fd_out);
	//close(confd);
	printf("file and server closed \n");
	(void) signal(SIGINT,SIG_DFL);
	

}
