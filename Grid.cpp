#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Snake.h"
#include<fstream>



Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}


void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========
Player* Grid::GetNearestPlayer(Player* pPlayer)
{
	Player* NearestPlayer = GetCurrentPlayer();

	int min = 100;

	int currentpos = pPlayer->GetCell()->GetCellPosition().GetCellNum();//gets cell number of the current position

	for (int i = 0; i < 4; i++)
	{

		if (NearestPlayer == PlayerList[i])//sees if the anyone in front of u 
		{

			PrintErrorMessage("No one ahead click to continue....");

			continue;
		}
		else
		{
			int nextposition = PlayerList[i]->GetCell()->GetCellPosition().GetCellNum();

			int difference = nextposition - currentpos;//sees the nearest player from the current position of the card

			if (difference < min && difference>0)
			{
				min = difference;

				NearestPlayer = PlayerList[i];
			}
		}	
	}
	return NearestPlayer;
}

int Grid::GetcurrPlayerNumber()
{
	return currPlayerNumber;
}

void Grid::SaveAll(ofstream& OutFile, int type) {
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject())
				CellList[i][j]->GetGameObject()->Save(OutFile, type);
		}
	}
}

int Grid::GetNumLadder() { return LadderNum; }
int Grid::GetNumSnakes() { return SnakesNum; }
int Grid::GetNumCards() { return CardsNum; }
void Grid::SetNums()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder())
			{
				LadderNum++;
			}

			if (CellList[i][j]->HasSnake())
			{
				SnakesNum++;
			}


			if (CellList[i][j]->HasCard())
			{
				CardsNum++;
			}

		}
	}
}






Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			if (CellList[i][j]->HasLadder() != NULL)
			{
				return CellList[i][j]->HasLadder();
			}
			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}
//rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
Card* Grid::GetCard(const CellPosition& position) const
{
	if (position.IsValidCell()) // Validation for the passed CellPostion (Position)
	{
		if (CellList[position.VCell()][position.HCell()]->HasCard())
			return CellList[position.VCell()][position.HCell()]->HasCard(); // Returning the card of the selected CellPosition
	}
	return NULL; // Returning NULL in case there is no card in the CellPosition
}

Snake* Grid::GetSnake(const CellPosition& position) const
{
	if (position.IsValidCell()) // Validation for the passed CellPostion (Position)
	{
		if (CellList[position.VCell()][position.HCell()]->HasSnake())
			return CellList[position.VCell()][position.HCell()]->HasSnake(); // Returning the Snake of the selected CellPosition
	}
	return NULL; // Returning NULL in case there is no Snake in the CellPosition
}

Snake* Grid::GetNextSnake(const CellPosition& position) const
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the Snake in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			if (CellList[i][j]->HasSnake() != NULL)
				return CellList[i][j]->HasSnake();
			// Check if CellList[i][j] has a Snake, if yes return it
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Ladder* Grid::GetLadder(const CellPosition& position) const
{
	if (position.IsValidCell()) // Validation for the passed CellPostion (Position)
	{
		if (CellList[position.VCell()][position.HCell()]->HasLadder())
			return CellList[position.VCell()][position.HCell()]->HasLadder(); // Returning the ladder of the selected CellPosition
	}
	return NULL; // Returning NULL in case there is no ladder in the CellPosition
}
GameObject* Grid::GetObjectinCell(const CellPosition& pos) {
	// Get the cell object that corresponds to the given CellPosition
	Cell* cell = CellList[pos.VCell()][pos.HCell()];
	if (cell->HasLadder()) {
		// If the cell has a ladder, return a pointer to that ladder object
		return cell->HasLadder();
	}
	// Check if the cell has a snake object on it
	else if (cell->HasSnake()) {
		// If the cell has a snake, return a pointer to that snake object
		return cell->HasSnake();
	}
	else if (cell->HasCard()) {
		return cell->HasCard();

	}
	// If there is no game object at the given CellPosition, return a nullptr
	else {
		return nullptr;
	}
}

// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}