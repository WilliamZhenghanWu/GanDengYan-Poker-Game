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
string AI1_push;//AI打的牌，下一个同上，仅限单牌 
string AI2_push;
int passtime=0;//不出的次数 
bool pass_or_not;//是否不出 
/* 理牌函数 */

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
        if(rank[OnesCard]-rank[OthersCard]==1)	return 1;
		else if(rank[OnesCard]==-1) return 0; 
        else if(OnesCard=="2"&&OthersCard!="2") return 1;
        else if(passtime>=2) return 1;
		else if(OthersCard=="None") return 1;
        else return 0;
};


/* AI出牌 */

void AI1_Push_Cards(){//AI1逻辑（写的有点不耐烦了） 
    AI1_push="";
	if(Cards_Be_Chosen_Num==1){
		map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["小王"] = -1; rank["大王"] = -1; rank["广告"] = -1;rank[""] = -100;
		if(passtime==2){
			for(int i=0;i<=5;i++)
			if(AI1Card[i]!=""&&AI1Card[i]!="小王"&&AI1Card[i]!="大王"&&AI1Card[i]!="广告"){
			passtime=0;
		    AI1_push=AI1Card[i];
		    AI1Card[i]="";
	    	Last_Cards[0]=AI1_push;
		    range_cards();
		    return;
	        }
		}
		else{
	for(int i=0;i<6;i++){ 
		if(rank[AI1Card[i]]-rank[Last_Cards[0]]==1||(AI1Card[i]=="2"&&Last_Cards[0]!="2")){
		passtime=0;
		AI1_push=AI1Card[i];
		AI1Card[i]="";
		Last_Cards[0]=AI1_push;
		range_cards();
		return;
		}
	}
	AI1_push="不出";
	passtime++;
	return;
}
	}

};

void AI2_Push_Cards(){//AI2逻辑（写的有点不耐烦了） 
    AI2_push="";
	if(Cards_Be_Chosen_Num==1){
    map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["小王"] = -1; rank["大王"] = -1; rank["广告"] = -1;rank[""] = -100;
        if(passtime==2){
			for(int i=0;i<=5;i++)
			if(AI2Card[i]!=""&&AI2Card[i]!="小王"&&AI2Card[i]!="大王"&&AI2Card[i]!="广告"){
			passtime=0;
		    AI2_push=AI2Card[i];
		    AI2Card[i]="";
	    	Last_Cards[0]=AI2_push;
		    range_cards();
		    return;
	        }
	    }
	    else{
	for(int i=0;i<6;i++){
		if(rank[AI2Card[i]]-rank[Last_Cards[0]]==1||(AI2Card[i]=="2"&&Last_Cards[0]!="2")){
		passtime=0;
		AI2_push=AI2Card[i];
		AI2Card[i]="";
		Last_Cards[0]=AI2_push;
		range_cards();
		return;
		}
		}
		AI2_push="不出";
		passtime++;
		return;
	}
	}
};

/* 摸牌 */

void New_Card_Void(string Card[]){
    Card[1]=cards[New_Card];
    New_Card++;
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
    }*/
}

