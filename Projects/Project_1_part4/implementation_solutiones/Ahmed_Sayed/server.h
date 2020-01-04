typedef struct can_packet
{
    char username[10];
    char id[5];
    char dlc[5];
    char data[5];
    int payload[5];
} packet;

extern packet p;
extern char x[100];
pthread_mutex_t fill_mutex;
pthread_cond_t cond_var=PTHREAD_COND_INITIALIZER;
extern int confd=0;
void runserver()
{
	int listenfd=0;
	struct sockaddr_in serv_addr;

	char sendbuff[100];
	time_t ticks;
	
	listenfd =socket(AF_INET,SOCK_STREAM,0);
	memset(&serv_addr,'0',sizeof(serv_addr));
	memset(sendbuff,'0',sizeof(sendbuff));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(5200);
	
	bind(listenfd, (struct sockaddr*) &serv_addr,sizeof(serv_addr));

	listen(listenfd,10);

	confd= accept(listenfd, (struct sockaddr*)NULL,NULL);

	while(1)
	{
		
		//ticks =time(NULL);
		memset(sendbuff,0,sizeof(sendbuff));
		
		//snprintf(sendbuff, sizeof(sendbuff),"sent time%.24s \n",ctime(&ticks));
		//write(confd,sendbuff,strlen(sendbuff));
		
pthread_mutex_lock(&fill_mutex);
		pthread_cond_signal(&cond_var);
		
		printf("i am in server\n");
		read_packet();	
			
		write(confd,x,strlen(x));
		pthread_mutex_unlock(&fill_mutex);
//pthread_exit(NULL);
		sleep(1);

		
		
	}
}


void read_packet()
{

char *s;
char d[5];
time_t ticks;
memset(&s,0,sizeof(s)-1);
ticks =time(NULL);
s=ctime(&ticks)+4;
s[strlen(s)-1]=0;


    
memset(&x,0,sizeof(x));
memset(&(p.data),'0',sizeof(p.data));
    printf("Enter username:");
    scanf("%s", &(p.username));

    printf("Enter ID:");
    scanf("%s", &(p.id));
    printf("Enter DLC:");
    scanf("%s", &(p.dlc));

    printf("Enter Data:");
    scanf("%s", &(d));

    strcpy(p.data+strlen(p.data)-strlen(d),d);

strcpy(x,p.username);
strcat(x,";");
strcat(x,p.id);
strcat(x,";");
strcat(x,p.dlc);
strcat(x,";");
strcat(x,p.data);
strcat(x,";");
strcat(x,s);
strcat(x,";");
printf("%s",x);

}

