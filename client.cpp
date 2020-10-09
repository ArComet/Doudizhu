#include<stdio.h>
#include<string.h>
#include"game.cpp"

void ReadCard(int* card){
	for (int i=1; i<16; i++) card[i]=0;
	int n;
	cin>>n;
	for (int i=1; i<=n; i++){
		int x;
		cin>>x;
		if (x>=1 && x<=15) card[x]++;
	}
}

void ShowCard(int* card){
	for (int i=1; i<16; i++)
		for (int j=1; j<=card[i]; j++)
			cout<<i<<' ';
	cout<<endl;
}

int SingleMod(){
	Game player[3];
	int card1[20],card2[20];
	player[0].ShuffleCard(card1,card2);
	player[1].SetCard(card1);
	player[2].SetCard(card2);

	int Now=0;
	while (1){
		int Pl1=(Now+1)%3,Pl2=(Now+2)%3;
		
		if (player[Pl1].flag_host){
			player[Pl1].NewTurn();
			player[Pl2].NewTurn();
			player[Now].NewTurn();
			player[Now].flag_host=true;
		}
		while (1){
			cout<<"[model]"<<player[Now].PreModel.ModelName;ShowCard(player[Now].PreModel.Card);
			cout<<"[play"<<Now<<"]Your card:";player[Now].DEBUG_Card();
			int card[20];
			ReadCard(card);
			int flag=player[Now].PlayCard(card);
			if (flag==0){
				if (player[Now].CheckGameEnd()) return 0; 
				player[Pl1].SetPreModel(card);
				player[Pl2].SetPreModel(card);	
				break;
			}
			else if (flag==5) break;
			else if (flag==1) cout<<"no model!\n";
			else if (flag==2) cout<<"no engouh card!\n";
			else if (flag==3) cout<<"can't match the premodel!\n";
			else if (flag==4) cout<<"can't win the premodel!\n";
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

void DEBUG_Shuffle(){
	Game player0,player1,player2;
	int card1[20],card2[20];
	player0.ShuffleCard(card1,card2);
	player1.SetCard(card1);
	player2.SetCard(card2);
	player0.DEBUG_Card();
	player1.DEBUG_Card();
	player2.DEBUG_Card();
}

int main(){

	// DEBUG_CardModel();
	// DEBUG_Shuffle();
	SingleMod();
	return 0;
}
