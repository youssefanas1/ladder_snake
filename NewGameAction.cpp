#include "NewGameAction.h"
#include "Grid.h"
#include "Player.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
NewGameAction::NewGameAction(ApplicationManager* pApp) :Action(pApp)
{

}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute()
{	
	

	CellPosition pos(8, 0); //the first cell in the game has vcell 8 (last row) and hcell 0 (first column)
	Grid* pGrid = pManager->GetGrid();

	CardNine* card9 = nullptr;
	CardTen* card10 = nullptr;
	CardEleven* card11 = nullptr;

	for (int i = 0; i < 4; i++)
	{
		pGrid->UpdatePlayerCell(pGrid->GetCurrentPlayer(), pos);
		pGrid->GetCurrentPlayer()->setturncount(0); //resets the game conditions
		pGrid->GetCurrentPlayer()->SetWallet(100);
		pGrid->AdvanceCurrentPlayer();//advances to the next player
		pGrid->UpdateInterface();
		pGrid->GetCurrentPlayer()->setowner9(false); //resets the ownership of the cards
		card9->setownership(NULL);
		pGrid->GetCurrentPlayer()->setowner10(false);
		card10->setownership(NULL);
		pGrid->GetCurrentPlayer()->setowner11(false);
		card11->setownership(NULL);
	}


	while (pGrid->GetCurrentPlayer()->getplayernum()!=0) // to make first player (player 0) start when new game is clicked breaks when it gets to player number 0 to make him start and play the first after excuting newgameaction
	{
		pGrid->AdvanceCurrentPlayer(); //looping till reaching first player (player 0) 
	}

	
}

NewGameAction::~NewGameAction()
{
}

