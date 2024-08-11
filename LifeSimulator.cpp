/*
	LifeSimulator
    Copyright (C) 2024  Cpp-King

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<winuser.h>
#include<fstream>
#include<vector>
#include<unistd.h>
//#define dev
using namespace std;
 
void setsize(int col, int row)
{
	char cmd[64];
	sprintf(cmd, "mode con cols=%d lines=%d", col, row);
	system(cmd);
} 
int main(){
	#ifndef dev
	if(access("RTMOWARE.txt", 0)==0){
		cout<<"You're not allowed to enter this city. Bad bye.";
		Sleep(3000);
		exit(0);
	}
	#endif
	srand(time(0));
    MessageBoxA(0,"Welcome to play Life Simulation - Visual Studio Version !","Life Simulation",MB_ICONINFORMATION|MB_OK);
    //An amazing title  0v0
    cout<<"     __          __   _________   _________       _________   __   __          __   __    __   __           ______    ________    ______    _______\n"
        <<"    |  |        |  | |  _______| |  _______|     |  _______| |  | |  \\        /  | |  |  |  | |  |         /  __  \\  |__    __|  /  __  \\  |   __  \\\n"
        <<"    |  |        |  | |  |____    |  |____        |  |        |  | |   \\      /   | |  |  |  | |  |        |  |__|  |    |  |    |  |  |  | |  |__|  |\n"
        <<"    |  |        |  | |   ____|   |   ____|       |  |______  |  | |    \\    /    | |  |  |  | |  |        |   __   |    |  |    |  |  |  | |   __  _|\n"
        <<"    |  |        |  | |  |        |  |            |_______  | |  | |  |\\ \\  / /|  | |  |  |  | |  |        |  |  |  |    |  |    |  |  |  | |  |  \\ \\\n"
        <<"    |  |______  |  | |  |        |  |______      _______|  | |  | |  | \\ \\/ / |  | |  |__|  | |  |______  |  |  |  |    |  |    |  |__|  | |  |   \\ \\\n"
        <<"    |_________| |__| |__|        |_________|    |__________| |__| |__|  \\__/  |__| |________| |_________| |__|  |__|    |__|     \\______/  |__|    \\_\\\n\n\n";
    cout<<"\nPress SPACE\n\n";
    title:
        char p=_getch();
        if(p!=' ') goto title;
    ;
    string buf;
    int first=MessageBoxA(0,"Okay, well... Do you come there first time?","From: Jacson",MB_YESNO|MB_ICONQUESTION);
    if(first==IDYES){
        MessageBoxA(0,"YAR HAR HAR HAR!\nThen I think I should tell you something...","From: Jacson",MB_OK);
        MessageBoxA(0,"First, you can almost talk to anyone!","From: Jacson",MB_OK);
        MessageBoxA(0,"But... There are some people... You know, bad... I can only say, DO NOT TALK TO THEM ANYTIME!!!","From: Jacson",MB_OK|MB_ICONWARNING);
        MessageBoxA(0,"Second, you should be pleasent to meet anyone.","From: Jacson",MB_OK);
        MessageBoxA(0,"Oh, wait, what\'s your name?","From: Jacson",MB_OK|MB_ICONQUESTION);
        string buf;
        names:;
        cin>>buf;
        if(buf=="Jacson"||buf=="jacson"){
        	MessageBoxA(0,"Oh, that\'s MY name!","From: Jacson",MB_OK|MB_ICONSTOP);
        	goto names;
		}
        int xb=MessageBoxA(0,"Ah yar, a good name!\nThen are you a boy?","From: Jacson",MB_YESNO|MB_ICONQUESTION);
    	if(xb==IDNO) MessageBoxA(0,"Ohh sorry... What a pretty girl!","From: Jacson",MB_OK);
    	else MessageBoxA(0,"Good! Look, how smart you are! Har har har! OK, Here we GO!","From: Jacson",MB_OK);
	}else{
		MessageBoxA(0,"Oh, so what\'s your name?","From: Jacson",MB_OK|MB_ICONQUESTION);
        names2:;
        cin>>buf;
        if(buf=="Jacson"||buf=="jacson"){
        	MessageBoxA(0,"Oh, that\'s MY name!","From: Jacson",MB_OK|MB_ICONSTOP);
        	goto names2;
		}
	}
    MessageBoxA(0,"GAME START!","SYSTEM",MB_OK);
    int day=1;
    int hp=100;
    int maxhp=100;
    int hungry=100;
    int maxhungry=100;
    int hour=7,minute=30;
    int inte=90;
    int money=500000;
    int bdt=0;
    int phone=0;
    int police=0,atteck=10;
    int fz=0,gun=0;
    vector<string> things;
	if(buf=="ttcandy") bdt=1;
    while(1){
        system("cls");
        cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\nWhat will you do now?\n1.Move 2.Talk 3.State 4.Exit\n";
        int op;
        cin>>op;
        if(op==4) exit(0);
        else if(op==3){
        	system("cls");
        	cout<<"HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<", Inteligence "<<inte;
        	Sleep(5000);
		}else if(op==2){
        	int p=rand()%500+1;
        	system("cls");
        	cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
        	if(p>=1&&p<=299){
        		cout<<"Naoko: こんにちは��";
        		Sleep(2000);
			}else if(p>=100&&p<=497){
				cout<<"Wassily: Don't get in the way! I'll hit you!";
        		Sleep(3000);
			}else if(p==498){
				cout<<"Cao Yuan: I have won the gold medal and come back!";
        		Sleep(4000);
        		system("cls");
        		cout<<"MISSON WIN!\nTalk to Cao Yuan and get his autograph.";
        		Sleep(4000);
			}else if(p==499){
				cout<<"Officer: Have you seen a man in black?";
				minute+=10;
        		Sleep(3000);
        		system("cls");
        		cout<<"MISSON WIN!\nHelp the officer to catch the bad man.";
        		Sleep(4000);
			}else if(p==500){
				cout<<"Madam: Oh! My phone has been stolen!!!";
        		Sleep(3000);
				system("cls");
        		cout<<"MISSON START!\nFind her phone";
        		Sleep(3000);
				system("cls");
				cout<"Please enter the Author's team name(Full name without space): ";
				string ddd;
				cin>>ddd;
				if(ddd=="BintreeDevelopmentTeam"){
					system("cls");
	        		cout<<"MISSON WIN!\nFind her phone";
	        		money+=100;
	        		Sleep(2000);
				}else{
					system("cls");
	        		cout<<"MISSON FAIL!\nFind her phone";
	        		Sleep(2000);
				}
				minute+=10;
			}else{
				cout<<"No ones are here.";
				Sleep(2000);
			}
			minute+=1;
		}else if(op==1){
            system("cls");
            cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\nWhere will you move?\n1.School 2.BDT 3.Walking Street 4.Qingbang 5.Shop 6.Restaurant 7.Police 8.Home 9.Cancel\n";
            int move;
            cin>>move;
            system("cls");
            if(move==1){
                inte+=rand()%2+1;
                hungry-=rand()%5+1;
                cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\nYou learnt for 0.5 hours.\n";
                Sleep(2000);
                minute+=30;
            }else if(move==2){
                cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
                if(bdt==0){
                    cout<<"ttcandy: Here is Bintree Development Team. What are you gonna do?\n1.Interview 2.Leave\n";
                    int dop;
                    cin>>dop;
                    system("cls");
                    if(dop==1){
                        cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
                        if(rand()%100+1>75){
                            cout<<"You passed the interview!\n";
                            Sleep(2000);
                            bdt=1;
                            minute+=30;
                            hungry-=rand()%3+1;
                        }else{
                            cout<<"You failed the interview.\n";
                            Sleep(2000);
                            minute+=30;
                            hungry-=rand()%3+1;
                        }
                    }
                }else{
                    cout<<"You worked for 0.5 hours.";
                    Sleep(2000);
                    minute+=30;
                    money+=100;
                    hungry-=rand()%5+1;
                }
            }else if(move==3){
            	system("cls");
            	cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\nYou: Great! I feel better.";
			    Sleep(3000);
			    minute+=10;
			    hungry-=rand()%3+1;
			}else if(move==5){
            	system("cls");
            	
            	cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\nAssistant: Welcome! What do you want?\n";
            	if(money<10){
            		system("cls");
            		cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\nAssistant: You do not have enough money!\n";
					continue;
				}
            	cout<<"1.Sausage $10  2.LS-Phone $20000  3.Medicine $30  4.Gun $50000  5.No, thanks.\n";
            	int buy;
            	cin>>buy;
            	system("cls");
            	cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
            	if(buy==1){
            		cout<<"You bought a sausage.";
            		money-=10;
            		hungry+=10;
            		if(hungry>maxhungry) hungry=maxhungry;
            		Sleep(1000);
				}else if(buy==2){
					if(money<20000){
						cout<<"Assistant: You do not have enough money!";
						Sleep(1000);
					}else{
						cout<<"You bought a LS-Phone.";
						money-=20000;
						Sleep(1000);
						phone=true;
					}
				}else if(buy==3){
					if(money<30){
						cout<<"Assistant: You do not have enough money!";
						Sleep(1000);
					}else{
						cout<<"You bought some medicine.";
						money-=30;
						Sleep(1000);
						things.push_back("medicine");
					}
				}else if(buy==4){
					if(money<50000){
						cout<<"Assistant: You do not have enough money!";
						Sleep(1000);
					}else{
						gun=1;
						cout<<"You bought a Gun.\n";
						money-=50000;
						atteck=25;
						if(!police){
							if(access("TB.txt", 0)==0){
								cout<<"Officer: Oh, hello.";
								Sleep(1000);
								system("cls");
								cout<<"Officer: So, you bought a gun. AGAIN. Right?";
								Sleep(3000);
								system("cls");
								cout<<"You: Oh...NONONO, ...(All is over...)";
								Sleep(3000);
								system("cls");
								cout<<"ENDING\nRefuse to mend one 's ways after repeated education";
								system("type nul>RTMOWARE.txt");
								Sleep(3000);
								exit(0);
							}
							cout<<"Assistant: Oh, you're not police...I need to tell them.(quiet)";
							Sleep(3000);
							system("cls");
							cout<<"MISSON START!\nSTOP THE ASSISTANT!";
							Sleep(3000);
							system("cls");
							int kill=MessageBoxA(0,"Do you want to KILL her?","Please think carefully",MB_YESNO);
							if(kill==IDYES){
								cout<<"SNAP!!!";
								Sleep(1000);
								system("cls");
								cout<<"Assistant: Ahhhhhhhhhh!";
								Sleep(1000);
								srand(time(0));
								int ca=rand()%3+1;
								if(ca>2){
									system("cls");
									cout<<"You: What did I do...I killed her...";
									Sleep(3000);
									system("cls");
									cout<<"MISSON WIN!\nA ruthless killer";
									Sleep(3000);
									system("cls");
									minute+=30;
									fz++;
									continue;
								}else{
									system("cls");
									cout<<"Police: What happened? -Ah! I saw him! POLICE! FREEZE!";
									Sleep(3000);
									system("cls");
									cout<<"You: All is over...";
									Sleep(3000);
									system("cls");
									cout<<"MISSON FAIL!\n\nSNAP!!!\nYou: Ahhh......";
									Sleep(3000);
									exit(0);
								}
							}else{
								cout<<"You: ...";
								Sleep(1000);
								system("cls");
								cout<<"At local police:";
								Sleep(1000);
								system("cls");
								cout<<"Assistant: Oh, I saw a person that bought a gun! And the person isn't a police! I'm sure!";
								Sleep(3000);
								system("cls");
								cout<<"Officer: OK, we know. Thank you.";
								Sleep(1000);
								system("cls");
								cout<<"You: I'll go to the local police.";
								Sleep(1000);
								system("cls");
								cout<<"You: I'm come.";
								Sleep(1000);
								system("cls");
								cout<<"Officer: What's wrong with you? Can I help you?";
								Sleep(2000);
								system("cls");
								cout<<"You: I bought a gun...I come to surrender oneself.";
								Sleep(2000);
								system("cls");
								cout<<"Officer: [Smile] You are an honest man. Since you admit it, I won't say much. Go to jail for three years.";
								Sleep(5000);
								system("cls");
								cout<<"1 year later, you were released early due to your good performance.";
								Sleep(5000);
								system("cls");
								cout<<"MISSON FAIL BUT...\nTwice-Born";
								system("type nul>TB.txt");
								Sleep(3000);
								exit(0);
							}
						}
					}
				}
			    minute+=10;
			    hungry-=rand()%3+1;
			}else if(move==4){
				system("cls");
				if(!police){
					cout<<"You: Qingbang? Jackson told me that don't get there. So...?";
					Sleep(3000);
					system("cls");
					cout<<"You: Maybe Jackson just kidding? All right, I think I can get in.";
					Sleep(3000);
					system("cls");
					cout<<"You: OK...";
					Sleep(1000);
					system("cls");
					cout<<"Black clothed man 1: WHO ARE YOU???";
					Sleep(1500);
					system("cls");
					cout<<"You: (Oh shit...)Ah...Hey that...";
					Sleep(1000);
					system("cls");
					cout<<"Black clothed man 1: GET AWAY!!!";
					Sleep(1000);
					system("cls");
					cout<<"Black clothed man 2: You don't need to shout. I'll kill him.";
					Sleep(2000);
					system("cls");
					cout<<"SNAP!!!";
					Sleep(1000);
					system("cls");
					cout<<"ENDING\nAn old man's sayings are seldom untrue.";
					Sleep(3000);
					exit(0);
				}else{
					if(gun){
						cout<<"MISSON START!\nCAUGHT THE QINGBANG";
						Sleep(3000);
						system("cls");
						cout<<"You: I'll caught you!";
						Sleep(1500);
						system("cls");
						cout<<"SNAP!!! SNAP!!! SNAP!!!";
						Sleep(2000);
						system("cls");
						cout<<"Black clothed man 1: Ahhhhhhh!";
						Sleep(1500);
						system("cls");
						cout<<"SNAP!!!";
						Sleep(1000);
						system("cls");
						cout<<"You: STOP!";
						Sleep(1000);
						system("cls");
						string sn="SNAPSNAPSNAPSNAPSNAPSNAP";
						for(int i=0;i<sn.size();i++){
							cout<<sn[i];
							Sleep(125);
						}
						cout<<"-------------";
						Sleep(1000);
						system("cls");
						cout<<"You: Thanks to the machine gun provided to me by the bureau...";
						Sleep(4000);
						system("cls");
						cout<<"Jackson: Oh, hello.";
						Sleep(1500);
						system("cls");
						cout<<"You: It's you!?!?!?";
						Sleep(1500);
						system("cls");
						cout<<"Jackson: Oh, yar. I told you DO NOT come. But you still came.";
						Sleep(4000);
						system("cls");
						cout<<"You: I am an OFFICER.";
						Sleep(1500);
						system("cls");
						cout<<"Jackson: So? What will you do, kill me or else?";
						Sleep(3000);
						system("cls");
						if(access("IKCIR.txt",0)!=0){
							MessageBoxA(0,"What will you do? Kill him?","Please think carefully",MB_OK);
							cout<<"You: OF COURSE I'LL KILL YOU! GO--DIE!!!";
							Sleep(2000);
							system("cls");
							cout<<"SNAP!!!";
							Sleep(1000);
							system("cls");
							cout<<"You: Ahhhh!";
							Sleep(1000);
							system("cls");
							cout<<"Jackson: [Sigh] You still remind that...";
							Sleep(2000);
							system("cls");
							cout<<"You: [Cough] Wh..What?";
							Sleep(2000);
							system("cls");
							cout<<"Jackson: ......";
							Sleep(2000);
							system("cls");
							cout<<"MISSON FAIL\nFALSE ENDING\nI knew...Can I restart?";
							system("type nul>IKCIR.txt");
							Sleep(3000);
							exit(0);
						}else{
							int choose=MessageBoxA(0,"What will you do? Kill him?","Please think carefully",MB_YESNO);
							if(choose==IDYES){
								cout<<"You: OF COURSE I'LL KILL YOU! GO--DIE!!!";
								Sleep(2000);
								system("cls");
								cout<<"SNAP!!!";
								Sleep(1000);
								system("cls");
								cout<<"You: Ahhhh!";
								Sleep(1000);
								system("cls");
								cout<<"Jackson: [Sigh] You still remind that...";
								Sleep(2000);
								system("cls");
								cout<<"You: [Cough] Wh..What?";
								Sleep(2000);
								system("cls");
								cout<<"Jackson: ......";
								Sleep(2000);
								system("cls");
								cout<<"MISSON FAIL\nFALSE ENDING\nI knew...Can I restart?";
								system("type nul>IKCIR.txt");
								Sleep(3000);
								exit(0);
							}else{
								cout<<"You: I...cannot kill you...";
								Sleep(2000);
								system("cls");
								cout<<"SNAP!!!";
								Sleep(1000);
								system("cls");
								cout<<"Officer 1: Oh! What's the matter? WHY DO NOT YOU KILL HIM!?";
								Sleep(4000);
								system("cls");
								cout<<"You: He...He...He maybe my...BROTHER!";
								Sleep(3000);
								system("cls");
								cout<<"Officer 2: His true name is yyvsmfu.";
								Sleep(2000);
								system("cls");
								cout<<"You: Ah...He...IS my brother...I CANNOT KILL HIM.";
								Sleep(3000);
								system("cls");
								cout<<"Officer 1: Hmm...But I still think you should kill him. You will not be an officer. FOREVER.";
								Sleep(6000);
								system("cls");
								cout<<"MISSON WIN\nTRUE ENDING\nHe is your brother.";
								Sleep(3000);
								system("cls");
								cout<<"Author: Thanks for your playing! Our GitHub is github.com/Cpp-King/Cpp-King ! Wel---come!";
								Sleep(6000);
								exit(0);
							}
						}
					}else{
						cout<<"You: I think I can't caught them. I don't have a gun!";
						Sleep(3000);
					}
				}
			}else if(move==7){
				system("cls");
				cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
				cout<<"Officer: What's happened? Can I help you?\n1.Interview 2.About Qingbang 3.Nothing\n";
				int po;
				cin>>po;
				system("cls");
				if(po==1){
					if(police){
						cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
						cout<<"Officer: Oh, you are already an officer!";
					}else if(phone){
						cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
						if((rand()%100+1)>=85){
							cout<<"You passed the interview!";
							police=true;
						}
						else cout<<"You failed the interview!";
						hungry-=10;
						Sleep(3000);
					}else{
						cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
						cout<<"Officer: You haven't a phone!";
						Sleep(1500);
					}
				}else if(po==2){
					cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
					cout<<"Officer: Oh, you helped our deeply!";
					Sleep(1500);
					system("cls");
					cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
					cout<<"5 hours later...";
					Sleep(1500);
					system("cls");
					cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
					cout<<"Officer: Thanks. Here are your bonus. $100000.";
					Sleep(1500);
					system("cls");
					money+=100000;
					hungry=maxhungry;
					hp=maxhp;
				}
			}else if(move==6){
				system("cls");
				if(money<200){
					cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
					cout<<"Assistant: You don't have enough money.";
					Sleep(1500);
				}else{
					cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", HP "<<hp<<"/"<<maxhp<<", Hungry "<<hungry<<"/"<<maxhungry<<", $"<<money<<".\n";
					cout<<"You had a good meal.";
					Sleep(1500);
					hungry=maxhungry;
					money-=200;
				}
			}else if(move==8){
				system("cls");
				cout<<"You had a rest for 1 hour.";
				hour++;
				hp=maxhp;
				hungry=maxhungry;
			}
        }else continue;
        if(minute>=60){
            hour++;
            minute-=60;
            if(hour>=24){
                day++;
                hour-=24;
            }
        }if(hungry<=0||hp<0){
        	system("cls");
        	cout<<"Day "<<day<<" "<<hour<<":"<<minute<<", $"<<money<<".\n";
        	cout<<buf<<" died.\nGAME OVER!";
        	Sleep(3000);
        	exit(0);
		} 
    }
    return 0;
}
