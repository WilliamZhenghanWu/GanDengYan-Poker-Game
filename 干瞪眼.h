#include<bits/stdc++.h>
#include<windows.h>
#include<sstream>
using namespace std;

/*       定义变量         */ 

string cards[55];//牌组 
int washCard_1;// 洗牌变量1 
int washCard_2;// 洗牌变量2
string TempCard;//临时牌变量，用于洗牌做替换时临时存储 
string MyCard[6];//玩家的牌 
string AI1Card[6];//AI1的牌 
string AI2Card[6];//AI2的牌 
string Master="Me";//庄家
int choice=-1;//开始界面选项 
int choice_in_game_num;//转换为数字的游戏中出牌选项 
string Cards_Be_Chosen[6];//被选中的牌
int Cards_Be_Chosen_Num;//在循环中用于计数 
string Last_Cards[6]={"None"};//上家出的牌，用于比较
int New_Card=16;//摸牌 
string AI1_push[6];//AI打的牌，下一个同上， 
string AI2_push[6];
int passtime=0;//不出的次数 
bool pass_or_not;//是否不出 
bool Started_Game_Or_Not=1;//判断是否开始游戏 
bool Card_Is_Valid;//判断牌是否合法 
/* 理牌函数 */
/* 摸牌 */

void New_Card_Void(string Card[]){
    Card[0]=cards[New_Card];
    New_Card++;
};

void range_cards(){
    auto cmp = [](const string &a, const string &b) {
        map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["小王"] = 0; rank["大王"] = 0; rank["广告"] = 0;
        return rank[a] < rank[b];
    };// 对牌进行排序
    sort(MyCard, MyCard+6, cmp);
    sort(AI1Card, AI1Card+6, cmp);
    sort(AI2Card, AI2Card+6, cmp);
};

/* 单张牌是否符合逻辑函数 */

bool SingleCardIsValid(const string &OthersCard, const string &OnesCard,int &passtime){
        map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["小王"] = -1; rank["大王"] = -1; rank["广告"] = -1;
        if(OnesCard=="") return 0;
        else if(rank[OnesCard]-rank[OthersCard]==1)	return 1;
		else if(rank[OnesCard]==-1) return 0; 
        else if(OnesCard=="2"&&OthersCard!="2") return 1;
        else if(passtime>=2) return 1;
		else if(OthersCard=="None") return 1;
        else return 0;
};

/* 对子是否符合逻辑 */

bool DoubleCardsIsValid(const string &OthersCard1,const string &OthersCard2,const string &OnesCard1,const string &OnesCard2,int &passtime){
	    map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["小王"] = -1; rank["大王"] = -1; rank["广告"] = -1;
        if((OnesCard1!=OnesCard2&&rank[OnesCard1]!=-1&&rank[OnesCard2]!=-1)||(OnesCard1==""||OnesCard2=="")) return 0;
        else if(rank[OnesCard1]==-1&&rank[OnesCard2]==-1) return 0;
        else{
        	if(passtime>=2) return 1;
        	else if(OthersCard2!=OthersCard1&&rank[OthersCard1]!=-1&&rank[OthersCard2]!=-1) return 0;
        	else if(((OnesCard1=="2"&&OnesCard2=="2")||(rank[OnesCard1]==-1&&OnesCard2=="2")||(rank[OnesCard2]==-1&&OnesCard1=="2"))&&OthersCard1!="2"&&OthersCard2!="2") return 1;
			else if((rank[OnesCard1]-1==rank[OthersCard1]&&rank[OnesCard2]-1==rank[OthersCard2])||(rank[OnesCard1]-1==rank[OthersCard1]&&rank[OnesCard2]==-1)||(rank[OnesCard1]==-1&&rank[OnesCard2]-1==rank[OthersCard2])||(rank[OnesCard1]-1==rank[OthersCard2]&&rank[OnesCard2]==-1)||(rank[OnesCard2]-1==rank[OthersCard1]&&rank[OnesCard1]==-1)) return 1;
			else return 0;
		}
};
/* AI出牌 */

