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
	stack<double> mystack;//用来存数据
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
		string tempstr = str.substr(i, endi - i + 1);//取出这一个元素
		if ((tempstr == "+") || (tempstr == "-") || (tempstr == "*") || (tempstr == "/"))
		{
			secnodnum = mystack.top();//取出栈顶元素
			mystack.pop();//出栈
			firstnum = mystack.top();//取出栈顶元素
			mystack.pop();//出栈
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
 
		i = endi + 1;//控制下标的移动
	}
	return mystack.top();
}

int main(){
	cout<<"(C)版权所有ttcandy2024保留所有权利。\n";
	Sleep(3000);
	cout<<"正在进入\n";
	Sleep(500);
	cout<<"请输入用户名，无论以前是否注册\n";
	string name;
	inn:;
	getline(cin,name);
	for(int i=0;i<name.size();i++){
		if(name[i]==' '||name[i]=='\\'||name[i]=='@'||name[i]=='.'||name[i]==','){
			cout<<"用户名不能包含以下字符：\\@.,和空格。\n";
			goto inn;
		}
	}
	bool admin=false;
	if(name=="ttcandy") admin=true;
	delay_print("欢迎使用ToolsOS！\n输入help查看所有命令\n");
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
			else cout<<"无效的管理权限激活码。\n";
		}else if(cmd=="color"){
			if(!admin){
				cout<<"你没有执行此命令的权限。\n";
				continue;
			}
			cout<<">>> ";
			string co;
			cin>>co;
			if(co=="green") system("color 02");
			else if(co=="blue") system("color 03");
			else if(co=="white") system("color 07");
			else cout<<"无意义的输入。\n";
			goto start;
		}else if(cmd=="help"){
			cout<<"命令列表\n";
			delay_print("calculator换行后输入后缀表达式并计算 用单个空格分隔\n");
			delay_print("color改变控制台颜色。没有管理权限无法使用。\n");
			delay_print("clear清空控制台\n");
			delay_print("help查看所有命令及用法\n");
			delay_print("timer空格后输入单位和时间 用空格分隔\n");
			delay_print("exit退出ToolsOS\n\n");
			while(true){
				delay_print("输入命令名称查看具体用法或输入0退出\n>>> ");
				string cmd2;
				string tmp; 
				cin >> cmd2;
				getline(cin, tmp); 
				if(cmd2=="0") break;
				else if(cmd2=="calculator"){
					delay_print("命令信息\n");
					delay_print("calculator换行输入后缀表达式 例：\n");
					cout<<">>> ";
					delay_print("calculator\n",125);
					cout<<">>> ";
					delay_print("3 4 * 9 -\n",125);
					cout<<"3\n";
					delay_print("务必遵循正确表达式语法！\n");
				}else if(cmd2=="clear"){
					delay_print("命令信息\n");
					delay_print("清空控制台。不需要输入除clear以外的字符。\n");
				}else if(cmd2=="color"){
					delay_print("命令信息\n");
					delay_print("color换行后输入颜色(green,blue,white)。\n");
				}else if(cmd2=="exit"){
					delay_print("命令信息\n");
					delay_print("退出程序。不需要输入除exit以外的字符。\n");
				}else if(cmd2=="help"){
					delay_print("命令信息\n");
					delay_print("你现在不就在用吗？\n");
				}else if(cmd2=="timer"){
					delay_print("命令信息\n");
					delay_print("timer HH:mm:ss\n");
					delay_print("其中HH小时不大于23，mm分钟不大于59，ss秒不大于59\n");
				}else cout<<"\""<<cmd2<<"\"不是一个命令。\n";
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
				cout<<"输入有误。\n";
			}
			continue;
		}
		else if(cmd=="clear"){
			system("cls");
			cout<<"(C)版权所有ttcandy2024保留所有权利。\n";
		}
		else if(cmd.length()>5&&cmd.substr(0,5)=="timer"){
			int hour, minu, seco;
			sscanf(cmd.substr(5).c_str(), "%d:%d:%d", &hour, &minu, &seco);
			if(hour>23||hour<0||minu>59||minu<0||seco>59||seco<0){
			    cout<<"不合法的参数:"<<cmd.substr(5)<<'\n';
			    continue;
			}
			cout<<'\n';
			int x=0,y=0,z=0;
			while(hour||minu||seco){
				int stt=clock();
				cout<<"\r过去了"<<x/10<<x%10<<":"<<y/10<<y%10<<":"<<z/10<<z%10<<"，还有"<<hour/10<<hour%10<<":"<<minu/10<<minu%10<<":"<<seco/10<<seco%10;
				z++;
				if(z==60)y++,z=0;
				if(y==60)x++,y=0;
				seco--;
				if(seco<0)minu--,seco=59;
				if(minu<0)hour--,minu=59;
				Sleep(1000-(clock()-stt));
			}
			cout<<"\r过去了"<<x/10<<x%10<<":"<<y/10<<y%10<<":"<<z/10<<z%10<<"，还有"<<hour/10<<hour%10<<":"<<minu/10<<minu%10<<":"<<seco/10<<seco%10<<"\n";
			cout<<"\n计时结束！\n";
		}
		else cout<<"\""<<cmd<<"\"不是一个命令。输入help查看命令列表。\n";
	}
	return 0;
}

