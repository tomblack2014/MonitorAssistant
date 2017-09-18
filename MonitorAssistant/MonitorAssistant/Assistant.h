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
	void Load();

	//�����ݱ��浽xml�ļ���
	void Save();

	//��ȡ��һ�������Ϣ
	string GetLastMsg();

	//���һ����Ա
	void AddMember(const string& name, int parTimes, const tm& lastTime);

	//ɾ��һ����Ա
	bool DeleteMember(const string& name);

	//���߸���˭�μӹ���
	void Decide(int memNum, vector<string>& nameList);

	//���ܾ��ߺ��޸��ļ�������
	bool Accept();

private:
	struct Member {
		string _name;	//��Ա���ƣ�����
		int _parTimes;	//��μӴ���
		tm _lastTime;	//���μ�ʱ��
	};

	string _lastMsg;			//���һ�������Ϣ
	list<Member> _members;		//��Ա�б�
	list<Member> _updateList;	//�����³�Ա�б�
};