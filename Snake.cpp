#include "Snake.h"
#include "Player.h"
#include"Grid.h"
#include<fstream>

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	//its start cell is above its end cell
	this->endCellPos = endCellPos;
	
}

void Snake::Save(ofstream& OutFile, int type) {
	if (type == 1)
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}
void Snake::Apply(Grid* pGrid, Player* pPlayer) // Applys the effect of the snake by moving player to snake's end cell
{
	//Geting a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	//printing to a descriptive message to the user
	pOut->PrintMessage("You have reached a Snake. Click to continue ...");
	//clearing stutus bar
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	// Applying the snake's effect by moving the player to the endCellPos
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
}
CellPosition Snake::GetEndPosition() const
{
	return CellPosition();
}
Snake::~Snake()
{
}
