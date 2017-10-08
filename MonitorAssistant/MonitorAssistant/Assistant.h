#pragma once
#include <string>
#include <list>
#include <vector>
#include <time.h>

using namespace std;

class Assistant
{
public:
	//����xml�ļ���ʼ������
	bool Load();

	//�����ݱ��浽xml�ļ���
	bool Save();

	//���һ����Ա
	void AddMember(const string& name, int parTimes, const tm& lastTime);

	//ɾ��һ����Ա
	bool DeleteMember(const string& name);

	//���߸���˭�μӹ���
	bool Decide(int memNum, list<string>& nameList);

	//���ܾ��ߺ��޸��ļ�������
	bool Accept();

	//�Ǽ�һ����ͬѧͬѧ�μӹ���
	bool Regist(vector<string>nameList, int workTimes);

	//������г�Ա��Ϣ
	void PrintMemberMsg();

	//��ȡ��Ա����
	int GetMemCount();

private:

	static tm StringToDatetime(const char *str);

	static tm GetTimeNow();

	struct Member {
		string _name;	//��Ա���ƣ�����
		int _parTimes;	//��μӴ���
		tm _lastTime;	//���μ�ʱ��
	};

	list<Member> _members;		//��Ա�б�
	list<Member> _updateList;	//�����³�Ա�б�

	static const string _configName;	//�洢��Ա�б���ļ���
};