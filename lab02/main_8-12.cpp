#include <iostream>    // for cout
#include <time.h>      // for time()
#include <stdlib.h>    // for rand()
#include "Rect.h"
#include "cs1037lib-window.h" // for basic window drawing and keyboard/mouse operations 
#include "cs1037lib-image.h" // for basic image (load/save/display) operations 
using namespace std;

// (global) static variables/objects
int num_rect = 5; 
Rect ** c = new Rect* [num_rect];
Rect *p = NULL; // non-initialized pointers are a common source of "wicked" (unpredictable behaviour) bugs that are hard to track
                // it is safer to set a pointer value to NULL while this pointer is not in use
int *r = &num_rect;

// global function declarations
void draw_rectangles();
void reset_rectangles();

int main() 
{
for (int i=0; i<num_rect; i++)
{
c[i] = NULL;
}
reset_rectangles();
cout << "'digit' = choose\n m  = move \n r = reset" << endl;    // prints hints on the console
srand( (unsigned int) time( NULL ) );    // initialize random number generator

SetWindowTitle("Lab 2");
SetWindowVisible(true); 
draw_rectangles();

char k;
int x,y,btn;
while (!WasWindowClosed()) { // this while-loop allows to probe keyboard (or mouse) for any user interactions 
		if (GetKeyboardInput(&k)) { // checks if some key was pressed and sets value of variable 'k' accordingly 
			
			if      (k == 'r')  reset_rectangles();
			else if (k == '1')  p = c[0];        // LINE 1: pointer 'p' now points at rectangle 'c[0]'
			else if (k == '2')  p = c[1];      // LINE 2: pointer 'p' now points at rectangle 'c[1]'       
			else if (k == '3')  p = c[2];      // LINE 3: pointer 'p' now points at rectangle 'c[2]'			
			else if (k == '4')  p = c[3];      // LINE 2: pointer 'p' now points at rectangle 'c[3]'       
			else if (k == '5')  p = c[4];      // LINE 3: pointer 'p' now points at rectangle 'c[4]'
			else if (k == '6')  p = c[5]; 
			else if (k == '7')  p = c[6]; 
			else if (k == '8')  p = c[7]; 
			else if (k == '9')  p = c[8]; 
			else if (k == 'm')  { 
				if (p!=NULL) p->shift(10,0);    // LINE 4: shifts the rectangle that 'p' points at (if any)
				draw_rectangles();
			}
		}
		if (GetMouseInput(&x,&y,&btn)) // checks if mouse was clicked and sets values of variables 'x','y', and 'btn' accordingly 
			if (btn==1) {    // left button was pressed
				for(int i=0; i<num_rect; i++)
				{
					if(c[i] != NULL)
					{
						if((c[i]->get_top() < y) && (y < c[i]->get_bottom()) && (c[i]->get_left() < x) && (x < c[i]->get_right()))
						{
							delete c[i];
							if (p == c[i])
							{
								p = NULL;
							}
							c[i] = NULL;

							draw_rectangles();
						}
					}
				}
			}
}
for (int i=0; i < num_rect; i++)
{
delete c[i];
}
return 0;
}

// global function definitions

void draw_rectangles() // graphically draws rectangles on the screen
{
// Clear the window to white using functions from cs1037libs-window.h 
SetDrawColour(255,255,255); DrawRectangleFilled(0,0,1280,1024);  
SetDrawColour(255,0,0); DrawText(100, 10, "Welcome to LAB 2");

// Draw each rectangle at its current location using a function from cs1037lib-window.h
for (int i=0; i<num_rect; i++)
if (c[i]!= NULL)
{
		DrawRectangleFilled(c[i]->get_left(), c[i]->get_top(), c[i]->get_right(), c[i]->get_bottom());
}

}

void reset_rectangles()
{
// Iterate over all elements of c: delete c[i] (for the i'th element of c)

// Delete the array: c

num_rect = 1 + rand() % 9;

// Allocate the array c to be a new array of size num_rect

for (int i=0; i<num_rect; i++)
{
c[i] = new Rect( Point(rand()%400, rand()%200) , rand()%40, rand()%80);
}
		

cout << "reset rectangles" << endl;
draw_rectangles();   // immediately displays the new state of all rectangles
}
