#include<stdio.h>
#include<string.h>
#include "game.cpp"

int SingleMod(){
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

	 DEBUG_CardModel();
	// DEBUG_Shuffle();

	return 0;
}
