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
#define TRUE 1
#define PORT 5000
#include"../Game/game.cpp"
using namespace std;

int quit=0; //quit表示是否用户确定退出
char player[5][1024];
int snd,rev;
char msg1[1024];
int i;
//close((intptr_t)sockfd);//关闭此套接口   游戏结束记得关套接口 
int connfd;
int selfnum;//自己的编号 //后续根据 getplayername(int connfd) char player[5][20];得出 
int Pl1,Pl2;
int now=0;

void ReadCard(int* card){
	
	for (int i=1; i<16; i++) card[i]=0;

	cout<<"请输入你要打出的牌数(0表示不出牌):";	
	int n;
	cin>>n;
	getchar();

	char s[500];
	int x;
	int count = 0;
	char s1[] = "大王";
	char s2[] = "小王"; 
	if(count<n) 
	{
		cout<<"请输入你要打出的牌:";
		cin.getline(s,sizeof(s));

	}
	string tmp="";
	for (int i=0;i<strlen(s);i++)
	{
		// if(count>=n) break;
		// x = 0;
		// if(s[i]<='9'&&s[i]>='2') x = s[i]-'0';
		// else if(s[i]=='1')
		// {
		// 	if(s[i+1]=='0')
		// 	{
		// 		x = 10;
		// 		i++;
		// 	}
		// }
		// else if(s[i]=='j'||s[i]=='J') x=11;
		// else if(s[i]=='q'||s[i]=='Q') x=12;
		// else if(s[i]=='k'||s[i]=='K') x=13;
		// else if(s[i]=='a'||s[i]=='A') x=1;
		// else if(s[i]==s1[0]&&s[i+1]==s[1]&&s[i+2]==s[2]&&s[i+3]==s[3]){
		// 	x=15;
		// 	i+=3;
		// }
		// else if(s[i]==s2[0]&&s[i]==s2[1]&&s[i]==s2[2]&&s[i]==s2[3]){
		// 	x=14;
		// 	i+=3;
		// }
		// if(x!=0)
		// {
		// 	card[x]++;
		// 	count++;
		// }
		if (s[i]!=' ') tmp+=s[i];
		if (s[i]==' ' || i==strlen(s)-1){
			if (tmp.size()==1 && (tmp>="1" || tmp<="9") ){
				x=tmp[0]-'0';
			}
			else if (tmp=="10") x=10;
			else if(tmp=="j"||tmp=="J"||tmp=="11") x=11;
			else if(tmp=="q"||tmp=="Q"||tmp=="12") x=12;//exist problem
			else if(tmp=="k"||tmp=="K"||tmp=="13") x=13;
			else if(tmp=="a"||tmp=="A") x=1;
			else if(tmp=="小王"||tmp=="14") x=14;
			else if(tmp=="大王"||tmp=="15") x=15;
			if(x!=0)
			{
				card[x]++;
				count++;
			}
			tmp="";
		}
	}
}
void ShowUnderCard(int *card){
	int count = 0;
	int exist[21];
	/*for (int i=3; i<14; i++)
		for (int j=1; j<=card[i]; j++)
			exist[count++] = i;
	for(int i=1;i<3;i++)
		for(int j=1;j<=card[i];j++)
			exist[count++] =i;
	for(int i=14;i<16;i++)
		for(int j=1;j<=card[i];j++)
				exist[count++] =i;*/
	int num = 29;
	cout<<endl;
	count = 3;
	for(int i=0;i<3;i++)
	{
		exist[i] = card[i];
	}
	for (int i=0;i<(num-count)/2;i++)
	cout<<"       ";
		for(int i = 0; i< count ; i++)
	{
		cout<<"┏━━━━┓";
	}
	cout<<endl;
	for (int i=0;i<(num-count)/2;i++)
	cout<<"       ";
		for(int i = 0; i<count ; i++)
		if(exist[i]==1)
		cout<<"┃"<<"A"<<"   ┃";
		else if(exist[i]<10)
		cout<<"┃"<<exist[i]<<"   ┃";
		else if(exist[i]==10)
		cout<<"┃"<<"10"<<"  ┃";
		else if(exist[i]==11)
		cout<<"┃"<<"J"<<"   ┃";		
		else if(exist[i]==12)
		cout<<"┃"<<"Q"<<"   ┃";
		else if(exist[i]==13)
		cout<<"┃"<<"K"<<"   ┃";
		else if(exist[i]==14)
		cout<<"┃"<<"小王"<<"┃";	
		else if(exist[i]==15)
		cout<<"┃"<<"大王"<<"┃";	
		cout<<endl;
		for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
		for(int i = 0; i<count ; i++)
		cout<<"┃    ┃";
		cout<<endl;
		for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
		for(int i = 0; i<count ; i++)
		cout<<"┃    ┃";
		cout<<endl;
		for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
		for(int i = 0; i<count ; i++)
		cout<<"┗━━━━┛";
		cout<<endl;
		cout<<endl;
		cout<<endl;
}
void ShowOtherCard(int beforenum,int afternum)//BeforeCardNum,AfterCardNum,PreModel.Card
{
	// cout<<endl;
	// cout<<endl;
	// cout<<endl;
	int count =2;
	int num = 23;
	int BeforeCardNum = beforenum;
	int AfterCardNum  = afternum;
	int i;
	if(BeforeCardNum>0&&AfterCardNum>0)
	{
	cout<<"       ";
	cout<<"┏━━━━┓";
	for (i=0;i<num;i++)
	cout<<"       ";
	cout<<"┏━━━━┓";
	cout<<endl;
	

	cout<<"       ";
	if(BeforeCardNum<10)
	cout<<"┃"<<BeforeCardNum<<"   ┃";	
	else cout<<"┃"<<BeforeCardNum<<"  ┃";	
	for (i=0;i<num;i++)
	cout<<"       ";
	if(AfterCardNum<10)
	cout<<"┃"<<AfterCardNum<<"   ┃";
	else 	cout<<"┃"<<AfterCardNum<<"  ┃";
	cout<<endl;
		
	cout<<player[Pl2];
	for(i=0;i<7-strlen(player[Pl2]);i++)
	cout<<" ";
	cout<<"┃    ┃";
	for (i=0;i<num;i++)
	cout<<"       ";
	cout<<"┃    ┃";
		for(i=0;i<7-strlen(player[Pl1]);i++)
	cout<<" ";
	cout<<player[Pl1];
	cout<<endl;
	
	cout<<"       ";
	cout<<"┃    ┃";
	for (i=0;i<num;i++)
	cout<<"       ";	
	cout<<"┃    ┃";
	cout<<endl;
	
	cout<<"       ";
	cout<<"┗━━━━┛";
	for (i=0;i<num;i++)
	cout<<"       ";	
	cout<<"┗━━━━┛";
	cout<<endl;
	}
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl<<endl<<endl;
}

