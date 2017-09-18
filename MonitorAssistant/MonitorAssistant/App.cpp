#include "App.h"
#include <string>
#include <iostream>

using namespace std;

void App::Run()
{
	PrintHelp();
	
	bool done = false;
	while (!done) {
		string cmd;
		cin >> cmd;
		if (cmd == "-h") {
			PrintHelp();
		}
		else {
			cout << "invalid input!" << endl;
		}
	}
}

void App::PrintHelp()
{

}