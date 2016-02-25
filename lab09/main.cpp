#include "cs1037lib-window.h" // for basic drawing and keyboard/mouse input operations 
#include "cs1037lib-button.h" // for basic buttons and other GUI controls 
#include <iostream>     // for cout, rand
#include <time.h>
#include "List.h"
#include "Basics2D.h" // Point class is defined in Basics2D.h
#include "Table2D.h"  // declares templated Table2D class (analogous to FloatArray from home work 1)
#include "Image2D.h"  // global functions for drawing Table2D objects as images
#include "lab09.h"    // declarations of global variables and functions used in lab09.cpp

using namespace std;

// declarations of global variables used for GUI controls/buttons/dropLists
const char* image_names[] = { "uwocampus.bmp", "canada.bmp", "liver.bmp" }; // an array of image file names
const char* mode_names[]  = { "CONTOUR", "REGION" }; // an array of mode names 
enum Mode  {DRAW_CONTOUR=0, DRAW_REGION=1}; 
Mode mode = DRAW_CONTOUR; // index of the current mode (in the array 'mode_names')
bool view = true; // flag set by the check box
const int cp_height = 34; // height of "control panel" (area for buttons)
const int pad = 10; // width of extra "padding" around image (inside window)

// declarations of global functions used in GUI (see code below "main")
void left_click(Point click);   // call-back function for left mouse-clicks
void right_click(Point click);  // call-back function for right mouse-clicks
void middle_click(Point click); // call-back function for middle mouse-clicks
void image_load(int index); // call-back function for dropList selecting image file
void mode_set(int index);   // call-back function for dropList selecting mode 
void clear(); // call-back function for button "Clear"
void view_set(bool v);  // call-back function for check box for "view" 


int main()
{
	// initializing buttons/dropLists and the window
 	cout << " left/right clicks - enter contour points or region seeds " << endl; 
 	cout << " click 'Clear' or press 'c' to delete current 'contour' or 'region' " << endl; 
	cout << " click 'X'-box to close the application \n\n " << endl; 
	int blank = CreateTextLabel(""); // adds grey "control panel" for the buttons/dropLists
    SetControlPosition(blank,0,0); SetControlSize(blank,1280,cp_height);
	int dropList_files = CreateDropList(3, image_names, 0, image_load); // the last argument specifies the call-back function, see code below "main"
	int label = CreateTextLabel("Mode:");
	int dropList_modes = CreateDropList(2, mode_names, mode, mode_set); // the last argument specifies the call-back function, see code below "main"
	int button_clear = CreateButton("Clear",clear); // the last argument specifies the call-back function, see code below "main"
	int check_box_view = CreateCheckBox("view" , view, view_set);

	SetWindowTitle("Lab 9");
    SetDrawAxis(pad,cp_height+pad,false); // sets window's "coordinate center" for GetMouseInput(x,y) and for all DrawXXX(x,y) functions in "cs1037utils" 
	                                      // we set it in the left corner below the "control panel" with buttons
	// initializing the application
	image_load(0); // loads the first image from the list "image_names"
	srand((unsigned) time(NULL)); // random number initializer

	SetWindowVisible(true);
	while (!WasWindowClosed()) // WasWindowClosed() returns true when 'X'-box is clicked
	{
		char c;
		if (GetKeyboardInput(&c)) // check keyboard
		{ 
			if (c == 'c') clear(); //
		}

		int x, y, button;
		if (GetMouseInput(&x, &y, &button)) // checks if there are mouse clicks or mouse moves
		{
			Point mouse(x,y); // STORES PIXEL OF MOUSE CLICK
			if      (button == 1) left_click(mouse);   // button 1 means the left mouse button
			else if (button == 2) right_click(mouse);  // button 2 means the right mouse button
			else if (button == 3) middle_click(mouse); // button 3 means the right mouse button
			draw(mouse);
		}
	}
	DeleteControl(button_clear);
	DeleteControl(dropList_files);
	DeleteControl(dropList_modes);     
	DeleteControl(label);
	DeleteControl(check_box_view);
	return 0;
}

// call-back function for the 'mode' selection dropList 
// 'int' argument specifies the index of the 'mode' selected by the user among 'mode_names'
void mode_set(int index)
{
	mode = (Mode) index;
	cout << "drawing mode is set to " << mode_names[mode] << endl;
	reset_segm();
	draw();
}

// call-back function for the 'image file' selection dropList
// 'int' argument specifies the index of the 'file' selected by the user among 'image_names'
void image_load(int index) {
	cout << "loading image file " << image_names[index] << endl;
	im = loadImage<RGB>(image_names[index]); // global function defined in Image2D.h
	if (!im.isEmpty()) SetWindowSize(im.getWidth()+2*pad,im.getHeight()+cp_height+2*pad); // window height includes control panel ("cp")
	reset_segm();  // clears current "contour" and "region" objects - function in lab09.cpp
	draw();
}

// call-back function for button "Clear"
void clear() { 
	reset_segm(); // clears current "contour" and "region" objects - function in lab09.cpp
	draw();
}

// call-back function for check box for "view" check box 
void view_set(bool v) {view=v; draw();}  

// call-back function for left mouse-click
void left_click(Point click)
{
	if (!im.pointIn(click)) return;
	if      (mode==DRAW_CONTOUR) addToContour(click); // function in lab09.cpp
	else if (mode==DRAW_REGION && region[click]==0) floodFill_BFS(click); // function in lab09.cpp
}

// call-back function for right mouse-click
void right_click(Point click)
{
	if (!im.pointIn(click)) return;
	if      (mode==DRAW_CONTOUR) addToContourLast(click); // function in lab09.cpp
	else if (mode==DRAW_REGION  && region[click]==0)  floodFill_DFS(click); // function in lab09.cpp
}

// call-back function for middle mouse-click
void middle_click(Point click)
{
	if (!im.pointIn(click)) return;
	if (mode==DRAW_REGION)  addSquare(click); // function in lab09.cpp
}

// window drawing function
void draw(Point mouse)
{  
	// Clear the window to white
	SetDrawColour(255,255,255); DrawRectangleFilled(-pad,-pad,1280,1024);
	if (im.isEmpty()) return; // return if no image - object "im" is declared in lab09.cpp

	// draws an image "im" - object declared in lab09.cpp
	drawImage(im);  // function "drawImage" draws Table2D objects as images. It is defined in Image2D.h

	if (mode==DRAW_CONTOUR && !contour.isEmpty()) 
	{	// Draw "contour" - object declared in lab09.cpp
		SetDrawColour(255,0,0); 
		unsigned i;
		for (i = 1; i<contour.getLength(); i++)  
			DrawLine(contour.retrieve(i).x,   contour.retrieve(i).y,     // "DrawLine" is a method from CS1037util library
			         contour.retrieve(i+1).x, contour.retrieve(i+1).y);

		// If contour is 'open' and mouse is over the image, draw extra 'preview' line segment to current mouse pos.
		if (im.pointIn(mouse) && !closedContour) 
			DrawLine(contour.retrieve(i).x, contour.retrieve(i).y, mouse.x, mouse.y);
	}
	else if (mode==DRAW_REGION) 
	{   // Draw "region" mask on the top of image ("region" object is declared in lab09.cpp)
		// Declare look-up tables specifying colors and transparancy for each possible integer value (0,1,2) in "region"
		RGB    colors[3]       = { black,  blue,  red};
		double transparancy[3] = { 0,      0.2,   1.0};
		drawImage(region,colors,transparancy); // 4th drawImage() function in Image2D.h
	}
}
