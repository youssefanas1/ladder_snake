#include "Deleteopj.h"
#include"Action.h"
#include"Grid.h"
#include"Output.h"
#include"Input.h"
#include"CellPosition.h"
Deleteopj::Deleteopj(ApplicationManager* pApp):Action(pApp)// used intionlazier list as we used inhertance
{
}

void Deleteopj::setdel(bool D)
{
	del = D;
}

bool Deleteopj::getdel()
{
	return del;
}

void Deleteopj::ReadActionParameters()
{
	
	
	
	Pcell = (pManager->GetGrid());
	pin = Pcell->GetInput();
	pout = Pcell->GetOutput();
	setdel(true);
	pout->PrintMessage("to Delete any GameObject=click on its cell");
	delpos=pin->GetCellClicked();
	
	if (delpos.IsValidCell()!=true)
	{
		Pcell->PrintErrorMessage("this cell is invalid:click to continue... ");          //if the cell clicked isnot valid make del = false and clear what was written on statusbar
		setdel(false);
		pout->ClearStatusBar();
		return;
	}
	pout->ClearStatusBar();
	return;
}

void Deleteopj::Execute()
{
	ReadActionParameters();
	Pcell = (pManager->GetGrid());
	pin = Pcell->GetInput();
	pout = Pcell->GetOutput();
	GameObject* pop = Pcell->GetObjectinCell(delpos);
	if (pop==NULL)
	{
		Pcell->PrintErrorMessage("this cell don't have an gameobject!!:click anywhere to continue"); //check if cell dont have game object
		return;
	}
        if (getdel() == true)
		{
			Pcell->RemoveObjectFromCell(delpos);
			Pcell->PrintErrorMessage("done...! ");   //set the pointer to gameobject with null to delete
		}
		return;
	
}

Deleteopj::~Deleteopj()
{
}