void AI1_Push_Cards(){//AI1逻辑（写的有点不耐烦了） //已重构，暴力求解 
    if(passtime==2) New_Card_Void(AI1Card); 
    for(int i=0;i<=5;i++) AI1_push[i]=""; 
    
    if(Cards_Be_Chosen_Num==2||passtime==2){
	    for(int i=0;i<=5;i++){
		for(int j=0;j<=5;j++){
			if(i==j)continue;
			else if(DoubleCardsIsValid(Last_Cards[0],Last_Cards[1],AI1Card[i],AI1Card[j],passtime)){
				Cards_Be_Chosen_Num=2;
				passtime=0;
		        AI1_push[0]=AI1Card[i];
			    AI1_push[1]=AI1Card[j];
		        AI1Card[i]="";AI1Card[j]="";
		        Last_Cards[0]=AI1_push[0];Last_Cards[1]=AI1_push[1];
		        range_cards();
		        return;
			}
		}
	    }
	}
	
	if(Cards_Be_Chosen_Num==1||passtime==2){
    for(int i=0;i<=5;i++){
    	if(SingleCardIsValid(Last_Cards[0],AI1Card[i],passtime)){
    		Cards_Be_Chosen_Num=1;
    		passtime=0;
		    AI1_push[0]=AI1Card[i];
		    AI1Card[i]="";
		    Last_Cards[0]=AI1_push[0];
		    range_cards();
		    return;
		}
	}
    }
    
	AI1_push[0]="不出";
	passtime++;
};

void AI2_Push_Cards(){//AI2逻辑（写的有点不耐烦了） //已重构，暴力求解 
    if(passtime==2) New_Card_Void(AI2Card); 
    for(int i=0;i<=5;i++) AI2_push[i]=""; 
    
    if(Cards_Be_Chosen_Num==2||passtime==2){
	    for(int i=0;i<=5;i++){
		for(int j=0;j<=5;j++){
			if(i==j)continue;
			else if(DoubleCardsIsValid(Last_Cards[0],Last_Cards[1],AI2Card[i],AI2Card[j],passtime)){
				Cards_Be_Chosen_Num=2;
				passtime=0;
		        AI2_push[0]=AI2Card[i];
			    AI2_push[1]=AI2Card[j];
		        AI2Card[i]="";AI2Card[j]="";
		        Last_Cards[0]=AI2_push[0];Last_Cards[1]=AI2_push[1];
		        range_cards();
		        return;
			}
		}
	    }
	}
	
	if(Cards_Be_Chosen_Num==1||passtime==2){
    for(int i=0;i<=5;i++){
    	if(SingleCardIsValid(Last_Cards[0],AI2Card[i],passtime)){
    		Cards_Be_Chosen_Num=1;
    		passtime=0;
		    AI2_push[0]=AI2Card[i];
		    AI2Card[i]="";
		    Last_Cards[0]=AI2_push[0];
		    range_cards();
		    return;
		}
	}
    }
    
	AI2_push[0]="不出";
	passtime++;
};

int AI1Hand(){//AI1还剩的牌 
	int cnt=0;//计数器 
    for(int i=0;i<=5;i++){
    	if(AI1Card[i]!="")cnt++;
	}
	return cnt; 
};

int AI2Hand(){//AI2还剩的牌 
	int cnt=0;//计数器 
    for(int i=0;i<=5;i++){
    	if(AI2Card[i]!="")cnt++;
	}
	return cnt; 
};

/* 更新手牌 */

void Player_Cards_Update(string MyCard[]){
    // 从玩家手牌中删除用户选中的牌
    string NewHand[6];
    int NewHandSize = 0;
    bool removed[6] = {false};
    for (int i = 0; i < 6; i++) {
        bool chosen = false;
        for (int j = 0; j < Cards_Be_Chosen_Num; j++) {//判断牌是否被选中，并标记 
            if (MyCard[i] == Cards_Be_Chosen[j] && !removed[j]) {
                chosen = true;
                removed[j] = true;
                break;
            }
        }
        if (!chosen) {//删除 
            NewHand[NewHandSize] = MyCard[i];
            NewHandSize++;
        }
        else{
        	NewHand[NewHandSize] = "";
        	NewHandSize++;
		}
	}

    // 更新玩家手牌
    for (int i = 0; i < NewHandSize; i++) {
        MyCard[i] = NewHand[i];
    }
};

