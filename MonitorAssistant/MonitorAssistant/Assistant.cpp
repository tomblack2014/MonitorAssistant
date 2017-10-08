#include "Assistant.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

#include <iostream>
#include <sstream>
#include <time.h>
#include <algorithm>

using namespace std;

const string Assistant::_configName = "config.xml";

tm Assistant::StringToDatetime(const char *str)
{
	tm tm_;
	int year, month, day, hour, minute, second;
	sscanf(str, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;

	return tm_; //��ʱ��  
}

//����xml�ļ���ʼ������
bool Assistant::Load()
{
	TiXmlDocument xmlDocument(_configName.c_str());
	if (!xmlDocument.LoadFile()) {
		return false;
	}

	TiXmlHandle docHandle(&xmlDocument);
	TiXmlHandle docRoot = docHandle.FirstChildElement("MonitorAssistant");

	//Member
	TiXmlElement* memElement = docRoot.FirstChildElement("Member").ToElement();
	if (!memElement) {
		cout << "invalid file format." << endl;
		return false;
	}
	else {
		if (memElement->Attribute("cnt") == NULL) {
			cout << "invalid file format." << endl;
			return false;
		}
		else {
			int memCount = atoi(memElement->Attribute("cnt"));
			for (int i = 0; i < memCount; i++) {
				stringstream sstream;
				sstream.str("");
				sstream << "mem" << i;
				TiXmlElement* element = memElement->FirstChildElement(sstream.str().c_str())->ToElement();
				if (element == NULL) {
					cout << "invalid file format." << endl;
					return false;
				}
				else {
					Member member;
					if (element->Attribute("name") != NULL && element->Attribute("parTimes") != NULL && element->Attribute("lastTime") != NULL) {
						member._name = element->Attribute("name");
						member._parTimes = atoi(element->Attribute("parTimes"));
						member._lastTime = StringToDatetime(element->Attribute("lastTime"));
					}
				}
			}
		}
	}

	return true;
}

//�����ݱ��浽xml�ļ���
bool Assistant::Save()
{
	TiXmlDocument xmlDocument(_configName.c_str());
	if (!xmlDocument.LoadFile()) {
		return false;
	}

	TiXmlHandle docHandle(&xmlDocument);
	TiXmlHandle docRoot = docHandle.FirstChildElement("MonitorAssistant");

	//Member
	TiXmlElement* memElement = docRoot.FirstChildElement("Member").ToElement();
	if (!memElement) {
		cout << "invalid file format." << endl;
		return false;
	}
	else {
		if (memElement->Attribute("cnt") == NULL) {
			cout << "invalid file format." << endl;
			return false;
		}
		else {
			int memCount = _members.size();
			memElement->SetAttribute("cnt", memCount);

			auto iter = _members.begin();
			for (int i = 0; i < memCount; i++) {
				stringstream sstream;
				sstream.str("");
				sstream << "mem" << i;
				TiXmlElement* element = memElement->FirstChildElement(sstream.str().c_str())->ToElement();
				if (element == NULL) {
					element = new TiXmlElement(sstream.str().c_str());
					element->SetAttribute("name", iter->_name.c_str());
					element->SetAttribute("parTimes", iter->_parTimes);
					char str[20] = { 0 };
					strftime(str, 20, "%Y/%m/%d %H:%M:%S", &iter->_lastTime);
					element->SetAttribute("lastTime", str);
					memElement->LinkEndChild(element);
				}
				else {
					element->SetAttribute("name", iter->_name.c_str());
					element->SetAttribute("parTimes", iter->_parTimes);
					char str[20] = { 0 };
					strftime(str, 20, "%Y/%m/%d %H:%M:%S", &iter->_lastTime);
					element->SetAttribute("lastTime", str);
				}
				iter++;
			}
		}
	}
}

//���һ����Ա
void Assistant::AddMember(const string& name, int parTimes, const tm& lastTime)
{
	Member newMeb;
	newMeb._name = name;
	newMeb._parTimes = parTimes;
	newMeb._lastTime = lastTime;

	_members.push_back(newMeb);
}

//ɾ��һ����Ա
bool Assistant::DeleteMember(const string& name)
{
	bool ret = false;
	for (auto iter = _members.begin(); iter != _members.end(); iter++) {
		if (iter->_name == name) {
			_members.erase(iter);
			ret = true;
			break;
		}
	}
	return ret;
}

bool operator > (tm t1, tm t2) 
{
	return mktime(&t1) > mktime(&t2);
}

//���߸���˭�μӹ���
bool Assistant::Decide(int memNum, list<string>& nameList)
{
	if (memNum <= 0 || memNum > _members.size()) {
		return false;
	}

	auto func = [](const Member& l, const Member& r)
	{

		return l._parTimes != r._parTimes
			? l._parTimes > r._parTimes
			: l._lastTime > r._lastTime;
	};

	//����ȡǰmemNum
	std::sort(_members.begin(), _members.end(), func);

	nameList.clear();
	_updateList = _members;
	auto iter = _updateList.begin();
	
	for (int i = 0; i < memNum; i++) {
		iter->_parTimes++;
		iter->_lastTime = GetTimeNow();
		nameList.push_back(iter->_name);
		iter++;
	}

	return true;
}

//���ܾ��ߺ��޸��ļ�������
bool Assistant::Accept()
{
	_members = _updateList;
	return Save();
}

//�Ǽ�һ����ͬѧ�μӻ���
bool Assistant::Regist(vector<string>nameList, int workTimes)
{
	//������������Ƿ�Ϸ�
	for (auto const& iterO : nameList) {
		bool flag = false;
		for (auto const& iterI : _members) {
			if (iterI._name == iterO) {
				flag = true;
				break;
			}
		}
		if (!flag)
			return false;
	}

	for (auto const& iterO : nameList) {
		for (auto & iterI : _members) {
			if (iterI._name == iterO) {
				iterI._parTimes += workTimes;
				iterI._lastTime = GetTimeNow();
				break;
			}
		}
	}

	return true;
}

//������г�Ա��Ϣ
void Assistant::PrintMemberMsg()
{
	cout << "Printing members' messages��" << endl;
	for (auto const& iter : _members) {
		char str[20] = { 0 };
		strftime(str, 20, "%Y/%m/%d %H:%M:%S", &iter._lastTime);
		cout << "name: " << iter._name << "  "
			<< "parTimes: " << iter._parTimes << "  "
			<< "lastParTime: " << str << endl;
	}
	cout << endl;
}

//��ȡ��Ա����
int Assistant::GetMemCount()
{
	return _members.size();
}

tm Assistant::GetTimeNow()
{
	time_t timeNow = 0;
	time(&timeNow);
	tm* t;
	t = gmtime(&timeNow);

	return *t;
}