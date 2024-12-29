#pragma once

#include "Action.h"

class SwitchToDesignMode : public Action
{
public:
	Grid* pGrid = pManager->GetGrid();
	SwitchToDesignMode(ApplicationManager* pApp);
	virtual ~SwitchToDesignMode();
	virtual void ReadActionParameters();
	virtual void Execute();
};


