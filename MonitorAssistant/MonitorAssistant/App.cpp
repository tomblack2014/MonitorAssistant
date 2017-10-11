#include "App.h"
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

void App::Run()
{
	PrintHelp();
	
	cout << "Loading..." << endl;
	if (!_asst.Load())
		cout << "there is no config file, has already create a new one." << endl;

	bool done = false;
	while (!done) {
		cout << "please input a command : ";

		string cmd;
		cin >> cmd;

		//帮助
		if (cmd == "-h" || cmd == "help") {
			PrintHelp();
		}
		//添加一名成员
		else if (cmd == "-a" || cmd == "add") {
			string name, lastTimeP1, lastTimeP2;
			int parTimes;
			cin >> name >> parTimes >> lastTimeP1 >> lastTimeP2;
			tm tm_t;
			sscanf_s(lastTimeP1.c_str(), "%d-%d-%d", &tm_t.tm_year, &tm_t.tm_mon, &tm_t.tm_mday);
			sscanf_s(lastTimeP2.c_str(), "%d:%d:%d", &tm_t.tm_hour, &tm_t.tm_min, &tm_t.tm_sec);
			_asst.AddMember(name, parTimes, tm_t);
		}
		//删除一名成员
		else if (cmd == "-d" || cmd == "delete") {
			string name;
			cin >> name;
			if (!_asst.DeleteMember(name))
				cout << "delete failed." << endl;
			else
				cout << "delete " << name << " succeed." << endl;
		}
		//决策n名工作者
		else if (cmd == "-dc" || cmd == "decide") {
			int memNum;
			cin >> memNum;

			//check
			if (memNum <= 0 || memNum > _asst.GetMemCount()) {
				cout << "number is invalid." << endl
					 << "please input num in 1~" << _asst.GetMemCount() << endl;
			}

			list<string> nameList;
			_asst.Decide(memNum, nameList);

			//output result
			cout << "you may choose : ";
			for (auto &iter : nameList) {
				cout << iter << " ";
			}
			cout << "to participate the activity." << endl;
			cout << "you can use the \"-de\" command again if you do not like the result, I may give you another." << endl;
		}
		//接受决策
		else if (cmd == "-ac" || cmd == "accept") {
			if (!_asst.Accept()) {
				cout << "accept failed because there is not a decided result." << endl;
			}
			else {
				cout << "accepted!" << endl;
			}
		}
		else if (cmd == "-r"){
			int num = 0;
			cout << "please input the member number." << endl;
			cin >> num;
			if (num <= 0 || num > _asst.GetMemCount()) {
				cout << "invalid member number." << endl;
				continue;
			}
			cout << "please input the member names." << endl;
			vector<string> memNames(num);
			for (int i = 0; i < num; i++) {
				string tmp;
				cin >> tmp;
				if (tmp == "-b")
					continue;
				memNames.push_back(tmp);
			}
			_asst.Regist(memNames, 1);
		}
		//输出当前成员信息
		else if (cmd == "-s" || cmd == "show") {
			_asst.PrintMemberMsg();
		}
		//清屏
		else if (cmd == "-c" || cmd == "clear") {
			system("cls");
		}
		else {
			cout << "invalid input!" << endl;
		}
	}
}

void App::PrintHelp()
{
	cout << "**************************************************************************************************************" << endl
		<< "* welcome to MonitorAssistant!" << endl
		<< "* -h		   show a Help list(none param)" << endl
		<< "* -a		   Add a new member to this system( name(string) parTime(int) lastTime(string, ""y-m-d h:m:s"") )" << endl
		<< "* -d		   Delete a member( name(string) )" << endl
		<< "* -dc		   DeCide a list of members to participate the activity( num(int) )" << endl
		<< "* -ac		   ACcept the last decision(none param)" << endl
		<< "* -r		   Regist the participation of members( num(int) name(string * num))" << endl
		<< "* -s		   Show messages of members(none param)" << endl
		<< "* -c		   Clear the screen(none param)" << endl
		<< "**************************************************************************************************************" << endl
		<< endl;
}