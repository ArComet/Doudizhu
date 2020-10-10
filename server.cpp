/* 由于线程pthread库不是Linux系统默认的库，连接时需要使用库libpthread.a,所以程序中有使用pthread_create，在编译中要加-lpthread参数

gcc client.c -o client -lpthread 

*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>
#define MAXLINE 1000 //在一条消息中最大的输出字符数
#define LISTENQ 20 //最大监听队列
#define PORT 5000 //监听端口
#define MAXFD 3 //最大的在线用户数量

void *get_client(void *);
FILE *fp;
int i,maxi=-1;//maxi表示当前client数组中最大的用户的i值
int client[MAXFD];
//num 0-2 牌发给谁 isplay 是否到他出牌 cardlist[] 牌组 cardlist[1]=3:表示有3张A
int sendcardmsg(int num,int isplay,int cardtype,int cardlist[]) //cardtype 牌型编号 
{//发牌//发送出牌信息 //可以以前一个结合，客户端判断牌型 
	int flag;
	//如果确认到返回1
	return flag ;
}
int sendendmsg(int num,int win)//win 赢得人的编号 
{//发送牌局结束信息 
	int flag;
	//如果确认到返回1
	//想继续玩返回2 
	return flag ;
}
int receivecardmsg(int *cardlist)//cardlist接收牌组信息 
{
	int num;//收到的出牌人编号 
	
	return num;
}


int main(void)
{
	int connfd,listenfd,sockfd; //connfd存放accept函数的返回值，listenfd表示监听的套接口，
	//sockfd用于遍历client的数组
	char playname[5][20]; //用户名 
	socklen_t length;
	fp=fopen("student.txt","w");
	struct sockaddr_in server;
	struct sockaddr tcpaddr;
	pthread_t tid;
	listenfd=socket(AF_INET,SOCK_STREAM,0); //建立套接口并监听
	if(listenfd<0){
		printf("建立套接口错误\n");
		exit(1);
	}
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	if( bind(listenfd,(struct sockaddr*)&server,sizeof(server))<0 )
	{
		printf("绑定套接口失败\n");
		exit(1); //绑定套接口
	}
	length=sizeof(server);
	if(getsockname(listenfd,(struct sockaddr*)&server,&length)<0)
	{
		printf("取服务器的端口号失败\n"); //取得服务器的端口号
		exit(1);
	}
	for(i=0;i<MAXFD;i++)
	client[i]=-1; //initialize the client column
	listen(listenfd, LISTENQ);
	printf("服务器监听端口 %d...\n", ntohs(server.sin_port));
	printf("欢迎来到本棋牌室\n");
	//等待用户链接.
	for(;;)
	{
		connfd=accept(listenfd, &tcpaddr, &length);
		for(i=0;i<MAXFD;i++)
		if(client[i]<0)
		{
			client[i]=connfd;
			char hello[50]="进入房间成功，请输入你的昵称："; 
			send(client[i],hello,strlen(hello)+1,0);
			char pname[20];
			while(1)
			{//得到用户名1--3 
					if ((rev = recv((intptr_t)sockfd,pname,1024,0))>0)
					{
						strcpy(playname[i],pname);
						break;
					}
			}
			break;
		} //用户链接成功后，在client数组中保存用户套接口号
		if(i==MAXFD-1)
		{
			printf("房间已满员，游戏即将开始\n"); //若此时以达到用户最大值，则退出链接
			char begin[50]="房间已满员，游戏即将开始\n"; 
			for(i=0;i<=2;i++)
			send(client[i],begin,strlen(begin)+1,0);
			break; 
		}
		if(i>maxi) maxi=i;	
	} //运行get_client函数，处理用户请求
	while(1)//游戏运行 
	{
			
	} 
	return 0; 
}
//memset(buf,0,sizeof(buf)); //初始化buffer 
