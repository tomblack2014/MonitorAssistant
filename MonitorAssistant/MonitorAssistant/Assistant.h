#pragma once
#include <string>
#include <list>
#include <vector>
#include <time.h>

using namespace std;

class Assistant
{
public:
	//根据xml文件初始化数据
	void Load();

	//将数据保存到xml文件中
	void Save();

	//获取上一条输出信息
	string GetLastMsg();

	//添加一名成员
	void AddMember(const string& name, int parTimes, const tm& lastTime);

	//删除一名成员
	bool DeleteMember(const string& name);

	//决策该由谁参加工作
	void Decide(int memNum, vector<string>& nameList);

	//接受决策后修改文件中数据
	bool Accept();

private:
	struct Member {
		string _name;	//成员名称，主键
		int _parTimes;	//活动参加次数
		tm _lastTime;	//最后参加时间
	};

	string _lastMsg;			//最后一条输出信息
	list<Member> _members;		//成员列表
	list<Member> _updateList;	//待更新成员列表
};