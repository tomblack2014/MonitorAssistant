#pragma once

#include <string>

using namespace std;

class Member
{
public:
	string GetName() const;

	void SetName(const string& name);

	int GetParTimes() const;

	void SetParTimes(const int& psrTimes);

	int GetLastTime() const;

	void SetLastTime(const int& lastTime);

private:
	string _name;
	int _parTimes;
	int _lastTime;
};