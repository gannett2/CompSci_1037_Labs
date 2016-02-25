#include <iostream>    // for cout
#include <time.h>      // for time()
#include <stdlib.h>    // for rand()
#include "Rect.h"
#include "cs1037lib-window.h" // for basic window drawing and keyboard/mouse operations 
#include "cs1037lib-image.h" // for basic image (load/save/display) operations 
using namespace std;

// (global) static variables/objects
Rect a(Point(100,100),Point(130,130));  
Rect b(Point(200,150),50,20);   
Rect *c = NULL;
Rect *p = NULL; // non-initialized pointers are a common source of "wicked" (unpredictable behaviour) bugs that are hard to track
                // it is safer to set a pointer value to NULL while this pointer is not in use

// global function declarations
void draw_rectangles();
void reset_rectangles();

int main() 
{

cout << a.get_left() << endl;
cout << b.get_bottom() << endl;

cout << "a-c = choose\n m  = move \n r = reset" << endl;    // prints hints on the console
srand( (unsigned int) time( NULL ) );    // initialize random number generator

SetWindowTitle("Lab 2");
SetWindowVisible(true); 
draw_rectangles();

char k;
while (!WasWindowClosed()) // this while-loop allows to probe keyboard (or mouse) for any user interactions 
{
		
		if (GetKeyboardInput(&k)) // checks if some key was pressed and sets value of variable 'k' accordingly 
		{ 
			
			if      (k == 'r')  reset_rectangles();
			else if (k == 'a')
			{
				p=&a;      // LINE 1: pointer 'p' now points at rectangle 'a'
				cout << "p points at rectangle of width " << a.get_length() << " and height " << a.get_height() << endl;
			}
			else if (k == 'b')  
			{
				p=&b;      // LINE 2: pointer 'p' now points at rectangle 'b'  
				cout << "p points at rectangle of width " << b.get_length() << " and height " << b.get_height() << endl;
			}
			else if (k == 'c') 
			{
				if (c!=NULL)
				{
				p=c;      // LINE 3: pointer 'p' now points at rectangle 'c'
				cout << "p points at rectangle of width " << (*c).get_length() << " and height " << c->get_height() << endl;
				}
				else{}
			}
			else if (k == 'm')  
			{          
				if (p!=NULL) p->shift(10,0);     // LINE 4: shifts the rectangle that 'p' points at (if any)
				draw_rectangles();
			}
			else if (k == 'n')
			{
				if (c == NULL)
				{
					c = new Rect( Point(rand()%400, rand()%200) , rand()%40, rand()%80);
					draw_rectangles();
				}
			}
			else if (k == 'd')
			{
				if (c != NULL)
				{
					delete c;
					if(p == c)
					{
						p = NULL;
					}
					c = NULL;
					draw_rectangles();
				}
			}


			 cout << "pointer p has value " << p << endl;
		}
}

delete c;
return 0;
}

// global function definitions

void draw_rectangles() // graphically draws rectangles on the screen
{
// Clear the window to white using functions from cs1037libs-window.h 
SetDrawColour(255,255,255); DrawRectangleFilled(0,0,1280,1024);  
SetDrawColour(255,0,0); DrawText(100, 10, "Welcome to LAB 2");

// Draw each rectangle at its current location using a function from cs1037lib-window.h
DrawRectangleFilled(a.get_left(), a.get_top(), a.get_right(), a.get_bottom());
DrawRectangleFilled(b.get_left(), b.get_top(), b.get_right(), b.get_bottom());
if (c!=NULL)
{
DrawRectangleFilled(c->get_left(), c->get_top(), c->get_right(), c->get_bottom());
}
else{}
}

void reset_rectangles()
{
if (c!=NULL)
{
*c = Rect( Point(rand()%400, rand()%200) , rand()%40, rand()%80);
}
else{}
a = Rect( Point(rand()%400, rand()%200) , rand()%40, rand()%80);
b = Rect( Point(rand()%400, rand()%200) , rand()%40, rand()%80);



cout << "reset rectangles" << endl;
draw_rectangles();   // immediately displays the new state of all rectangles
}

