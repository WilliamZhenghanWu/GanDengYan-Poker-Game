#include<bits/stdc++.h>
#include<windows.h>
#include<sstream>
using namespace std;

/*       �������         */ 

string cards[55];//���� 
int washCard_1;// ϴ�Ʊ���1 
int washCard_2;// ϴ�Ʊ���2
string TempCard;//��ʱ�Ʊ���������ϴ�����滻ʱ��ʱ�洢 
string MyCard[6];//��ҵ��� 
string AI1Card[6];//AI1���� 
string AI2Card[6];//AI2���� 
string Master="Me";//ׯ��
int choice=-1;//��ʼ����ѡ�� 
int choice_in_game_num;//ת��Ϊ���ֵ���Ϸ�г���ѡ�� 
string Cards_Be_Chosen[6];//��ѡ�е���
int Cards_Be_Chosen_Num;//��ѭ�������ڼ��� 
string Last_Cards[6]={"None"};//�ϼҳ����ƣ����ڱȽ�
int New_Card=16;//���� 
string AI1_push[6];//AI����ƣ���һ��ͬ�ϣ� 
string AI2_push[6];
int passtime=0;//�����Ĵ��� 
bool pass_or_not;//�Ƿ񲻳� 
bool Started_Game_Or_Not=1;//�ж��Ƿ�ʼ��Ϸ 
bool Card_Is_Valid;//�ж����Ƿ�Ϸ� 
/* ���ƺ��� */
/* ���� */

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
        rank["2"] = 13; rank["С��"] = 0; rank["����"] = 0; rank["���"] = 0;
        return rank[a] < rank[b];
    };// ���ƽ�������
    sort(MyCard, MyCard+6, cmp);
    sort(AI1Card, AI1Card+6, cmp);
    sort(AI2Card, AI2Card+6, cmp);
};

/* �������Ƿ�����߼����� */

bool SingleCardIsValid(const string &OthersCard, const string &OnesCard,int &passtime){
        map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["С��"] = -1; rank["����"] = -1; rank["���"] = -1;
        if(OnesCard=="") return 0;
        else if(rank[OnesCard]-rank[OthersCard]==1)	return 1;
		else if(rank[OnesCard]==-1) return 0; 
        else if(OnesCard=="2"&&OthersCard!="2") return 1;
        else if(passtime>=2) return 1;
		else if(OthersCard=="None") return 1;
        else return 0;
};

/* �����Ƿ�����߼� */

bool DoubleCardsIsValid(const string &OthersCard1,const string &OthersCard2,const string &OnesCard1,const string &OnesCard2,int &passtime){
	    map<string, int> rank;
        rank["3"] = 1; rank["4"] = 2; rank["5"] = 3; rank["6"] = 4; 
        rank["7"] = 5; rank["8"] = 6; rank["9"] = 7; rank["10"] = 8; 
        rank["J"] = 9; rank["Q"] = 10; rank["K"] = 11; rank["A"] = 12; 
        rank["2"] = 13; rank["С��"] = -1; rank["����"] = -1; rank["���"] = -1;
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
/* AI���� */

void AI1_Push_Cards(){//AI1�߼���д���е㲻�ͷ��ˣ� //���ع���������� 
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
    
	AI1_push[0]="����";
	passtime++;
};

void AI2_Push_Cards(){//AI2�߼���д���е㲻�ͷ��ˣ� //���ع���������� 
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
    
	AI2_push[0]="����";
	passtime++;
};

int AI1Hand(){//AI1��ʣ���� 
	int cnt=0;//������ 
    for(int i=0;i<=5;i++){
    	if(AI1Card[i]!="")cnt++;
	}
	return cnt; 
};

int AI2Hand(){//AI2��ʣ���� 
	int cnt=0;//������ 
    for(int i=0;i<=5;i++){
    	if(AI2Card[i]!="")cnt++;
	}
	return cnt; 
};

/* �������� */

void Player_Cards_Update(string MyCard[]){
    // �����������ɾ���û�ѡ�е���
    string NewHand[6];
    int NewHandSize = 0;
    bool removed[6] = {false};
    for (int i = 0; i < 6; i++) {
        bool chosen = false;
        for (int j = 0; j < Cards_Be_Chosen_Num; j++) {//�ж����Ƿ�ѡ�У������ 
            if (MyCard[i] == Cards_Be_Chosen[j] && !removed[j]) {
                chosen = true;
                removed[j] = true;
                break;
            }
        }
        if (!chosen) {//ɾ�� 
            NewHand[NewHandSize] = MyCard[i];
            NewHandSize++;
        }
        else{
        	NewHand[NewHandSize] = "";
        	NewHandSize++;
		}
	}

    // �����������
    for (int i = 0; i < NewHandSize; i++) {
        MyCard[i] = NewHand[i];
    }
};

void startGame(){
	/*        ϴ��         */
	for(int j=0;j<=5;j++){
		MyCard[j]="";
	}
	for(int j=0;j<=5;j++){
		AI1Card[j]="";
	}
	for(int j=0;j<=5;j++){
		AI2Card[j]="";
	}
	
	
	srand(time(0));//��ʱ����Ϊ������� 
	for(int i=1;i<=rand();i++){
	    int washCard_1=rand()%55;//����ȡ0-54������� 
        int washCard_2=rand()%55;
        if(washCard_1==washCard_2)continue;//�������ϴ���൱��ûϴ 
		else{
		   TempCard=cards[washCard_1];
		   cards[washCard_1]=cards[washCard_2];
		   cards[washCard_2]=TempCard;
		   //���ѡ�����ƽ��л������ظ��ò���ʵ��ϴ�� 
		}
		} 
	
	/*����ϴ���Ƿ���ȷ 
	for(int i=0;i<=54;i++)
	cout<<"��"<<i<<"���ƣ�"<<cards[i]<<endl;
    return 0;*/
    
    /*     ����      */
    
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
	/*���Է����Ƿ���ȷ 
	cout<<"�ҵ��ƣ�"<<endl;
	for(int i=0;i<=5;i++)
	cout<<"��"<<i<<"�ţ�"<<MyCard[i]<<endl;
	
	cout<<"AI1���ƣ�"<<endl;
	for(int i=0;i<=5;i++)
	cout<<"��"<<i<<"�ţ�"<<AI1Card[i]<<endl;
	
	cout<<"AI2���ƣ�"<<endl;
	for(int i=0;i<=5;i++)
	cout<<"��"<<i<<"�ţ�"<<AI2Card[i]<<endl;
	Sleep(10000);*/
	
	/*      ����           */
	range_cards();

    /*�������������Ƿ����� 
    cout << "�ҵ��ƣ�" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "��" << i+1 << "�ţ�" << MyCard[i] << endl;
    }

    cout << "AI1���ƣ�" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "��" << i+1 << "�ţ�" << AI1Card[i] << endl;
    }

    cout << "AI2���ƣ�" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "��" << i+1 << "�ţ�" << AI2Card[i] << endl;
    }
	Sleep(10000);*/
}

