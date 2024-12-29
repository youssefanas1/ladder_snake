#include "SaveClass.h"
#include "Grid.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"
#include "Cell.h"
#include "CardOne.h"
#include "CardTwo.h"


SaveClass::SaveClass(ApplicationManager* pApp) : Action(pApp)
{
}

void SaveClass::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;

	pOut->PrintMessage("Enter file name...");
	filename = pIn->GetSrting(pOut);
	pGrid->PrintErrorMessage("file has been created..(click to continue)");
	pOut->ClearStatusBar();
	save.open(filename + ".txt");

}

void SaveClass::Execute()
{

	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	ofstream SaveFile(filename + ".txt", ios::out);
	pGrid->SetNums();
	SaveFile << pGrid->GetNumLadder() << endl;
	pGrid->SaveAll(SaveFile, 0);
	SaveFile << pGrid->GetNumSnakes() << endl;
	pGrid->SaveAll(SaveFile, 1);
	SaveFile << pGrid->GetNumCards() << endl;
	pGrid->SaveAll(SaveFile, 2);
	SaveFile.close();
}

SaveClass::~SaveClass(void)
{
}
