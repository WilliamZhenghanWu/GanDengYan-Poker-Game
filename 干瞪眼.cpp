#include<bits/stdc++.h>
#include<windows.h>
#include<sstream>
#include "�ɵ���.h"
using namespace std;

int main(){
	
	/*      ��������       */
	
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
    cards[52]="С��";
	cards[53]="����";
	cards[54]="���";

    /*     ��ʼ�߼�        */
    
    while(1){
    startGame();
    system("color 03");//������ɫ 
    system("cls");
    cout<<"_______________________________________________________"<<endl; //��ʼ���� 
	cout<<"|                    �ɵ�����Ϸ                       |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 	
	cout<<"|                     ������־                        |"<<endl; 
	cout<<"| 1.�����������ƣ���ֻ�ܳ����źͶ��ӣ��ɴ��ٴ      |"<<endl; 
	cout<<"| 2.�޸�����֪bug                                     |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 
	cout<<"|                     ��Ϸѡ��                        |"<<endl;	
    cout<<"| 1.��ʼ��Ϸ                                          |"<<endl; 
	cout<<"| 2.��ȴ���һ���汾                                  |"<<endl; 
	cout<<"-------------------------------------------------------"<<endl; 	
	cout<<"| InfDev1.4                                           |"<<endl;
	cout<<"-------------------------------------------------------"<<endl; 
	cout<<">>>";
	cin>>choice;
	if(choice==1){
	    //��ʼ��Ϸ 
	    startGame();
	    Last_Cards[0]="None";
	    passtime=2;
	    while(choice){
	    if(Master=="Me"){//��ֻ���������ׯ�ҵ���� 
        system("cls");
 		CardFlag:
 		if(passtime==2&&!Started_Game_Or_Not&&Card_Is_Valid){
 			New_Card_Void(MyCard);
 			range_cards();
		 }
		 Started_Game_Or_Not=0;
		cout << "�ҵ��ƣ�" << endl;
        for (int i = 0; i < 6; i++) {
        cout << "��" << i+1 << "�ţ�" << MyCard[i] << endl;
 		}

    // ����AI1 AI2 ����&&������Ϣ 
	cout << "AI1���ƣ�" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "��" << i+1 << "�ţ�" << AI1Card[i] << endl;
    }

    cout << "AI2���ƣ�" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "��" << i+1 << "�ţ�" << AI2Card[i] << endl;
    } 
    cout<<"��һ�γ����ƣ�"<<Last_Cards[0]<<Last_Cards[1]<<Last_Cards[2]<<Last_Cards[3]<<Last_Cards[4]<<Last_Cards[5]<<endl;
    cout<<"��������:"<<passtime<<endl;
    cout<<"����������"<<Cards_Be_Chosen_Num<<endl;
	//*/
	 
 		cout<<"��ѡ����ڼ��ţ�>>>";
 		for(int i=0;i<=5;i++)Cards_Be_Chosen[i]="";
		Cards_Be_Chosen_Num=0;
		//choice_in_game_num=-1;
		while(cin>>choice_in_game_num){
            if(choice_in_game_num==-1||choice_in_game_num==-2){ 
                if(choice_in_game_num==-2) pass_or_not=1;
            	break;
			}
			else if(choice_in_game_num<-2){
				cout<<"��Чѡ������������"<<endl;
				Card_Is_Valid=0;
				Sleep(3000);
				system("cls");
				goto CardFlag; 
			}
			Cards_Be_Chosen[Cards_Be_Chosen_Num]=MyCard[choice_in_game_num-1];
		    Cards_Be_Chosen_Num++;	
		}
		
		/*�������Ƿ���ȷѡ�� 
		for(int i=0;i<=5;i++)
		cout<<"��ѡ�еĵ�"<<i+1<<"���ƣ�"<<Cards_Be_Chosen[i]<<endl;
		Sleep(5000);
		*/
		if(choice_in_game_num==-2&&passtime!=2) {
			Cards_Be_Chosen[0]="����";
			Cards_Be_Chosen_Num=1;
			passtime++;
		} 
		else if(Cards_Be_Chosen_Num==1){
			if(SingleCardIsValid(Last_Cards[0],Cards_Be_Chosen[0],passtime)){
				Card_Is_Valid=1;
				passtime=0;
			    Player_Cards_Update(MyCard);//������ 
			    range_cards();//���� 
			    Last_Cards[0]=Cards_Be_Chosen[0];
			}
            else{
            	cout<<"���Ʋ��Ϸ���"<<endl;
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
			else{//����ֻ���ǵ���
		    cout<<"���Ʋ��Ϸ���"<<endl;
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
		else{//����ֻ���ǵ���
		    cout<<"���Ʋ��Ϸ���"<<endl;
		    Card_Is_Valid=0;
			Sleep(5000);
			system("cls");
			goto CardFlag;
	    }
	    //�����ж� 
	    AI1_Push_Cards();
	    AI2_Push_Cards();
	    if(MyCard[0]==""&&MyCard[1]==""&&MyCard[2]==""&&MyCard[3]==""&&MyCard[4]==""&&MyCard[5]==""){//���ʤ�� 
	    	system("cls");
			cout<<"��Ӯ�ˣ�����"<<endl;
			Sleep(3000);
			break; 
		}
		system("cls");
	    for(int i=3;i>0;i--){
	    	cout<<"��������:"<<passtime<<endl;//���Բ������� 
	    	cout<<"��ѡ�����"<<Cards_Be_Chosen[0]<<" "<<Cards_Be_Chosen[1]<<" "<<Cards_Be_Chosen[2]<<" "<<Cards_Be_Chosen[3]<<" "<<Cards_Be_Chosen[4]<<" "<<Cards_Be_Chosen[5]<<endl;
		    cout<<"���ڵȴ�������1���ơ���"<<i<<"��"<<endl;
		    Sleep(1000);
			system("cls");
		}
		if(AI1Card[0]==""&&AI1Card[1]==""&&AI1Card[2]==""&&AI1Card[3]==""&&AI1Card[4]==""&&AI1Card[5]==""){//���ʤ�� 
	    	system("cls");
			cout<<"������1Ӯ�ˣ������´�ף����ˣ�"<<endl;
			Sleep(3000);
			break; 
		}
		for(int i=3;i>0;i--){
			cout<<"��������:"<<passtime<<endl;//���Բ������� 
	    	cout<<"��ѡ�����"<<Cards_Be_Chosen[0]<<" "<<Cards_Be_Chosen[1]<<" "<<Cards_Be_Chosen[2]<<" "<<Cards_Be_Chosen[3]<<" "<<Cards_Be_Chosen[4]<<" "<<Cards_Be_Chosen[5]<<endl;
		    cout<<"������1���ƣ�";
		    for(int j=0;j<=5;j++)cout<<AI1_push[j];
		    cout<<endl;
			cout<<"���ڵȴ�������2���ơ���"<<i<<"��"<<endl;
			Sleep(1000);
			system("cls");
			}
        system("cls");
		cout<<"������1���ƣ�";
		for(int j=0;j<=5;j++)cout<<AI1_push[j];
		cout<<endl;
		cout<<"������2���ƣ�";
		for(int j=0;j<=5;j++)cout<<AI2_push[j];
		cout<<endl;
		if(AI2Card[0]==""&&AI2Card[1]==""&&AI2Card[2]==""&&AI2Card[3]==""&&AI2Card[4]==""&&AI2Card[5]==""){//���ʤ�� 
	    	system("cls");
			cout<<"������2Ӯ�ˣ������´�ף����ˣ�"<<endl;
			Sleep(3000);
			break; 
		}
		goto CardFlag;
    }
    }
	}
	
	
	 
	else if(choice==2){//�ȴ���һ���汾 
	    for(int i=3;i>0;i--){
	        system("cls");
	        cout<<"��ȴ���һ���汾��" <<endl;
	        cout<<i<<"���ص������桭��"<<endl;
	        Sleep(1000);
	    }
    }
}
}
