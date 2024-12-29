#include "Output.h"

#include "Input.h"

////////////////////////////////////////////////////////////////////////////////////////// 

Output::Output()
{
	// Initialize user interface parameters
	UI.InterfaceMode = MODE_DESIGN;

	// Widths and Heights

	UI.StatusBarHeight = 60;
	UI.ToolBarHeight = 55;
	UI.MenuItemWidth = 55;

	UI.width = 1210; // make it divisible by NumHorizontalCells
	UI.height = 610; 
	UI.wx = 5;
	UI.wy = 5;

	UI.CellWidth = UI.width / NumHorizontalCells;
	UI.CellHeight = (UI.height -  UI.ToolBarHeight - UI.StatusBarHeight) / NumVerticalCells;

	// Pen Colors of messages of status bar and players' info
	UI.MsgColor = DARKRED;
	UI.PlayerInfoColor = DARKSLATEBLUE;

	// Background Colors of toolbar and statusbar 
	UI.ToolBarColor = WHITE;
	UI.StatusBarColor = LIGHTGRAY; 

	// Line Colors of the borders of each cell
	UI.GridLineColor = WHITE;

	// Cell Color if Empty & Cell Number Font & Color
	UI.CellColor_NoCard = LIGHTSLATEBLUE;
	UI.CellNumFont = 13;
	UI.CellNumColor = UI.GridLineColor;

	// Cell Color if Has Card & CARD Number Font & Color
	UI.CellColor_HasCard = SALMON;
	UI.CardNumFont = 35;
	UI.CardNumColor = WHITE;

	// Ladder Line Width and Color
	UI.LadderlineWidth = 6;
	UI.LadderColor = DARKSLATEBLUE;

	// The X and Y Offsets of the Space BEFORE Drawing the Ladder (offset from the start X and Y of the Cell)
	UI.LadderXOffset = (UI.CellWidth  - 2 * UI.LadderlineWidth) / 5;
	UI.LadderYOffset = UI.CellHeight / 2;

	// Snake Line Width and Color
	UI.SnakelineWidth = 6;
	UI.SnakeColor = FIREBRICK;

	// Colors of the 4 Players
	UI.PlayerColors[0] = GOLD;
	UI.PlayerColors[1] = DARKSLATEBLUE;
	UI.PlayerColors[2] = KHAKI;
	UI.PlayerColors[3] = CHOCOLATE;

	// Create the output window
	pWind = CreateWind(UI.width + 15, UI.height, UI.wx, UI.wy); 

	// Change the title
	pWind->ChangeTitle("Snakes & Ladders");

	// Create the toolbar, grid area and status bar
	CreateDesignModeToolBar();
	ClearGridArea();
	ClearStatusBar();

}

////////////////////////////////////////////////////////////////////////////////////////// 

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	// The Window Object is created inside the Ouput class
	window* pW = new window(w, h, x, y);
	return pW;
}

////////////////////////////////////////////////////////////////////////////////////////// 

