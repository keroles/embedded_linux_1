
extern packet p;
extern char x[100];
extern int fd_out;
extern pthread_mutex_t fill_mutex;
extern pthread_cond_t cond_var;
int runclient()
{
	
	fd_out=open("newfile.txt",O_RDWR | O_TRUNC | O_CREAT,0744);// open write file
	int sockfd =0,n=0;
	char recvbuff[100];
	time_t ticks;
	char *s;
	struct sockaddr_in serv_addr;


	memset(recvbuff,0,sizeof(recvbuff));

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
	
	printf("\n Error: Could not create socket \n");
	return 1;
	}
	memset(&serv_addr, '0',sizeof(serv_addr));
	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(5200);
	serv_addr.sin_addr.s_addr= inet_addr("127.0.0.1");
	
	if(connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
	{
		printf("\nError : connect Failed client \n");
		return 1;

	}

	while ( (n=read(sockfd, recvbuff,sizeof(recvbuff)-1))>0)
	{
//		memset(recvbuff,'0',sizeof(recvbuff));
		pthread_mutex_lock(&fill_mutex);
		printf("i am in cleint and mutex locked\n");
		
	
memset(&s,0,sizeof(s)-1);
		ticks =time(NULL);
s=ctime(&ticks)+4;
s[strlen(s)-1]=0;
//		printf("\n%s\n",s);


strcat(recvbuff,s);
strcat(recvbuff,"\n");
write(fd_out,recvbuff,(strlen(recvbuff)));
memset(recvbuff,0,sizeof(recvbuff));
pthread_cond_wait(&cond_var,&fill_mutex);
pthread_mutex_unlock(&fill_mutex);
//pthread_exit(NULL);
	}


	
	return 0;
}
