#include<bits/stdc++.h>
using namespace std;
string cards[55];//牌组 
int washCard_1;// 洗牌变量1 
int washCard_2;// 洗牌变量2
string TempCard;//临时牌变量，用于洗牌做替换时临时存储 
string MyCard[6];//玩家的牌 
string AI1Card[6];//AI1的牌 
string AI2Card[6];//AI2的牌 
string Master="Me";//庄家 
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
	/*        洗牌         */ 
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
	cout<<"第"<<i<<"张："<<AI2Card[i]<<endl;*/
	
	/*      排序           */
    auto cmp = [](const string &a, const string &b) {
        map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["小王"] = 14; rank["大王"] = 15; rank["广告"] = 16;
        return rank[a] < rank[b];
    };// 对牌进行排序
    sort(MyCard, MyCard+6, cmp);
    sort(AI1Card, AI1Card+6, cmp);
    sort(AI2Card, AI2Card+6, cmp);

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
    
    /*     出牌        */
	 
}
