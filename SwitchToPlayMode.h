#pragma once

#include "Action.h"

class SwitchToPlayMode : public Action
{
public:
	Grid* pGrid = pManager->GetGrid();
	SwitchToPlayMode(ApplicationManager* pApp);
	virtual ~SwitchToPlayMode();
	virtual void ReadActionParameters();
	virtual void Execute();
};

