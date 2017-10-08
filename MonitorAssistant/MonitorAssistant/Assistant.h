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
	bool Load();

	//将数据保存到xml文件中
	bool Save();

	//添加一名成员
	void AddMember(const string& name, int parTimes, const tm& lastTime);

	//删除一名成员
	bool DeleteMember(const string& name);

	//决策该由谁参加工作
	bool Decide(int memNum, list<string>& nameList);

	//接受决策后修改文件中数据
	bool Accept();

	//登记一部分同学同学参加工作
	bool Regist(vector<string>nameList, int workTimes);

	//输出所有成员信息
	void PrintMemberMsg();

	//获取成员数量
	int GetMemCount();

private:

	static tm StringToDatetime(const char *str);

	static tm GetTimeNow();

	struct Member {
		string _name;	//成员名称，主键
		int _parTimes;	//活动参加次数
		tm _lastTime;	//最后参加时间
	};

	list<Member> _members;		//成员列表
	list<Member> _updateList;	//待更新成员列表

	static const string _configName;	//存储成员列表的文件名
};