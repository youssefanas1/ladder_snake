#pragma once
#include "Action.h"
#include <iostream>
#include <fstream>

class SaveClass : public Action
{
private:
	ofstream save;
	string filename;

public:
	SaveClass(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	~SaveClass(void);
};

