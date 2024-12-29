#pragma once

#include "Action.h"

class RollDiceAction : public Action
{

	// No parameters for this action

public:
	Grid* pGrid = pManager->GetGrid(); 
	RollDiceAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
	 
	virtual ~RollDiceAction();
};