void ShowCard(int* card,int flag){
		
		int count = 0;
		int exist[21];
		for (int i=3; i<14; i++)
			for (int j=1; j<=card[i]; j++)
				exist[count++] = i;
		for(int i=1;i<3;i++)
			for(int j=1;j<=card[i];j++)
				exist[count++] =i;
		for(int i=14;i<16;i++)
			for(int j=1;j<=card[i];j++)
				exist[count++] =i;
	
	const int num = 29;
	for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
	for(int i = 0; i< count ; i++)
	{
		cout<<"┏━━━━┓";
	}	
	cout<<endl;
	for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
	for(int i = 0; i<count ; i++)
		if(exist[i]==1)
		cout<<"┃"<<"A"<<"   ┃";
		else if(exist[i]<10)
		cout<<"┃"<<exist[i]<<"   ┃";
		else if(exist[i]==10)
		cout<<"┃"<<"10"<<"  ┃";
		else if(exist[i]==11)
		cout<<"┃"<<"J"<<"   ┃";		
		else if(exist[i]==12)
		cout<<"┃"<<"Q"<<"   ┃";
		else if(exist[i]==13)
		cout<<"┃"<<"K"<<"   ┃";
		else if(exist[i]==14)
		cout<<"┃"<<"小王"<<"┃";	
		else if(exist[i]==15)
		cout<<"┃"<<"大王"<<"┃";	
		cout<<endl;
		for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
		for(int i = 0; i<count ; i++)
		cout<<"┃    ┃";
		cout<<endl;
		for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
		for(int i = 0; i<count ; i++)
		cout<<"┃    ┃";
		cout<<endl;
		for (int i=0;i<(num-count)/2;i++)
		cout<<"       ";
		for(int i = 0; i<count ; i++)
		cout<<"┗━━━━┛";
		cout<<endl;
		
		if(flag == 1)
		{

			cout<<"正在等待"<<player[now%3]<<"出牌"<<endl;

		}
		cout<<endl<<endl<<endl;
	
}

