/*
	ToolsOS
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
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<vector>
#include<list>
#include<queue>
#include<deque>
#include<stack>
#include<conio.h>
#include<windows.h>
#define ll long long
#define cls(a,b) memset(a,b,sizeof(a))
#define read(aaaa) {char cccc;while((cccc=getchar())>47) aaaa=aaaa*10+(cccc^48);}

using namespace std;

bool cmp(int a,int b){
	return a<b;
}
void delay_print(std::string msg,int delay_time=8){
	for(int i=0;i<msg.size();i++){
		cout<<msg[i];
		Sleep(delay_time);
	}
}

double calculate(string str)
{
	str = str + " ";
	stack<double> mystack;//����������
	string Empty = " ";
	string ch = "+-*/";
	string numbers = "0123456789";
	string s = "0123456789+-*/";
	int endi;
	double num, secnodnum, firstnum;
	for (int i = 0; i < str.length(); )
	{
		if (str[i] == ' ') {
			i++;
			continue;
		}
		endi = i;
		while (str[endi + 1] != ' ') endi++;
		string tempstr = str.substr(i, endi - i + 1);//ȡ����һ��Ԫ��
		if ((tempstr == "+") || (tempstr == "-") || (tempstr == "*") || (tempstr == "/"))
		{
			secnodnum = mystack.top();//ȡ��ջ��Ԫ��
			mystack.pop();//��ջ
			firstnum = mystack.top();//ȡ��ջ��Ԫ��
			mystack.pop();//��ջ
			if (tempstr == "+")
			{
				num = firstnum + secnodnum;
				mystack.push(num);
			}
			if (tempstr == "-")
			{
				num = firstnum - secnodnum;
				mystack.push(num);
			}
			if (tempstr == "*")
			{
				num = firstnum * secnodnum;
				mystack.push(num);
			}
			if (tempstr == "/")
			{
				num = firstnum / secnodnum;
				mystack.push(num);
			}
		}
		else
		{
			double temp = stod(tempstr);
			mystack.push(temp);
		}
 
		i = endi + 1;//�����±���ƶ�
	}
	return mystack.top();
}

int main(){
	cout<<"(C)��Ȩ����ttcandy2024��������Ȩ����\n";
	Sleep(3000);
	cout<<"���ڽ���\n";
	Sleep(500);
	cout<<"�������û�����������ǰ�Ƿ�ע��\n";
	string name;
	inn:;
	getline(cin,name);
	for(int i=0;i<name.size();i++){
		if(name[i]==' '||name[i]=='\\'||name[i]=='@'||name[i]=='.'||name[i]==','){
			cout<<"�û������ܰ��������ַ���\\@.,�Ϳո�\n";
			goto inn;
		}
	}
	bool admin=false;
	if(name=="ttcandy") admin=true;
	delay_print("��ӭʹ��ToolsOS��\n����help�鿴��������\n");
	while(true){
		start:;
		cout<<">>> ";
		string cmd;
		getline(cin, cmd);
		if(cmd=="exit") exit(0);
		else if(cmd=="__def"){
			cout<<">>> ";
			string d1;
			cin>>d1;
			if(d1=="admin-ttcandy-LIMIT") admin=true;
			else cout<<"��Ч�Ĺ���Ȩ�޼����롣\n";
		}else if(cmd=="color"){
			if(!admin){
				cout<<"��û��ִ�д������Ȩ�ޡ�\n";
				continue;
			}
			cout<<">>> ";
			string co;
			cin>>co;
			if(co=="green") system("color 02");
			else if(co=="blue") system("color 03");
			else if(co=="white") system("color 07");
			else cout<<"����������롣\n";
			goto start;
		}else if(cmd=="help"){
			cout<<"�����б�\n";
			delay_print("calculator���к������׺���ʽ������ �õ����ո�ָ�\n");
			delay_print("color�ı����̨��ɫ��û�й���Ȩ���޷�ʹ�á�\n");
			delay_print("clear��տ���̨\n");
			delay_print("help�鿴��������÷�\n");
			delay_print("timer�ո�����뵥λ��ʱ�� �ÿո�ָ�\n");
			delay_print("exit�˳�ToolsOS\n\n");
			while(true){
				delay_print("�����������Ʋ鿴�����÷�������0�˳�\n>>> ");
				string cmd2;
				string tmp; 
				cin >> cmd2;
				getline(cin, tmp); 
				if(cmd2=="0") break;
				else if(cmd2=="calculator"){
					delay_print("������Ϣ\n");
					delay_print("calculator���������׺���ʽ ����\n");
					cout<<">>> ";
					delay_print("calculator\n",125);
					cout<<">>> ";
					delay_print("3 4 * 9 -\n",125);
					cout<<"3\n";
					delay_print("�����ѭ��ȷ���ʽ�﷨��\n");
				}else if(cmd2=="clear"){
					delay_print("������Ϣ\n");
					delay_print("��տ���̨������Ҫ�����clear������ַ���\n");
				}else if(cmd2=="color"){
					delay_print("������Ϣ\n");
					delay_print("color���к�������ɫ(green,blue,white)��\n");
				}else if(cmd2=="exit"){
					delay_print("������Ϣ\n");
					delay_print("�˳����򡣲���Ҫ�����exit������ַ���\n");
				}else if(cmd2=="help"){
					delay_print("������Ϣ\n");
					delay_print("�����ڲ���������\n");
				}else if(cmd2=="timer"){
					delay_print("������Ϣ\n");
					delay_print("timer HH:mm:ss\n");
					delay_print("����HHСʱ������23��mm���Ӳ�����59��ss�벻����59\n");
				}else cout<<"\""<<cmd2<<"\"����һ�����\n";
			}
		}
		else if(cmd=="calculator"){
			string str;
			cout<<">>> ";
			getline(cin,str);
			try{
				double ans=calculate(str);
				cout<<ans<<"\n";
				//throw ;
			}catch(...){
				cout<<"��������\n";
			}
			continue;
		}
		else if(cmd=="clear"){
			system("cls");
			cout<<"(C)��Ȩ����ttcandy2024��������Ȩ����\n";
		}
		else if(cmd.length()>5&&cmd.substr(0,5)=="timer"){
			int hour, minu, seco;
			sscanf(cmd.substr(5).c_str(), "%d:%d:%d", &hour, &minu, &seco);
			if(hour>23||hour<0||minu>59||minu<0||seco>59||seco<0){
			    cout<<"���Ϸ��Ĳ���:"<<cmd.substr(5)<<'\n';
			    continue;
			}
			cout<<'\n';
			int x=0,y=0,z=0;
			while(hour||minu||seco){
				int stt=clock();
				cout<<"\r��ȥ��"<<x/10<<x%10<<":"<<y/10<<y%10<<":"<<z/10<<z%10<<"������"<<hour/10<<hour%10<<":"<<minu/10<<minu%10<<":"<<seco/10<<seco%10;
				z++;
				if(z==60)y++,z=0;
				if(y==60)x++,y=0;
				seco--;
				if(seco<0)minu--,seco=59;
				if(minu<0)hour--,minu=59;
				Sleep(1000-(clock()-stt));
			}
			cout<<"\r��ȥ��"<<x/10<<x%10<<":"<<y/10<<y%10<<":"<<z/10<<z%10<<"������"<<hour/10<<hour%10<<":"<<minu/10<<minu%10<<":"<<seco/10<<seco%10<<"\n";
			cout<<"\n��ʱ������\n";
		}
		else cout<<"\""<<cmd<<"\"����һ���������help�鿴�����б�\n";
	}
	return 0;
}

