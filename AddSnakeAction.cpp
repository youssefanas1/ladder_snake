#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Snake.h"
#include "Ladder.h"
AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	isValid = true;              // Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	//making needed validations
	if (!endPos.IsValidCell())       //if end position is not valid print error massege
	{
		pGrid->PrintErrorMessage(" You have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (!startPos.IsValidCell())                //if start position is not valid print error massege
	{
		pGrid->PrintErrorMessage(" You have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	if (startPos.GetCellNum() == endPos.GetCellNum())       //if start position is same as end position print error massege
	{
		pGrid->PrintErrorMessage(" It is not possible for Start Cell and End Cell to be the same! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (pGrid->GetCard(startPos)!=NULL)                //if snakes's start position is on a card  print error massege
	{
		pGrid->PrintErrorMessage(" The start cell cannot be a special cell ! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (startPos.VCell() == 8)              // if start position of snake in first row  print error massege
	{
		pGrid->PrintErrorMessage(" The start cell cannot be a cell in the first row ! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (endPos.GetCellNum() > startPos.GetCellNum())         // if end position bigger  than start position print error massege
	{
		pGrid->PrintErrorMessage(" start cell cannot be smaller than end cell ! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;

	}
	if (endPos.HCell() != startPos.HCell())  // if end position and start position are not in the same horizontal line print error massege
	{
		pGrid->PrintErrorMessage(" End cell and start cell should be in the same column ! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	
	pOut->ClearStatusBar();

}

void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (isValid == true)
	{


		// Create a snake object with the parameters read from the user
		Snake* psnake = new Snake(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(psnake);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the snake is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}
}
