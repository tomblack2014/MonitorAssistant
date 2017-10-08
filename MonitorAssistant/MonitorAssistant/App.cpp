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

		//����
		if (cmd == "-h" || cmd == "help") {
			PrintHelp();
		}
		//���һ����Ա
		else if (cmd == "-a" || cmd == "add") {
			string name, lastTime;
			int parTimes;
			cin >> name >> parTimes >> lastTime;
			tm tm_t;
			sscanf_s(lastTime.c_str(), "%d-%d-%d %d:%d:%d", &tm_t.tm_year, &tm_t.tm_mon, &tm_t.tm_mday, &tm_t.tm_hour, &tm_t.tm_min, &tm_t.tm_sec);
			_asst.AddMember(name, parTimes, tm_t);
		}
		//ɾ��һ����Ա
		else if (cmd == "-d" || cmd == "delete") {
			string name;
			cin >> name;
			if (!_asst.DeleteMember(name))
				cout << "delete failed." << endl;
		}
		//����n��������
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
		//���ܾ���
		else if (cmd == "-ac" || cmd == "accept") {
			if (!_asst.Accept()) {
				cout << "accept failed because there is not a decided result." << endl;
			}
			else {
				cout << "accepted!" << endl;
			}
		}
		else if (cmd == "-e"){
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
		//�����ǰ��Ա��Ϣ
		else if (cmd == "-s" || cmd == "show") {
			_asst.PrintMemberMsg();
		}
		//����
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
	cout << "welcome to MonitorAssistant!" << endl
		<< "-h         show a Help list" << endl
		<< "-a		   Add a new member to this system" << endl
		<< "-d		   Delete a member" << endl
		<< "-dc		   DeCide a list of members to participate the activity" << endl
		<< "-ac		   ACcept the last decision" << endl
		<< "-s		   Show messages of members" << endl
		<< "-c		   Clear the screen" << endl;
}