int main(){
	
	/*      创建牌组       */
	
	cards[0]="3";
	cards[1]="3";
	cards[2]="3";
	cards[3]="3";
	cards[4]="4";
	cards[5]="4";
	cards[6]="4";
	cards[7]="4";
	cards[8]="5";
	cards[9]="5";
	cards[10]="5";
	cards[11]="5";
	cards[12]="6";
	cards[13]="6";
	cards[14]="6";
	cards[15]="6";
	cards[16]="7";
	cards[17]="7";
	cards[18]="7";
	cards[19]="7";
	cards[20]="8";
	cards[21]="8";
	cards[22]="8";
	cards[23]="8";
	cards[24]="9";
	cards[25]="9";
	cards[26]="9";
	cards[27]="9";
	cards[28]="10";
	cards[29]="10";
	cards[30]="10";
	cards[31]="10";
	cards[32]="J";
	cards[33]="J";
	cards[34]="J";
	cards[35]="J";
	cards[36]="Q";
	cards[37]="Q";
	cards[38]="Q";
	cards[39]="Q";
	cards[40]="K";
	cards[41]="K";
	cards[42]="K";
	cards[43]="K";
	cards[44]="A";
	cards[45]="A";
	cards[46]="A";
	cards[47]="A";
	cards[48]="2";
	cards[49]="2";
	cards[50]="2";
    cards[51]="2";
    cards[52]="小王";
	cards[53]="大王";
	cards[54]="广告";

    /*     开始逻辑        */
    
    while(1){
    startGame();
    system("color 03");//设置颜色 
    system("cls");
    cout<<"_______________________________________________________"<<endl; //开始界面 
	cout<<"|                    干瞪眼游戏                       |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 	
	cout<<"|                     更新日志                        |"<<endl; 
	cout<<"| 1.现在在游戏中可以正常出牌，且只能出单张            |"<<endl; 
	cout<<"| 2.修复了已知bug                                     |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 
	cout<<"|                     游戏选项                        |"<<endl;	
    cout<<"| 1.开始游戏                                          |"<<endl; 
	cout<<"| 2.请等待下一个版本                                  |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 	
	cout<<"| InfDev1.2                                           |"<<endl;
	cout<<"-------------------------------------------------------"<<endl; 
	cout<<">>>";
	cin>>choice;
	if(choice==1){
	    //开始游戏 
	    startGame();
	    Last_Cards[0]="None";
	    passtime=2;
	    while(choice){
	    if(Master=="Me"){//先只考虑玩家是庄家的情况 
        system("cls");
 		CardFlag:
		cout << "我的牌：" << endl;
        for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << MyCard[i] << endl;
 		}

    // 测试AI1 AI2 的牌
	cout << "AI1的牌：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << AI1Card[i] << endl;
    }

    cout << "AI2的牌：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << AI2Card[i] << endl;
    } 
    cout<<"上一次出的牌："<<Last_Cards[0]<<endl;
    cout<<"不出次数"<<passtime<<endl;
	//
	 
 		cout<<"你选择出第几张？>>>";
 		for(int i=0;i<=5;i++)Cards_Be_Chosen[i]="";
		Cards_Be_Chosen_Num=0;
		//choice_in_game_num=-1;
		while(cin>>choice_in_game_num){
            if(choice_in_game_num==-1||choice_in_game_num==-2){ 
                if(choice_in_game_num==-2) pass_or_not=1;
            	break;
			}
			Cards_Be_Chosen[Cards_Be_Chosen_Num]=MyCard[choice_in_game_num-1];
		    Cards_Be_Chosen_Num++;	
		}
		
		/*测试牌是否被正确选中 
		for(int i=0;i<=5;i++)
		cout<<"被选中的第"<<i+1<<"张牌："<<Cards_Be_Chosen[i]<<endl;
		Sleep(5000);
		*/
		if(choice_in_game_num==-2&&passtime!=2) {
			Cards_Be_Chosen[0]="不出";
			Cards_Be_Chosen_Num=1;
			passtime++;
		} 
		else if(Cards_Be_Chosen_Num==1){
			if(SingleCardIsValid(Last_Cards[0],Cards_Be_Chosen[0],passtime)){
				passtime=0;
			    Player_Cards_Update(MyCard);//更新牌 
			    range_cards();//理牌 
			    Last_Cards[0]=Cards_Be_Chosen[0];
			}
            else{
            	cout<<"出牌不合法！"<<endl;
				Sleep(5000);
			    system("cls");
				goto CardFlag;
			}
		}
		else{//现在只考虑单张
		    cout<<"出牌不合法！"<<endl;
			Sleep(5000);
			system("cls");
			goto CardFlag;
	    }
	    //牌类判断 
	    AI1_Push_Cards();
	    AI2_Push_Cards();
	    if(MyCard[0]==""&&MyCard[1]==""&&MyCard[2]==""&&MyCard[3]==""&&MyCard[4]==""&&MyCard[5]==""){//玩家胜利 
	    	system("cls");
			cout<<"你赢了！！！"<<endl;
			Sleep(3000);
			break; 
		}
		system("cls");
	    for(int i=3;i>0;i--){
	    	cout<<"你选择出："<<Cards_Be_Chosen[0]<<" "<<Cards_Be_Chosen[1]<<" "<<Cards_Be_Chosen[2]<<" "<<Cards_Be_Chosen[3]<<" "<<Cards_Be_Chosen[4]<<" "<<Cards_Be_Chosen[5]<<endl;
		    cout<<"正在等待机器人1出牌……"<<i<<"秒"<<endl;
		    Sleep(1000);
			system("cls");
		}
		if(AI1Card[0]==""&&AI1Card[1]==""&&AI1Card[2]==""&&AI1Card[3]==""&&AI1Card[4]==""&&AI1Card[5]==""){//玩家胜利 
	    	system("cls");
			cout<<"机器人1赢了！！！下次祝你好运！"<<endl;
			Sleep(3000);
			break; 
		}
		for(int i=3;i>0;i--){
	    	cout<<"你选择出："<<Cards_Be_Chosen[0]<<" "<<Cards_Be_Chosen[1]<<" "<<Cards_Be_Chosen[2]<<" "<<Cards_Be_Chosen[3]<<" "<<Cards_Be_Chosen[4]<<" "<<Cards_Be_Chosen[5]<<endl;
		    cout<<"机器人1出牌："<<AI1_push<<endl;
			cout<<"正在等待机器人2出牌……"<<i<<"秒"<<endl;
			Sleep(1000);
			system("cls");
			}
        system("cls");
		cout<<"机器人1出牌："<<AI1_push<<endl;
		cout<<"机器人2出牌："<<AI2_push<<endl;
		if(AI2Card[0]==""&&AI2Card[1]==""&&AI2Card[2]==""&&AI2Card[3]==""&&AI2Card[4]==""&&AI2Card[5]==""){//玩家胜利 
	    	system("cls");
			cout<<"机器人2赢了！！！下次祝你好运！"<<endl;
			Sleep(3000);
			break; 
		}
		goto CardFlag;
    }
    }
	}
	
	
	 
	else if(choice==2){//等待下一个版本 
	    for(int i=3;i>0;i--){
	        system("cls");
	        cout<<"请等待下一个版本！" <<endl;
	        cout<<i<<"秒后回到主界面……"<<endl;
	        Sleep(1000);
	    }
    }
}
}
