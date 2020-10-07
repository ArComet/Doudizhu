#include<stdio.h>

#define RANGE 16
/*	卡的范围1-15,
	1-10对应数字卡牌 
	11-13对应J，Q，K，
	14,15对应小王和大王  */

struct CardModel{
	int Card[RANGE],CardNum;
	int type1,type2,val;
	/*	type1牌型 
			0-王炸/火箭 1-炸弹 2-单牌 3-对子 
			4-三张 5-三带一 6-三带二 7-顺子 
			8-双顺 9-三顺子 10-飞机 11-四带二  
		type2牌型附加信息 
		val特征值 								*/
	CardModel(int _Card[RANGE]){
		CardNum=0;
		for (int i=1; i<=RANGE; i++){
			Card[i]=_Card[i];
			CardNum+=Card[i];
		}
	}
	friend bool operator <(CardModel a,CardModel b){
		
	}
}; 

struct HandCard{
	
};

struct Game{
	
};
