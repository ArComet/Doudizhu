/* 由于线程pthread库不是Linux系统默认的库，连接时需要使用库libpthread.a,所以程序中有使用pthread_create，在编译中要加-lpthread参数*/ 
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
int rev,snd;
FILE *fp;
int i,maxi=-1;//maxi表示当前client数组中最大的用户的i值
int client[MAXFD];
char playname[5][20]; //用户名 
void sendplaymsg()
{
	for(int k=0;k<3;k++)
	{
		for(int l=0;l<3;l++)
		{
				send(client[k],playname[l],strlen(playname[l]),0);
				while(1)
				{
						char tempp[1024];
						memset(tempp,0,sizeof(tempp));
						rev = recv((intptr_t)client[k],tempp,1024,0);
						if(rev>0)
						break;	
				}
		}
	}
}
int main(void)
{
	int connfd,listenfd,sockfd; //connfd存放accept函数的返回值，listenfd表示监听的套接口，
	//sockfd用于遍历client的数组
	socklen_t length;
	//fp=fopen("student.txt","w");
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
	printf("欢迎来到本室\n");
	//等待用户链接.
	for(;;)
	{
		connfd=accept(listenfd, &tcpaddr, &length);
		for(i=0;i<MAXFD;i++)
		if(client[i]<0)
		{
			client[i]=connfd;
			
			char hello[1024]="进入房间成功，请输入你的昵称:"; 

			send(client[i],hello,strlen(hello),0);
			
			char pname[1024];
			memset(pname,0,sizeof(pname));
			while(1)
			{//得到用户名1--3 
					if ((rev = recv((intptr_t)connfd,pname,1024,0))>0)
					{
						memset(playname[i],0,sizeof(playname[i]));
						strcpy(playname[i],pname);
						printf("%s\n",pname); 
						break;
					}
			}
			break;
		} //用户链接成功后，在client数组中保存用户套接口号
		if(i==MAXFD-1)
		{
			sendplaymsg(); 
			printf("房间已满员，游戏即将开始\n"); //若此时以达到用户最大值，则退出链接
			char begin[50]="房间已满员，游戏即将开始\n"; 
			for(int k=0;k<3;k++)
			send(client[k],begin,strlen(begin)+1,0);
			char tempp[1024];
			memset(tempp,0,sizeof(tempp));
			while(1)
			{
				rev = recv((intptr_t)client[0],tempp,1024,0);
				if(rev>0)
				break;				
			}
			memset(tempp,0,sizeof(tempp));
			while(1)
			{
				rev = recv((intptr_t)client[1],tempp,1024,0);
				if(rev>0)
				break;				
			}
			memset(tempp,0,sizeof(tempp));
			while(1)
			{
				rev = recv((intptr_t)client[2],tempp,1024,0);
				if(rev>0)
				break;				
			}
			break;
		}
		if(i>maxi) maxi=i;	
	} //运行get_client函数，处理用户请求
	for(int k=0;k<3;k++)//指定发牌 
	{
		send(client[k],playname[0],strlen(playname[0]),0);//让0发牌 				
	}
	while(1)//游戏运行 
	{		
					
			char tempp[1024];
			while(1)
			{
				for(int k=0;k<3;k++)
				{
					memset(tempp,0,sizeof(tempp));
					while(1)
					{
						if(rev = recv((intptr_t)client[k],tempp,1024,0)>0)
						{
							printf("%s",tempp);
						}
					}					
					if(rev>0)
					{
						int ta=tempp[0]-'0';
						for(int k=0;k<2;k++)
						{
							if(ta!=k)
							{
								send(client[ta],tempp,strlen(tempp),0);//转发信息 
							}
						}
					}	
				}						
			}	
	} 
	return 0;
}
//memset(buf,0,sizeof(buf)); //初始化buffer 
