#pragma once
#include"Action.h"
class Deleteopj:public Action
{
	Grid* Pcell;//taking input and output action
	Input* pin; // for calling getcellclicked and other membar
	Output* pout; // for clear gameobject after checking it 
	CellPosition delpos; //for knowing where user clicked
	bool del;
public:
	Deleteopj(ApplicationManager* pApp);  // Constructor

	void setdel(bool D);
	bool getdel();
	virtual void ReadActionParameters() ; // Reads parameters required for action to execute 
	// (code depends on action type so virtual)

	virtual void Execute() ;  // Executes action (code depends on action type so virtual)

	virtual ~Deleteopj();  // Virtual Destructor
};

