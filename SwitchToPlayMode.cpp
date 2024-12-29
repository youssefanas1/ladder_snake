#include "SwitchToPlayMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
SwitchToPlayMode::SwitchToPlayMode(ApplicationManager* pApp) : Action(pApp)
{
	// initializing the ApplicationManager pointer data member with initializer list
}

SwitchToPlayMode::~SwitchToPlayMode()
{
}

void SwitchToPlayMode::ReadActionParameters()
{
	//Geting a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	//printing to a descriptive message to the user
pGrid->PrintErrorMessage("Switch to play mode...click to continue");
	//clearing stutus bar
	pOut->ClearStatusBar();
}

void SwitchToPlayMode::Execute()
{
	ReadActionParameters();
	//Geting a Pointer to output interface from grid
	Output* pOut = pGrid->GetOutput();
	//creating play mode tool bar
	pOut->CreatePlayModeToolBar();
}