void dealcard(int goalnum,int cardlist[])
{
	char str[1024];
	memset(str,0,sizeof(str));
	str[0]='0'+selfnum;
	str[1]='0'+goalnum;
	str[2]='0'+1;
	for(int k=1;k<16;k++)
	{
		str[2+k]='0'+cardlist[k];
	}
	snd=send(connfd,str,strlen(str),0);//发送消息给服务器
	while(1)
	{
		char sbuf[1024];
		if ((rev = recv((intptr_t)connfd,sbuf,1024,0))>0)
		{
			//snd=send(connfd,buf,strlen(buf),0);//发送消息给服务器
			break;
		}
	}
}

void getplayername()
{
	char temp[1024];
	memset(temp,0,sizeof(temp));
	for(i=0;i<3;i++)
	{
		while(1)
		{
			memset(temp,0,sizeof(temp));
			if ((rev = recv((intptr_t)connfd,temp,1024,0))>0)
			{
				strcpy(player[i],temp);
				printf("%s\n",temp);
				snd=send(connfd,temp,strlen(temp),0);
				break;
			}	
		}
	}	
	for(int k=0;k<3;k++)
	{
		if(strcmp(player[k],msg1)==0)
		{
			selfnum=k;
		}
	}
}

void sendmsg(int goalnum,int isfirst,int cardlist[])
{
	char str[1024];
	memset(str,0,sizeof(str));
	str[0]='0'+selfnum;
	str[1]='0'+goalnum;
	str[2]='0'+isfirst;
	for(int k=1;k<16;k++)
	{
		str[2+k]='0'+cardlist[k];
	}
	snd=send(connfd,str,strlen(str),0);//发送消息给服务器
}
int sendnum;
int goalnum;
int isfirst;
int msglist[30];
void revmsg(void)
{
	char sbuf[1024];
	memset(msglist,0,sizeof(msglist));
	memset(sbuf,0,sizeof(sbuf));
	// cout<<"正在等待出牌";
	while(1)
	{

		if ((rev = recv((intptr_t)connfd,sbuf,1024,0))>0)
		{
			//snd=send(connfd,buf,strlen(buf),0);//发送消息给服务器
			printf("%s\n",sbuf);
			break;
		}
	}
	sendnum=sbuf[0]-'0';
	goalnum=sbuf[1]-'0';
	isfirst=sbuf[2]-'0';
	for(int k=1;k<16;k++)
	{
		msglist[k]=sbuf[2+k]-'0';
	}
}

void play_bgmusic(){
	system("mplayer -quiet ../Music/bg_music.mp3 > /dev/null 2>&1 &");
}

