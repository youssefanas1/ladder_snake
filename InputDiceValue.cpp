#include "InputDiceValue.h"
#include "Action.h"
#include "Grid.h"
#include "Player.h"

InputDiceValue::InputDiceValue(ApplicationManager *pApp):Action(pApp)
{
}

void InputDiceValue::ReadActionParameters()
{
}

void InputDiceValue::Execute()
{
	if (pGrid->GetEndGame()) {
		(pGrid->GetOutput())->ClearStatusBar();      //r.clearing status bar using funcction clearstatusbar 
		return;
	}
	else
	{
		pGrid->GetOutput()->PrintMessage("Enter a number from 1 to 6");
		diceValue = (pGrid->GetInput())->GetInteger(pGrid->GetOutput()); //to return pout
		//using while to make sure this loop will not be ended until acheiving  condition
		while (diceValue < 1 || diceValue > 6)
		{
			pGrid->GetOutput()->PrintMessage("ERROR: You have not entered a valid dice number! re-enter a dice number 1 to 6 ..");
			diceValue = (pGrid->GetInput())->GetInteger(pGrid->GetOutput());
		}
		(pGrid->GetOutput())->ClearStatusBar();
		Player* pPlayer = pGrid->GetCurrentPlayer(); //getting current player from pGrid
		pPlayer->Move(pGrid, diceValue);             //moving current player by function move of class player
		pGrid->AdvanceCurrentPlayer();  //Advancing the current player number by using pGrid pointer
		pGrid->UpdateInterface();          //updating changes
	}

}

InputDiceValue::~InputDiceValue()
{
}
