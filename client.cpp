#include<stdio.h>
#include<string.h>
#include"game.cpp"

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
	for (int i=0;i<strlen(s);i++)
	{
		if(count>=n) break;
		x = 0;
		if(s[i]<='9'&&s[i]>='2') x = s[i]-'0';
		else if(s[i]=='1')
		{
			if(s[i+1]=='0')
			{
				x = 10;
				i++;
			}
				

		}
		else if(s[i]=='j'||s[i]=='J') x=11;
		else if(s[i]=='q'||s[i]=='Q') x=12;
		else if(s[i]=='k'||s[i]=='K') x=13;
		else if(s[i]=='a'||s[i]=='A') x=1;
		else if(s[i]==s1[0]&&s[i+1]==s[1]&&s[i+2]==s[2]&&s[i+3]==s[3]){
			x=15;
			i+=3;
		}
		else if(s[i]==s2[0]&&s[i]==s2[1]&&s[i]==s2[2]&&s[i]==s2[3]){
			x=14;
			i+=3;
		}
		if(x!=0)
		{
			card[x]++;
			count++;
		}
	}
}
void ShowUnderCard(){
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
		exist[i] = 13;
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
}
void ShowOtherCard()//BeforeCardNum,AfterCardNum,PreModel.Card
{
	cout<<endl;
	cout<<endl;
	cout<<endl;
	int count =2;
	int num = 23;
	int BeforeCardNum = 13;
	int AfterCardNum  =14;
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
		

	cout<<"       ";
	cout<<"┃    ┃";
	for (i=0;i<num;i++)
	cout<<"       ";
	cout<<"┃    ┃";
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
	
}

void ShowCard(int* card){
		cout<<endl<<endl<<endl;
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
	cout<<endl<<endl<<endl;
	const int num = 31;
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
}


int SingleMod(){
	Game player[3];
	int card1[20],card2[20],cardex[20];
	player[0].ShuffleCard(card1,card2,cardex);
	player[1].SetCard(card1);
	player[2].SetCard(card2);
	player[0].AddCard(cardex);
	int Now=0,Host=0;
	while (1){
		int Pl1=(Now+1)%3,Pl2=(Now+2)%3;
		
		if (Now==Host){
			player[Pl1].ClearPreModel();
			player[Pl2].ClearPreModel();
			player[Now].ClearPreModel();
		}//
		system("clear");
		while (1){	cout<<"[player"<<Host<<"]"<<player[Now].PreModel.ModelName<<endl;;
			cout<<"[player"<<Now<<"]Your card:"<<endl;
			ShowUnderCard();
			ShowCard(player[Now].PreModel.Card);
			ShowOtherCard();


			ShowCard(player[Now].Card);
			int card[20];
			ReadCard(card);
			int flag=player[Now].PlayCard(card);
			if (flag==0){
				if (player[Now].CheckGameEnd()) return 0; 
				player[Pl1].SetPreModel(card);
				player[Pl2].SetPreModel(card);
				Host=Now;	
				break;
			}
			else if (flag==5) break;
			else if (flag==1) cout<<"no model!\n";
			else if (flag==2) cout<<"no engouh card!\n";
			else if (flag==3) cout<<"can't match the premodel!\n";
			else if (flag==4) cout<<"can't win the premodel!\n";
			else cout<<"unexpected error!\n";
		}
		Now=(Now+1)%3;
	}
	return 0;
}

int MultiMod(){
	return 0;
}

void DEBUG_CardModel(){
	while (1){
		int card1[20],card2[20];
		memset(card1,0,sizeof(card1));
		memset(card2,0,sizeof(card2));
		int n;
		cin>>n;
		for (int i=1; i<=n; i++){
			int x;
			cin>>x;
			if (x>=1 && x<=15) card1[x]++;
		}
		CardModel model1(card1);
		cout<<model1.ModelName<<'\n';
		cin>>n;
		for (int i=1; i<=n; i++){
			int x;
			cin>>x;
			if (x>=1 && x<=15) card2[x]++;
		}
		CardModel model2(card2);
		cout<<model2.ModelName<<'\n';
		int cmpres=cmp_CardModel(model1,model2);
		if (cmpres==-1) cout<<"无法比较\n";
		else cout<<"1"<<(cmpres?"<":">=")<<"2\n";
	}
}

int main(){

	// DEBUG_CardModel();
	// DEBUG_Shuffle();
	SingleMod();
	return 0;
}