void startGame(){
	/*        洗牌         */
	for(int j=0;j<=5;j++){
		MyCard[j]="";
	}
	for(int j=0;j<=5;j++){
		AI1Card[j]="";
	}
	for(int j=0;j<=5;j++){
		AI2Card[j]="";
	}
	
	
	srand(time(0));//将时间设为随机种子 
	for(int i=1;i<=rand();i++){
	    int washCard_1=rand()%55;//将其取0-54的随机数 
        int washCard_2=rand()%55;
        if(washCard_1==washCard_2)continue;//两者相等洗牌相当于没洗 
		else{
		   TempCard=cards[washCard_1];
		   cards[washCard_1]=cards[washCard_2];
		   cards[washCard_2]=TempCard;
		   //随机选两张牌进行互换，重复该操作实现洗牌 
		}
		} 
	
	/*测试洗牌是否正确 
	for(int i=0;i<=54;i++)
	cout<<"第"<<i<<"张牌："<<cards[i]<<endl;
    return 0;*/
    
    /*     发牌      */
    
    if(Master=="Me"){
	    MyCard[0]=cards[0];
	    AI1Card[0]=cards[1];
	    AI2Card[0]=cards[2];
	    MyCard[1]=cards[3];
	    AI1Card[1]=cards[4];
	    AI2Card[1]=cards[5];
	    MyCard[2]=cards[6];
	    AI1Card[2]=cards[7];
	    AI2Card[2]=cards[8];
	    MyCard[3]=cards[9];
	    AI1Card[3]=cards[10];
	    AI2Card[3]=cards[11];
	    MyCard[4]=cards[12];
	    AI1Card[4]=cards[13];
	    AI2Card[4]=cards[14];
	    MyCard[5]=cards[15];
    }
    
	if(Master=="AI1"){
		AI1Card[0]=cards[0];
	    AI2Card[0]=cards[1];
	    MyCard[0]=cards[2];
	    AI1Card[1]=cards[3];
	    AI2Card[1]=cards[4];
	    MyCard[1]=cards[5];
	    AI1Card[2]=cards[6];
	    AI2Card[2]=cards[7];
	    MyCard[2]=cards[8];
	    AI1Card[3]=cards[9];
	    AI2Card[3]=cards[10];
	    MyCard[3]=cards[11];
	    AI1Card[4]=cards[12];
	    AI2Card[4]=cards[13];
	    MyCard[4]=cards[14];
	    AI1Card[5]=cards[15];
    }
    
    if(Master=="AI2"){
		AI2Card[0]=cards[0];
	    MyCard[0]=cards[1];
	    AI1Card[0]=cards[2];
	    AI2Card[1]=cards[3];
	    MyCard[1]=cards[4];
	    AI1Card[1]=cards[5];
	    AI2Card[2]=cards[6];
	    MyCard[2]=cards[7];
	    AI1Card[2]=cards[8];
	    AI2Card[3]=cards[9];
	    MyCard[3]=cards[10];
	    AI1Card[3]=cards[11];
	    AI2Card[4]=cards[12];
	    MyCard[4]=cards[13];
	    AI1Card[4]=cards[14];
	    AI2Card[5]=cards[15];
    }
	/*测试发牌是否正确 
	cout<<"我的牌："<<endl;
	for(int i=0;i<=5;i++)
	cout<<"第"<<i<<"张："<<MyCard[i]<<endl;
	
	cout<<"AI1的牌："<<endl;
	for(int i=0;i<=5;i++)
	cout<<"第"<<i<<"张："<<AI1Card[i]<<endl;
	
	cout<<"AI2的牌："<<endl;
	for(int i=0;i<=5;i++)
	cout<<"第"<<i<<"张："<<AI2Card[i]<<endl;
	Sleep(10000);*/
	
	/*      排序           */
	range_cards();

    /*测试排序后的牌是否正常 
    cout << "我的牌：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << MyCard[i] << endl;
    }

    cout << "AI1的牌：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << AI1Card[i] << endl;
    }

    cout << "AI2的牌：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << AI2Card[i] << endl;
    }
	Sleep(10000);*/
}

