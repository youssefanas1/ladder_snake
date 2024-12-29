#include "SwitchToDesignMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
SwitchToDesignMode::SwitchToDesignMode(ApplicationManager* pApp) : Action(pApp)
{
	// initializing the ApplicationManager pointer data member with initializer list
}

SwitchToDesignMode::~SwitchToDesignMode()
{
}

void SwitchToDesignMode::ReadActionParameters()
{
	//Geting a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	//printing to a descriptive message to the user
	pGrid->PrintErrorMessage("Switch to design mode...click to continue");
	//clearing stutus bar
	pOut->ClearStatusBar();
}

void SwitchToDesignMode::Execute()
{
	ReadActionParameters();
	//Geting a Pointer to output interface from grid
	Output* pOut = pGrid->GetOutput();
	//creating play mode tool bar
	pOut->CreateDesignModeToolBar();
}