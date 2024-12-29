#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	isValid = true;             // Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters
	if (!endPos.IsValidCell())         //if end position is not valid print error massege
	{
		pGrid->PrintErrorMessage(" You have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (!startPos.IsValidCell())        //if start position is not valid print error massege
	{
		pGrid->PrintErrorMessage(" You have not selected a valid cell! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}

	if (startPos.GetCellNum() == endPos.GetCellNum())  //if start position is same as end position print error massege
	{
		pGrid->PrintErrorMessage(" It is not possible for Start Cell and End Cell to be the same! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (pGrid->GetCard(startPos)!=NULL)      //if ladder's start position is on a card  print error massege
	{
		pGrid->PrintErrorMessage(" The start cell cannot be a special cell ! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (startPos.VCell() == 0)  // if start position of ladder in last row  print error massege
	{
		pGrid->PrintErrorMessage(" The start cell cannot be a cell in the last row ! Click to continue ...");
		pOut->ClearStatusBar();
		isValid = false;
		return;
	}
	if (endPos.GetCellNum() < startPos.GetCellNum())  // if end position smaller than start position print error massege
	{
		pGrid->PrintErrorMessage(" End cell cannot be smaller than start cell ! Click to continue ...");
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
	
	
	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (isValid == true)
	{


		// Create a Ladder object with the parameters read from the user
		Ladder* pLadder = new Ladder(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pLadder);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}
}
