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
static const string MODELNAME[RANGE]={"王炸","炸弹","单牌","对子","三张","三带一","三带二","顺子","双顺","三顺","飞机","四带二","NULL"};

struct CardModel{
	int Card[RANGE],CardNum;
	int type1,type2,val;
	string ModelName;
	/*	type1牌型 
			0-王炸/火箭 1-炸弹 2-单牌 3-对子 
			4-三张 5-三带一 6-三带二 7-顺子 
			8-双顺 9-三顺 10-飞机 11-四带二 
			12 NULL -1 error 
		type2牌型附加信息 
		val特征值 								*/
	//检查 0-王炸/火箭
	void check0(){
		if (CardNum!=2) return;
		if (Card[14]==1 && Card[15]==1) type1=0,val=0;
	}
	//检查 1-炸弹
	void check1(){
		if (CardNum!=4) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==4) type1=1,val=RANK[i];
	}
	//检查 2-单牌
	void check2(){
		if (CardNum!=1) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==1) type1=2,val=RANK[i];	
	}
	//检查 3-对子
	void check3(){
		if (CardNum!=2) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==2) type1=3,val=RANK[i];	
	}
	//检查 4-三张
	void check4(){
		if (CardNum!=3) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=4,val=RANK[i];	
	}
	//检查 5-三带一
	void check5(){
		if (CardNum!=4) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=5,val=RANK[i];	
	}
	//检查 6-三带二
	void check6(){
		if (CardNum!=5) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==3) type1=6,val=RANK[i];	
	}
	//检查 7-顺子
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
	//检查 8-双顺
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
	//检查 9-三顺
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
	//检查 10-飞机
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
	//检查 11-四带二
	void check11(){
		if (CardNum!=6) return;
		for (int i=1; i<RANGE; i++)
			if (Card[i]==4) type1=11,val=RANK[i];	
	}
	//检查 12 NULL
	void check12(){
		if (CardNum!=0) return;
		type1=12;
	}
	//调用所有的检查函数，确定当前牌型
	void TypeCheck(){
		type1=-1;type2=0;
		check0();check1();check2();
		check3();check4();check5();
		check6();check7();check8();
		check9();check10();check11();
		check12();
	}
	//空构造函数
	CardModel(){
		CardNum=0;
		for (int i=1; i<RANGE; i++) Card[i]=0;
		type1=12;
		ModelName="NULL";
	}
	//构造函数，由输入的数组生成对应牌型
	CardModel(int _Card[RANGE]){
		CardNum=0;
		for (int i=1; i<RANGE; i++){
			Card[i]=_Card[i];
			CardNum+=Card[i];
		}
		TypeCheck();
		if (type1==-1) ModelName="无对应牌型";
		else ModelName=MODELNAME[type1];//由type1确定牌型名
	}
	// -1:无法比较  0:>=  1:<
	friend int cmp_CardModel(CardModel a,CardModel b){
		if (a.type1==12){
			if (b.type1==12) return 0;
			else return 1;
		}
		if (a.type1==0) return 0;
		if (a.type1==1){
			if (b.type1==0 || (b.type1==1 && b.val>=a.val)) return 0;
			else return 1;
		}
		if (b.type1==0 || b.type1==1) return 1;
		if (a.type1!=b.type1 || a.type2!=b.type2) return -1;
		return a.val<b.val;
	}
}; 

struct Game{
	int Card[RANGE];
	CardModel PreModel;
	int PrePlayer;
	bool flag_lord;
	//构造函数，清空Card和PreModel
	Game(){
		for (int i=1; i<RANGE; i++) Card[i]=0;
		PreModel=CardModel();
		PrePlayer=-1;
	}
	/*	洗牌发牌函数，由某一玩家调用，传入两个数组，
		调用后设置此玩家的Card，并其他玩家的Card保存在参量中导出
		其他玩家调用SetCard将Card信息导入			*/
	void ShuffleCard(int Card1[RANGE],int Card2[RANGE],int Cardex[RANGE]){
		for (int i=1; i<RANGE; i++) 
			Card[i]=Card1[i]=Card2[i]=Cardex[i]=0;//清空
		int Deck[60];
		for (int i=1; i<=13; i++)//数值1-13
			for (int j=0; j<4; j++)//每种4张
				Deck[4*(i-1)+j]=i;
		Deck[52]=14;//小王
		Deck[53]=15;//大王
		srand(time(0));//取当前时间为随机种子
		random_shuffle(Deck,Deck+54);//对54张牌随机重排
		int NUM=17;
		for (int i=0*NUM; i<1*NUM; i++) Card[Deck[i]]++;//0-16发给此玩家
		for (int i=1*NUM; i<2*NUM; i++) Card1[Deck[i]]++;//17-33发给1
		for (int i=2*NUM; i<3*NUM; i++) Card2[Deck[i]]++;//34-50发给2
		for (int i=3*NUM; i<54; i++) Cardex[Deck[i]]++;
	}
	void SetCard(int _Card[RANGE]){
		for (int i=1; i<RANGE; i++) Card[i]=_Card[i];
	}
	void AddCard(int _Card[RANGE]){
		for (int i=1; i<RANGE; i++) Card[i]+=_Card[i];
	}
	void SetPreModel(int _Card[RANGE],int Player=-1){
		PreModel=CardModel(_Card);
		PrePlayer=Player;
	}
	void ClearPreModel(){
		PreModel=CardModel();
	}
	bool Model_in_Hand(CardModel model){
		if (model.type1==-1) return false;
		for (int i=1; i<RANGE; i++)
			if (model.Card[i]>Card[i]) return false;
		return true;
	}
	int PlayCard(int _Card[RANGE]){
		CardModel model(_Card);
		if (model.type1==-1) return 1;
		if (model.type1==12) return 5;
		if (!Model_in_Hand(model)) return 2;
		if (cmp_CardModel(PreModel,model)==-1) return 3;
		if (cmp_CardModel(PreModel,model)==0) return 4;
		for (int i=1; i<RANGE; i++)
			Card[i]-=model.Card[i];
		return 0;
	}
	bool CheckGameEnd(){
		for (int i=1; i<RANGE; i++) 
			if (Card[i]!=0) return false;
		return true;
	}
	void DEBUG_Card(){
		for (int i=1; i<RANGE; i++)
			for (int j=1; j<=Card[i]; j++)
				cout<<i<<' ';
		cout<<endl;
	}
};
