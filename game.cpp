#include<stdio.h>
#include<algorithm>

#define RANGE 16
/*	卡的范围1-15,
	1-10对应数字卡牌 
	11-13对应J，Q，K，
	14,15对应小王和大王  */

static const int RANK[RANGE]={0,12,13,1,2,3,4,5,6,7,8,9,10,11,14,15};
static const int QUEUE[RANGE]={0,3,4,5,6,7,8,9,10,11,12,13,1,2,14,15};

struct CardModel{
	int Card[RANGE],CardNum;
	int type1,type2,val;
	/*	type1牌型 
			0-王炸/火箭 1-炸弹 2-单牌 3-对子 
			4-三张 5-三带一 6-三带二 7-顺子 
			8-双顺 9-三顺子 10-飞机 11-四带二 
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
			if (Card[i]==4) type1=1,val=i;
	}
	void check2(){
		if (CardNum!=1) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==1) type1=2,val=i;	
	}
	void check3(){
		if (CardNum!=2) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==2) type1=3,val=i;	
	}
	void check4(){
		if (CardNum!=3) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=4,val=i;	
	}
	void check5(){
		if (CardNum!=4) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=5,val=i;	
	}
	void check6(){
		if (CardNum!=5) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=6,val=i;	
	}
	void check7(){
		int l,r;
		for (int i=1; i<=13; i++)
			if (Card[i]==1){
				if (RANK[i]<l) l=RANK[i];
				if (RANK[i]>r) r=RANK[i];
			}
		for (int i=l; i<=r; i++)
			if (Card[QUEUE[i]]!=1) return;
		type1=7;
		type2=r-l+1;
		val=Card[QUEUE[l]];
	}
	void check8(){
		int l,r;
		for (int i=1; i<=13; i++)
			if (Card[i]==2){
				if (RANK[i]<l) l=RANK[i];
				if (RANK[i]>r) r=RANK[i];
			}
		for (int i=l; i<=r; i++)
			if (Card[QUEUE[i]]!=2) return;
		type1=8;
		type2=r-l+1;
		val=Card[QUEUE[l]];
	}
	void TypeCheck(){
		check0();check1();check2();
		check3();check4();check5();
		check6();check7();check8();
		// check9();check10();check11();
		type1=-1;
	}
	CardModel(int _Card[RANGE]){
		CardNum=0;
		for (int i=1; i<=RANGE; i++){
			Card[i]=_Card[i];
			CardNum+=Card[i];
		}
		TypeCheck();
	}
	friend bool operator <(CardModel a,CardModel b){
		
	}
}; 

struct HandCard{
	
};

struct Game{
	
};
