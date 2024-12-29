#pragma once
#include "Action.h"
class AddSnakeAction : public Action
{
	// [Action Parameters]
	CellPosition startPos; // 1- The start position of the snake
	CellPosition endPos;   // 2- The end position of the snake
	bool isValid;
	// Note: These parameters should be read in ReadActionParameters()

public:

	AddSnakeAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddSnakeAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Snake Object 
	// then Sets this snake object to the GameObject Pointer of its Cell


	virtual ~AddSnakeAction(); // Virtual Destructor
	


};

