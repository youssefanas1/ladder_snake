#include "Ladder.h"
#include<fstream>
Ladder::Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
	//its start cell is below its end cell
	if ((startCellPos.HCell() != endCellPos.HCell()) || startCellPos.VCell() < endCellPos.VCell())
	{
		if ((startCellPos.HCell() != endCellPos.HCell()) && startCellPos.VCell() > endCellPos.VCell())
		{
			this->endCellPos = endCellPos;
			this->endCellPos.SetHCell(startCellPos.HCell());
		}
		else if ((startCellPos.HCell() == endCellPos.HCell()) && startCellPos.VCell() < endCellPos.VCell())
		{
			position = endCellPos;
			this->endCellPos = startCellPos;
		}
		else
		{
			position = endCellPos;
			this->endCellPos = startCellPos;
			this->endCellPos.SetHCell(endCellPos.HCell());
		}
	}
	else {
		this->endCellPos = endCellPos;
	}
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	//Geting a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	//printing to a descriptive message to the user
	pOut->PrintMessage("You have reached a ladder..Click to continue ...");
	//clearing stutus bar
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream& OutFile, int type) {
	if (type == 0)
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}

Ladder::~Ladder()
{
}