int sendnums,isfirsts;
int cardlists[30];
int main(void)
{
	int slenth;
	struct sockaddr_in server;
	struct hostent *hp;
	char honame[20],msg2[1024],cln[102],qstr[]={"Quit"}; //qstr的值表示用户在输入"Quit"时和服务器断开链接
	pthread_t tid;
	printf("请输入服务器IP地址: ");
	scanf("%s*",honame);
	printf("正在建立套接口...\n");
	if((connfd= socket(AF_INET, SOCK_STREAM, 0))<0) //建立套接口
	printf("建立套接口失败\n");
	if ((hp= gethostbyname(honame))== NULL) //获取服务器IP地址
	{
		printf("获取服务器IP地址失败\n");
		exit(1);
	}
	else printf("套接口建立成功，连接服务器中...\n");
	memcpy(&server.sin_addr,hp->h_addr,hp->h_length); //将服务器IP地址放入结构体server中
	server.sin_family = AF_INET;
	server.sin_port=htons(PORT);
	if(connect(connfd,(struct sockaddr*)&server,sizeof(server))<0) //链接套接口 
	{
		printf("连接服务器失败\n");
		exit(1);
	}
	printf("连接服务器成功\n"); //链接成功显示成功的登录信息
	printf("等待其他玩家加入中...\n");
	while(1)
	{
		char buf[1024];
		memset(buf,0,sizeof(buf));
		memset(msg1,0,sizeof(msg1));
		if ((rev = recv((intptr_t)connfd,buf,1024,0))>0)
		{
			printf("%s",buf);//	printf("请输入你的用户昵称\n");	
			scanf("%s",msg1);
			strcpy(cln,msg1); //保存用户昵称在名为cln的数组中
			snd=send(connfd,msg1,strlen(msg1),0);//发送消息给服务器
			break;
		}
	}
	getplayername();
	while(1)
	{
		char buf[1024];
		memset(buf,0,sizeof(buf));
		if ((rev = recv((intptr_t)connfd,buf,1024,0))>0)
		{			
			printf("%s\n",buf);//	
			snd=send(connfd,buf,strlen(buf),0);//发送消息给服务器
			break;
		}

	}
	//pthread_t tid_bg;
	//pthread_create(&tid_bg,NULL,play_bgmusic,NULL);//bg_music
	play_bgmusic();//bg_music
	char buf[1024];
	memset(buf,0,sizeof(buf));
	Game play;
	int undercard[10];
	Pl1=(selfnum+1)%3;
	Pl2=(selfnum+2)%3;
	int beforenum,afternum,restnum;
	int last_before_num,last_after_num;
	if(Pl2 == 0) beforenum = 20;
	else beforenum = 17;
	if(Pl1 ==0) afternum =20;
	else afternum = 17;
	if(selfnum==0) restnum =20;
	else restnum = 17;
	memset(undercard,0,sizeof(undercard));
	while(1)
	{
		if ((rev = recv((intptr_t)connfd,buf,1024,0))>0)
		{
			printf("%s\n",buf);
			int ans=strcmp(buf,msg1);
			if(ans==0)
			{
				printf("fapai\n");
				int card1[20],card2[20],cardex[20];
				play.ShuffleCard(card1,card2,cardex);
				dealcard(1,card1);
				dealcard(2,card2);
				play.AddCard(cardex);
				int count =0;
						for(int th=1;th<16;th++)
						{
							if(cardex[th]==1) undercard[count++] = th;
							if(cardex[th]==2){
								undercard[count++] = th;
								undercard[count++] = th;
							}
							if(cardex[th] == 3)
							{
								undercard[count++] = th;
								undercard[count++] = th;
								undercard[count++] = th;
							}

						}
				sleep(1);
				sendmsg(selfnum,1,cardex);

				//fa pai
			}
			else
			{
				printf("%d\n",selfnum);
				printf("wait card\n");
				while(1)
				{
					revmsg();
					if(goalnum==selfnum&&isfirst==1)
					{
						play.SetCard(msglist);
						break;
					}
					
				}
				while(1)
				{
					revmsg();
					if(sendnum==0&&isfirst==1)
					{
						printf("dizpai:\n");
						int count = 0;
						for(int th=1;th<16;th++)
						{
							if(msglist[th]==1) undercard[count++] = th;
							if(msglist[th]==2){
								undercard[count++] = th;
								undercard[count++] = th;
							}
							if(msglist[th] == 3)
							{
								undercard[count++] = th;
								undercard[count++] = th;
								undercard[count++] = th;
							}

						}
						printf("\n");
						ShowUnderCard(undercard);
						ShowCard(play.PreModel.Card,0);
						ShowOtherCard(beforenum,afternum);
						ShowCard(play.Card,1);

						break;
					}
				}				
			}
			break;
		}
		
		
	}
	

	last_after_num = afternum;
	last_before_num = beforenum;//last time
	if(selfnum == 0)//game start
	{
		while(1)
		{
		system("clear");
		ShowUnderCard(undercard);
		ShowCard(play.PreModel.Card,0);
		ShowOtherCard(beforenum,afternum);
		ShowCard(play.Card,0);
		int card[20];
		ReadCard(card);
		
		int flag=play.PlayCard(card);

		if (flag==0){
			now++;
			sendmsg(Pl1,0,card);
			system("clear");
			
			play.SetPreModel(card,selfnum);
			ShowUnderCard(undercard);
			if(play.PrePlayer>=0)
			{
				for (int i=0;i<(29-2)/2;i++)
				cout<<"       ";
				cout<<"出牌的人为:"<<player[play.PrePlayer]<<endl;
				
			}
			ShowCard(play.PreModel.Card,0);
			ShowOtherCard(beforenum,afternum);
			ShowCard(play.Card,1);
			if (play.CheckGameEnd()) return 0; 
			break;

		}
		else if (flag==5) {
			now++;
			sendmsg(Pl1,0,card);
			system("clear");
			ShowUnderCard(undercard);
			if(play.PrePlayer>=0)
			{
				for (int i=0;i<(29-2)/2;i++)
				cout<<"       ";
				cout<<"出牌的人为:"<<player[play.PrePlayer]<<endl;
				
			}
			ShowCard(play.PreModel.Card,0);
			ShowOtherCard(beforenum,afternum);
			ShowCard(play.Card,1);
			break;
		}
		else if (flag==1) cout<<"no model!\n";
		else if (flag==2) cout<<"no engouh card!\n";
		else if (flag==3) cout<<"can't match the premodel!\n";
		else if (flag==4) cout<<"can't win the premodel!\n";
		else cout<<"unexpected error!\n";

		//sendmsg(pl2,0,card);

		}


	}

//int sendnum;
//int goalnum;
//int isfirst;
//int msglist[30];

	while(1)
	{
		
		revmsg();
			system("clear");
			// cout<<"正在等待"<<player[sendnum]<<"出牌";
			int count = 0;
			for(int i =1;i<16;i++)
			{
				if(msglist[i]!=0)  count+=msglist[i];
			}
			now++;
			if(sendnum == Pl2)
			{

				if(count != 0 ) 
				{
					play.SetPreModel(msglist,Pl2);//may exist problem
					beforenum -= count;

				}
				if(beforenum == 0){
					cout<<"Game is over!"<<endl<<player[Pl2]<<" win the game!"<<endl;
					return 0;
				} 
				// cout<<"beforecard:"<<beforenum<<endl;
				if(last_after_num == afternum&&last_before_num == beforenum)
				{
					play.ClearPreModel();

				}
				else{
					last_after_num = afternum;
					last_before_num = beforenum;
				}
				
				while(1)
				{
					// system("clear");
					ShowUnderCard(undercard);
					if(play.PrePlayer>=0)
					{
						for (int i=0;i<(29-2)/2;i++)
						cout<<"       ";
						cout<<"出牌的人为:"<<player[play.PrePlayer]<<endl;
						
					}
					ShowCard(play.PreModel.Card,0);
					ShowOtherCard(beforenum,afternum);
					ShowCard(play.Card,0);
					int card[20];
					ReadCard(card);
					int flag=play.PlayCard(card);
					

					if (flag==0){
						now++;
						sendmsg(Pl1,0,card);
						play.SetPreModel(card,selfnum);
						system("clear");
						ShowUnderCard(undercard);
						if(play.PrePlayer>=0)
						{
							for (int i=0;i<(29-2)/2;i++)
							cout<<"       ";
							cout<<"出牌的人为:"<<player[play.PrePlayer]<<endl;
							
						}
						ShowCard(play.PreModel.Card,0);
						ShowOtherCard(beforenum,afternum);
						ShowCard(play.Card,1);
						if (play.CheckGameEnd()) 
						{
							cout<<"Game is over!"<<endl<<"You win the game!"<<endl;
							return 0; 
						}
						break;

					}
					else if (flag==5) {
						now++;
						sendmsg(Pl1,0,card);
						system("clear");
						// play.SetPreModel(card);
						ShowUnderCard(undercard);
						if(play.PrePlayer>=0)
						{
							for (int i=0;i<(29-2)/2;i++)
							cout<<"       ";
							cout<<"出牌的人为:"<<player[play.PrePlayer]<<endl;
						}
						ShowCard(play.PreModel.Card,0);
						ShowOtherCard(beforenum,afternum);
						ShowCard(play.Card,1);
						break;
					}
					else if (flag==1) cout<<"no model!\n";
					else if (flag==2) cout<<"no engouh card!\n";
					else if (flag==3) cout<<"can't match the premodel!\n";
					else if (flag==4) cout<<"can't win the premodel!\n";
					else cout<<"unexpected error!\n";


				}				
				// cout<<"正在等待"<<player[sendnum]<<"出牌";


				
			}
			if(sendnum == Pl1)
			{
				
				// system("clear");
				if(count != 0 ) 
				{
					play.SetPreModel(msglist,Pl1);//may exist problem
					afternum -= count;
				}
				if(afternum == 0){
					cout<<"Game is over!"<<endl<<player[Pl1]<<" win the game!"<<endl;
					return 0;
				} 
				ShowUnderCard(undercard);
				if(play.PrePlayer>=0)
				{
						for (int i=0;i<(29-2)/2;i++)
						cout<<"       ";
					cout<<"出牌的人为:"<<player[play.PrePlayer]<<endl;
				}
				ShowCard(play.PreModel.Card,0);
				ShowOtherCard(beforenum,afternum);
				ShowCard(play.Card,1);
				// cout<<"正在等待"<<player[Pl1]<<"出牌";
			}
		
	}
	
	
	return 0; 
}
