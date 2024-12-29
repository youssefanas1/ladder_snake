#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	prisonned = false;
	extraroll = false;
	decreaseroll = false;
	owncard9 = false;
	owncard10 = false;
	owncard11 = false;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::setturncount(int zero)
{
	turnCount = zero;
}

void Player::setjustrolldice(int dice)
{ 
	justRolledDiceNum = dice;
}

int Player::getjustrolldice()
{
	return justRolledDiceNum;
}

void Player::setprisonned(bool gotarrested)
{
	prisonned = gotarrested;
}

bool Player::getprisonned()
{
	return prisonned;
}

bool Player::checkability(int fair)
{
	if (fair > wallet) {
		return false;
	}
	else
	{
		return true;
	}

}

void Player::setstepCount(int s)
{
	stepCount = s;
}

int Player::getplayernum()const 
{
	return playerNum;
}


void Player::setextra(bool card3)
{
	extraroll = card3;
}

void Player::setdecrease(bool card4)
{
	decreaseroll = card4;
}

bool Player::getextra()
{
	return extraroll;
}

bool Player::getdecrease()
{
	return decreaseroll;
}

void Player::setowner9(bool z)
{
	owncard9 = z;
}

bool Player::getowner9()
{
	return owncard9;
}

void Player::setowner10(bool z)
{
	owncard10 = z;
}

bool Player::getowner10()
{
	return owncard10;
}

void Player::setowner11(bool z)
{
	owncard11 = z;
}

bool Player::getowner11()
{
	return owncard11;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	 pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);

	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}


// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{
	turnCount++;
	if (turnCount == 3)
	{
		setprisonned(false);
	}
	if (prisonned == true) {
			return;
		
	}
	
	
	if (prisonned == false) {
		///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


		// == Here are some guideline steps (numbered below) to implement this function ==
		if (getextra()==true)// this if condition for card 3 to increase an extra roll dice with keeping wallet increase
		{
		
			if (turnCount >= 4)
			{
				wallet += diceNumber * 10;
				turnCount = 0;
				setextra(false);
				return;
			}
			setjustrolldice(diceNumber);
			CellPosition postion;
			postion = pCell->GetCellPosition();
			int cellnum = postion.GetCellNum();
			cellnum += diceNumber;
			postion = postion.GetCellPositionFromNum(cellnum);
			Player* play;
			play = pGrid->GetCurrentPlayer();
			pGrid->UpdatePlayerCell(play, postion);
			if (pCell->GetGameObject() != NULL)
			{
				pCell->GetGameObject()->Apply(pGrid, play);
			}
			pGrid->UpdateInterface();
			if (postion.GetCellNum() > 98)
			{
				pGrid->SetEndGame(true);
			}
			return;


		}
		if (getdecrease() == true)// this if condition for card 4 to decraese roll dice with keeping wallet increase
		{

			if (turnCount == 2)
			{
				wallet += diceNumber * 10;
				turnCount = 0;
				
				return;
			}
			setjustrolldice(0);
			CellPosition postion;
			postion = pCell->GetCellPosition();
			int cellnum = postion.GetCellNum();
			cellnum += justRolledDiceNum;
			postion = postion.GetCellPositionFromNum(cellnum);
			Player* play;
			play = pGrid->GetCurrentPlayer();
			pGrid->UpdatePlayerCell(play, postion);
			if (pCell->GetGameObject() != NULL)
			{
				pCell->GetGameObject()->Apply(pGrid, play);
			}
			pGrid->UpdateInterface();
			if (postion.GetCellNum() > 98)
			{
				pGrid->SetEndGame(true);
			}
			setdecrease(false);
			return;


		}

		// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once  DONE
		
		// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
		//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move) DONE
		if (turnCount == 3)
		{
			wallet += diceNumber * 10;
			turnCount = 0;
			return;
		}

		// 3- Set the justRolledDiceNum with the passed diceNumber
		setjustrolldice(diceNumber);
		// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
		//    Using the appropriate function of CellPosition class to update "pos"
		CellPosition postion;
		postion = pCell->GetCellPosition();
		int cellnum = postion.GetCellNum();
		cellnum += diceNumber;
		postion = postion.GetCellPositionFromNum(cellnum);

		// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
		//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
		Player* play;
		play = pGrid->GetCurrentPlayer();

		pGrid->UpdatePlayerCell(play, postion);


		// 6- Apply() the game object of the reached cell (if any)
		if (pCell->GetGameObject() != NULL)
		{
			pCell->GetGameObject()->Apply(pGrid, play);
		}
		pGrid->UpdateInterface();
		// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
		if (postion.GetCellNum() > 98)
		{
			pGrid->SetEndGame(true);
		}
	}
	return;
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}