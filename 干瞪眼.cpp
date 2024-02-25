#include<bits/stdc++.h>
#include<windows.h>
#include<sstream>
#include "干瞪眼.h"
using namespace std;

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
	cout<<"| 1.可以正常出牌，且只能出单张和对子（可带百搭）      |"<<endl; 
	cout<<"| 2.修复了已知bug                                     |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 
	cout<<"|                     游戏选项                        |"<<endl;	
    cout<<"| 1.开始游戏                                          |"<<endl; 
	cout<<"| 2.请等待下一个版本                                  |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 	
	cout<<"| InfDev1.4                                           |"<<endl;
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
 		if(passtime==2&&!Started_Game_Or_Not&&Card_Is_Valid){
 			New_Card_Void(MyCard);
 			range_cards();
		 }
		 Started_Game_Or_Not=0;
		cout << "我的牌：" << endl;
        for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << MyCard[i] << endl;
 		}

    // 测试AI1 AI2 的牌&&调试信息 
	cout << "AI1的牌：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << AI1Card[i] << endl;
    }

    cout << "AI2的牌：" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "第" << i+1 << "张：" << AI2Card[i] << endl;
    } 
    cout<<"上一次出的牌："<<Last_Cards[0]<<Last_Cards[1]<<Last_Cards[2]<<Last_Cards[3]<<Last_Cards[4]<<Last_Cards[5]<<endl;
    cout<<"不出次数:"<<passtime<<endl;
    cout<<"出牌张数："<<Cards_Be_Chosen_Num<<endl;
	//*/
	 
 		cout<<"你选择出第几张？>>>";
 		for(int i=0;i<=5;i++)Cards_Be_Chosen[i]="";
		Cards_Be_Chosen_Num=0;
		//choice_in_game_num=-1;
		while(cin>>choice_in_game_num){
            if(choice_in_game_num==-1||choice_in_game_num==-2){ 
                if(choice_in_game_num==-2) pass_or_not=1;
            	break;
			}
			else if(choice_in_game_num<-2){
				cout<<"无效选择！请重新输入"<<endl;
				Card_Is_Valid=0;
				Sleep(3000);
				system("cls");
				goto CardFlag; 
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
				Card_Is_Valid=1;
				passtime=0;
			    Player_Cards_Update(MyCard);//更新牌 
			    range_cards();//理牌 
			    Last_Cards[0]=Cards_Be_Chosen[0];
			}
            else{
            	cout<<"出牌不合法！"<<endl;
            	Card_Is_Valid=0;
				Sleep(5000);
			    system("cls");
				goto CardFlag;
			}
		}
		else if(Cards_Be_Chosen_Num==2){
			if(DoubleCardsIsValid(Last_Cards[0],Last_Cards[1],Cards_Be_Chosen[0],Cards_Be_Chosen[1],passtime)){
				Card_Is_Valid=1;
				passtime=0;
				Player_Cards_Update(MyCard); 
				range_cards();
				Last_Cards[0]=Cards_Be_Chosen[0];
				Last_Cards[1]=Cards_Be_Chosen[1];
			}
			else{//现在只考虑单张
		    cout<<"出牌不合法！"<<endl;
		    Card_Is_Valid=0;
			Sleep(5000);
			system("cls");
			goto CardFlag;
	    }
		}
		/* TODO
		else if(Cards_Be_CHosen_Num>=3){
			if(Bomb_Or_not(Last_Cards[0],Last_cards[1],Last_cards[2],Cards_Be_Chosen[0],Cards_Be_Chosen[1],Cards_Be_Chosen[2])){
				
			}
			else if(Straight_Or_not())
		} */
		else{//现在只考虑单张
		    cout<<"出牌不合法！"<<endl;
		    Card_Is_Valid=0;
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
	    	cout<<"不出次数:"<<passtime<<endl;//测试不出次数 
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
			cout<<"不出次数:"<<passtime<<endl;//测试不出次数 
	    	cout<<"你选择出："<<Cards_Be_Chosen[0]<<" "<<Cards_Be_Chosen[1]<<" "<<Cards_Be_Chosen[2]<<" "<<Cards_Be_Chosen[3]<<" "<<Cards_Be_Chosen[4]<<" "<<Cards_Be_Chosen[5]<<endl;
		    cout<<"机器人1出牌：";
		    for(int j=0;j<=5;j++)cout<<AI1_push[j];
		    cout<<endl;
			cout<<"正在等待机器人2出牌……"<<i<<"秒"<<endl;
			Sleep(1000);
			system("cls");
			}
        system("cls");
		cout<<"机器人1出牌：";
		for(int j=0;j<=5;j++)cout<<AI1_push[j];
		cout<<endl;
		cout<<"机器人2出牌：";
		for(int j=0;j<=5;j++)cout<<AI2_push[j];
		cout<<endl;
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
