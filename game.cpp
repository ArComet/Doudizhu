#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<random>
using namespace std;

#define RANGE 16
/*	卡的范围1-15,
	1-10对应数字卡牌 
	11-13对应J，Q，K，
	14,15对应小王和大王  */

static const int QUEUE[RANGE]={0,3,4,5,6,7,8,9,10,11,12,13,1,2,14,15};
static const int RANK[RANGE]={0,12,13,1,2,3,4,5,6,7,8,9,10,11,14,15};
static const string MODELNAME[RANGE]={"王炸","炸弹","单牌","对子","三张","三带一","三带二","顺子","双顺","三顺","飞机","四带二"};

struct CardModel{
	int Card[RANGE],CardNum;
	int type1,type2,val;
	string ModelName;
	/*	type1牌型 
			0-王炸/火箭 1-炸弹 2-单牌 3-对子 
			4-三张 5-三带一 6-三带二 7-顺子 
			8-双顺 9-三顺 10-飞机 11-四带二 
			-1 error 
		type2牌型附加信息 
		val特征值 								*/
	void check0(){
		if (CardNum!=2) return;
		if (Card[14]==1 && Card[15]==1) type1=0,val=0;
	}
	void check1(){
		if (CardNum!=4) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==4) type1=1,val=RANK[i];
	}
	void check2(){
		if (CardNum!=1) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==1) type1=2,val=RANK[i];	
	}
	void check3(){
		if (CardNum!=2) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==2) type1=3,val=RANK[i];	
	}
	void check4(){
		if (CardNum!=3) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=4,val=RANK[i];	
	}
	void check5(){
		if (CardNum!=4) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=5,val=RANK[i];	
	}
	void check6(){
		if (CardNum!=5) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=6,val=RANK[i];	
	}
	void check7(){
		int l=13,r=1;
		for (int i=1; i<=13; i++)
			if (Card[i]==1){
				if (RANK[i]<l) l=RANK[i];
				if (RANK[i]>r) r=RANK[i];
			}
		if (r-l+1<5) return;
		for (int i=l; i<=r; i++)
			if (Card[QUEUE[i]]!=1) return;
		type1=7;
		type2=r-l+1;
		val=l;
	}
	void check8(){
		int l=13,r=1;
		for (int i=1; i<=13; i++)
			if (Card[i]==2){
				if (RANK[i]<l) l=RANK[i];
				if (RANK[i]>r) r=RANK[i];
			}
		if (r-l+1<3) return;
		for (int i=l; i<=r; i++)
			if (Card[QUEUE[i]]!=2) return;
		type1=8;
		type2=r-l+1;
		val=l;
	}
	void check9(){
		int l=13,r=1;
		for (int i=1; i<=13; i++)
			if (Card[i]==3){
				if (RANK[i]<l) l=RANK[i];
				if (RANK[i]>r) r=RANK[i];
			}
		if (r-l+1<2) return;
		for (int i=l; i<=r; i++)
			if (Card[QUEUE[i]]!=3) return;
		type1=9;
		type2=r-l+1;
		val=l;
	}
	void check10(){
		int l=13,r=1;
		for (int i=1; i<=13; i++)
			if (Card[i]==3){
				if (RANK[i]<l) l=RANK[i];
				if (RANK[i]>r) r=RANK[i];
			}
		if (r-l+1<2) return;
		for (int i=l; i<=r; i++)
			if (Card[QUEUE[i]]!=3) return;
		int single_cnt=0;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==1) single_cnt++;
		if (single_cnt!=r-l+1) return; 
		type1=10;
		type2=r-l+1;
		val=l;
	}
	void check11(){
		if (CardNum!=6) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==4) type1=11,val=RANK[i];	
	}
	void TypeCheck(){
		type1=-1;type2=0;
		check0();check1();check2();
		check3();check4();check5();
		check6();check7();check8();
		check9();check10();check11();
	}
	CardModel(int _Card[RANGE]){
		CardNum=0;
		for (int i=1; i<RANGE; i++){
			Card[i]=_Card[i];
			CardNum+=Card[i];
		}
		TypeCheck();
		if (type1==-1) ModelName="无对应牌型";
		else ModelName=MODELNAME[type1];
	}
	// -1:can't_cmp  0:>=  1:<
	friend int cmp_CardModel(CardModel a,CardModel b){
		if (a.type1==0){
			return 0;
		}
		if (a.type1==1){
			if (b.type1==0 || (b.type1==1 && b.val>=a.val)) return 0;
			else return 1;
		}
		if (a.type1!=b.type1 || a.type2!=b.type2) return -1;
		return a.val<b.val;
	}
}; 

struct Game{
	int Card[RANGE];
	void ShuffleCard(int Card1[RANGE],int Card2[RANGE]){
		for (int i=1; i<RANGE; i++) Card[i]=Card1[i]=Card2[i]=0;
		int Deck[60];
		for (int i=1; i<=13; i++)
			for (int j=0; j<4; j++) 
				Deck[4*(i-1)+j]=i;
		Deck[52]=14;
		Deck[53]=15;
		srand(time(0));
		random_shuffle(Deck,Deck+54);
		for (int i=0; i<17; i++) Card[Deck[i]]++;
		for (int i=17; i<17+17; i++) Card1[Deck[i]]++;
		for (int i=17+17; i<17+17+17; i++) Card2[Deck[i]]++;
	}
	void SetCard(int _Card[RANGE]){
		for (int i=1; i<RANGE; i++) Card[i]=_Card[i];
	}
	void DEBUG_Card(){
		for (int i=1; i<RANGE; i++)
			for (int j=1; j<=Card[i]; j++)
				cout<<i<<' ';
		cout<<endl;
	}
};
