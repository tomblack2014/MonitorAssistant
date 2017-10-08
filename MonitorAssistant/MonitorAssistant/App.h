#pragma once

#include "Assistant.h"

class App
{
public:
	void Run();

private:
	void PrintHelp();

	Assistant _asst;
};