Input* Output::CreateInput() const
{
	// The Input Object is created inside the Output class
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Some Utility Functions										//
//======================================================================================//

int Output::GetCellStartX(const CellPosition& cellPos) const
{
	///TODO: implement the following function as described in Output.h file    done
	int xpostion;
	if (cellPos.IsValidCell()) {
		xpostion = UI.wx + cellPos.HCell() * UI.CellWidth;
	}
	else {
		xpostion= UI.wx;
	}//assume cellpos.hcell return num from 0 to 10
		                                    //then adding it to wx  
		return xpostion;
}// this line should be changed with your implementation

//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCellStartY(const CellPosition & cellPos) const
{
	///TODO: implement the following function as described in Output.h file
	int ypostion;
	if (cellPos.IsValidCell()) {
		ypostion = cellPos.VCell()*UI.CellHeight + UI.ToolBarHeight;   //assume cellpos.vcell return num from 0 to 8
		                                                          //then adding it to toolbar height+wy  
			
	}// this line should be changed with your implementation
	else {
		ypostion = UI.ToolBarHeight + UI.wy;
	}

	return ypostion;
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCardNumber(const CellPosition & cellPos, int cardNum) const
{
	// Get the X and Y of the upper left corner of the cell
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// Set the pen and font
	pWind->SetPen(UI.CardNumColor);
	pWind->SetFont(UI.CardNumFont, BOLD | ITALICIZED , BY_NAME, "Arial");

	int w=0, h=0;


	///TODO: Calculate the Width & Height of the integer "cardNum" if written using the Current Font
	//       (Use GetIntegerSize() window function) and set the "w" and "h" variables with its width and height      DONE
	pWind->GetIntegerSize( w, h, cardNum);


	// Calculate where to write the integer of the cardNum
	int x = cellStartX + UI.CellWidth - UI.LadderXOffset - w - 5; // Before the End vertical line of a ladder 
	                                                              // (assuming the case where ladder is inside the cell)
	int y = cellStartY + (UI.CellHeight - h) / 2;	// in the vertical Middle of the cell


	///TODO: Draw the Integer the representing the "cardNum" in the location (x,y)
	pWind->DrawInteger(x, y, cardNum);


}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const
{
	// Clear by drawing a rectangle filled with toolbar background color
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::ClearStatusBar() const
{
	// Clear drawing a rectangle filled with statusbar background color
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearGridArea() const
{
	// Draw each cell in the Grid: ( NumVerticalCells * NumberHorizontalCells )
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			CellPosition cellPos(i, j);
			DrawCell(cellPos); // Initially NO Cards in the cell
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDesignModeToolBar() const
{
	UI.InterfaceMode = MODE_DESIGN;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// ** MAKE SURE THAT THE IMAGES ARE .JPG FILES **
	string MenuItemImages[DESIGN_ITM_COUNT];
	MenuItemImages[ITM_ADD_LADDER] = "images\\Menu_Ladder.jpg";
	MenuItemImages[ITM_ADD_SNAKE] = "images\\Menu_Snake.jpg";
	MenuItemImages[ITM_ADD_CARD] = "images\\Menu_Card.jpg";
	MenuItemImages[ITM_COPY_CARD] = "images\\copy.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu_Exit.jpg";
	MenuItemImages[ITM_TO_PLAY_MODE] = "images\\Menu_SwitchToGame.jpg";
	MenuItemImages[ITM_PASTE_CARD] = "images\\paste.jpg";
	MenuItemImages[ITM_CUT_CARD] = "images\\cut.jpg";
	MenuItemImages[ITM_DELETE_CARD] = "images\\del.jpg";
	MenuItemImages[ITM_SAVE_GRID] = "images\\save.jpg";
	MenuItemImages[ITM_OPEN_GRID] = "images\\open.jpg";

	///TODO: Prepare images for each menu item and add it to the list



	// Draw menu item one image at a time
	for(int i=0; i < DESIGN_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayModeToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;

	ClearToolBar(); // in order not to draw above the icons of the other mode when you switch

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way

	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum DESIGN_MODE_ITEMS
	// ** MAKE SURE THAT THE IMAGES ARE .JPG FILES **
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_ROLL_DICE] = "images\\Menu_Dice.jpg";
	MenuItemImages[ITM_INPUT_DICE_VALUE] = "images\\input.jpg";
	MenuItemImages[ITM_TO_DESIGN_MODE] = "images\\Menu_SwitchToGrid.jpg";
	MenuItemImages[ITM_NEW_GAME] = "images\\new.jpg";
	MenuItemImages[ITM_EXITP] = "images\\Menu_Exit.jpg";
	///TODO: Prepare images for each menu item and add it to the list



	// Draw menu item one image at a time
	for(int i=0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	// Set pen and font before drawing the string on the window
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(18, BOLD , BY_NAME, "Verdana");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.3), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintPlayersInfo(string info)
{
	///TODO: Clear what was written on the toolbar     DONE
	CreatePlayModeToolBar();
	// One of the correct ways to implement the above TODO is to call CreatePlayModeToolBar(); 
	// to clear what was written in the player info (there are other ways too � You are free to use any)

	// Set the pen and font before drawing the string on the window
	pWind->SetPen(UI.PlayerInfoColor); 
	pWind->SetFont(20, BOLD , BY_NAME, "Verdana");   

	int w=0, h=0;

	///TODO: Calculate the Width and Height of the string if drawn using the current font 
	//       (Use GetStringSize() window function) and set the "w" and "h" variables with its width and height
	pWind->GetStringSize( w,  h,info);


	// Set the start X & Y coordinate of drawing the string
	int x = UI.width - w - 20; // space 20 before the right-side of the window
	                           // ( - w ) because x is the coordinate of the start point of the string (upper left)
	int y = (UI.ToolBarHeight - h) / 2; // in the Middle of the toolbar height

	///TODO: Draw the string "info" in the specified location (x, y)      DONE
	pWind->DrawString (x, y, info);


}

//======================================================================================//
//			         			Game Drawing Functions   								//
//======================================================================================//

void Output::DrawCell(const CellPosition & cellPos, int cardNum) const
{
	// Get the Cell Number (from 1 to NumVerticalCells*NumHorizontalCells) and the X & Y of its upper left corner
	int cellNum = cellPos.GetCellNum();
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// ----- 1- Draw the cell itself (background) --> Filled Rectangle -----
	pWind->SetPen(UI.GridLineColor, 1);
	if (cardNum == -1) // no card
		pWind->SetBrush(UI.CellColor_NoCard);
	else
		pWind->SetBrush(UI.CellColor_HasCard);

	///TODO: Draw the Cell Rectangle using the appropriate coordinates
	pWind->DrawRectangle(cellStartX, cellStartY, cellStartX + UI.CellWidth, cellStartY + UI.CellHeight, FILLED);


	// ----- 2- Draw the CELL number (the small number at the bottom right of the cell) -----
	pWind->SetPen(UI.CellNumColor);
	pWind->SetFont(UI.CellNumFont, BOLD , BY_NAME, "Verdana");   

	int w=0, h=0;

	///TODO: Get the Width and Height of the Cell Number if written using the current font 
	//       (Use GetIntegerSize() window function) and set the "w" and "h" variables with its width and height
	pWind->GetIntegerSize(w, h, cellNum);


	// Calculate X & Y coordinate of the start point of writing the card number (upper left point of the cell num)
	int x = cellStartX + (UI.CellWidth - w - 1);   // space 1 from the end of the cell width
												   // ( - w ) because x is for the start point of cell num (num's left corner)
	int y = cellStartY + (UI.CellHeight - h - 1);  // space 1 from the end of the cell height
												   // ( - w ) because y is for the start point of cell num (num's upper corner)
	
	///TODO: Draw the cell number in the x and y location
	pWind->DrawInteger(x, y, cellNum);
	

	// ----- 3- Draw card number (if any) -----
	if (cardNum != -1) // Note: cardNum -1 means no card
		DrawCardNumber(cellPos, cardNum);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawPlayer(const CellPosition & cellPos, int playerNum, color playerColor) const
{

	///TODO: Validate the playerNum, if not valid return
	if (cellPos.IsValidCell()) {
		if (playerNum < 0 || playerNum>3)
			return;
		else {


			// Get the X & Y coordinates of the start point of the cell (its upper left corner)
			int cellStartX = GetCellStartX(cellPos);
			int cellStartY = GetCellStartY(cellPos);

			// Calculate the Radius of the Player's Circle
			int radius = UI.CellWidth / 14; // proportional to cell width

			// Calculate the horizontal space before drawing players circles (space from the left border of the cell)
			int ySpace = UI.CellHeight / 6; // proportional to cell height

			// Note: Players' Circles Locations depending on "playerNum" is as follows:
			// Player_0   Player_1
			// Player_2   Player_3

			// Calculate the Y coordinate of the center of the player's circle (based on playerNum)
			int y = cellStartY + ySpace + radius + 2;
			if (playerNum == 2 || playerNum == 3)
				y += radius + 2 + radius; // because playerNum 2 and 3 are drawn in the second row of circles

			// Calculate the Y coordinate of the center of the player's circle (based on playerNum)
			int x = cellStartX + UI.LadderXOffset + radius + 4; // UI.LadderXOffset is used to draw players' circles 
			// AFTER the ladder start vertical line (assuming there is a ladder)
			// for not overlapping with ladders
			if (playerNum == 1 || playerNum == 3)
				x += radius + 2 + radius; // because playerNum 1 and 3 are drawn in the second column of circles

			///TODO: Draw the player circle in center(x,y) and filled with the playerColor passed to the function     DONE
			pWind->SetPen(playerColor);
			pWind->SetBrush(playerColor);
			pWind->DrawCircle(x, y, radius, FILLED);

		}
	}
	return;
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawLadder(const CellPosition& fromCell, const CellPosition& toCell) const
{

	///TODO: Validate the Cell Position (Must be Vertical Cells AND toCell above fromCell, otherwise, Do NOT draw)
	if (!(fromCell.VCell() > toCell.VCell())) { //draws the ladder vertical and from down
		return;
	}




	// Get the start X and Y coordinates of the upper left corner of the fromCell
	int cellStartX = GetCellStartX(fromCell);
	int fromStartY = GetCellStartY(fromCell);

	// Get the start Y coordinates of the upper left corner of the toCell (the X should be the same as fromCell .. Vertical)
	int toStartY = GetCellStartY(toCell);

	// ---- 1- Draw the First Vertical Line ---- 
	int x12 = cellStartX + UI.LadderXOffset; // the two points have the same x (vertical)
	int y1 = fromStartY + UI.LadderYOffset;  // the coordinate y of the first point of the First Vertical line
	int y2 = toStartY + UI.CellHeight - UI.LadderYOffset; // the coordinate y of the second point of the First Vertical line

	///TODO: Set pen color and width using the appropriate parameters of UI_Info object (UI)
	pWind->SetPen(UI.LadderColor, UI.LadderlineWidth);   //sets the color of the ladder


	///TODO: Draw The First Vertical Line (The Left Line) in the appropriate coordinates

	   // draws the first line of the ladder with the size Size of the horizontal space before drawing the ladder

	pWind->DrawLine(x12, y1, x12, y2);  // first line

	// ---- 2- Draw the Second Vertical Line ---- 
	int x34 = cellStartX + UI.CellWidth - UI.LadderXOffset; // same x (vertical line)
	// the y coordinates is the same as the First Vertical Line

///TODO: Set pen color and width using the appropriate variables of UI_Info object (UI)

	pWind->SetPen(UI.LadderColor, UI.LadderlineWidth);

	///TODO: Draw The Second Vertical Line (The Right Line) in the appropriate coordinates

	pWind->DrawLine(x34, y1, x34, y2);    //second line


	// ---- 3- Draw the Cross Horizontal Lines ---- 

	// The cross lines are drawn on the Horizontal Borders of the Cells between fromCell to toCell
	// Check the drawn ladders in the project document and imitate it

	///TODO: Draw the cross horizontal lines of the ladder using the appropriate coordinates


	int h = y1 - UI.CellHeight / 2;


	for (int i = 0; i < (fromCell.VCell() - toCell.VCell()); i++)  //draws the cross section horizontal line accros all the all ladder length
	{
		pWind->DrawLine(x12, h, x34, h + 1);

		h = h - UI.CellHeight;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawSnake(const CellPosition& fromCell, const CellPosition& toCell) const
{

	///TODO: Validate the fromCell and toCell (Must be Vertical and toCell is below fromCell otherwise do NOT draw)
	if (!( fromCell.VCell() < toCell.VCell())) {   // draws snake vertical and from down
		return;
	}


	// Get the upper left corner coordinates of the fromCell and toCell
	int cellStartX = GetCellStartX(fromCell); // same for fromCell and toCell (vertical)
	int fromStartY = GetCellStartY(fromCell);
	int toStartY = GetCellStartY(toCell);

	// ---- 1- Draw Line representing the Snake Body ----

	// Set coordinates of start and end points of the Line of the Snake's Body
	int x12 = cellStartX + UI.LadderXOffset / 2; // same for the start and end point (vertical)
	int y1 = fromStartY + UI.CellHeight / 2;
	int y2 = toStartY + UI.CellHeight / 2;

	///TODO: Set pen color and width from the appropriate variables of the UI_Info object (UI)

	pWind->SetPen(UI.SnakeColor , UI.SnakelineWidth);   //sets the color of the snakes body and sets snake line width

	///TODO: Draw the Line representing the Snake BOdy
	   
	pWind->DrawLine(x12, y1, x12 , y2 + 1);   // draws line of the snake
	// ---- 2- Draw Polygon with Diamond Shape representing the Snake Head ----

	// Set Pen and Brush (background) of the Polygon
	pWind->SetPen(UI.SnakeColor, UI.SnakelineWidth);
	pWind->SetBrush(UI.SnakeColor);

	int yChange = UI.CellHeight / 4; // slight vertical difference to be used in the up and down polygon points
	int xChange = UI.CellWidth / 14; // slight horizontal difference to be used in the left and right polygon points

	///TODO: Set the coordinates of the 4 points of the Polygon
	//       Check the snakes drawn in the project document and draw it the same way
	int Xright = x12 + xChange;    //right point of the snakes head
	int Xleft = x12 - xChange;     //left point of the nsakes head
	int Ydown = y1 + yChange;      //down point of the snakes head
	int Yup = y1 - yChange;        //upper point of the snakes head

	int Ax[5] = { Xleft,x12,Xright,x12,Xleft };
	int Ay[5] = { y1,Yup,y1,Ydown,y1 };
	///TODO: Draw the Polygon (diamond) representing the Snake's Head
	//       Check the snakes drawn in the project document and draw it the same way

	pWind->DrawPolygon(Ax, Ay, 5);   // draws the polygon (daimond head)

}

//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	// deallocating the window object
	delete pWind;
}

