#include <iostream>    // for cout, rand
#include "cs1037lib-time.h" // for "pause" function 
#include "Queue.h"
#include "Stack.h"
#include "List.h"
#include "Basics2D.h" // Point class is defined in Basics2D.h
#include "Table2D.h"  // declares templated Table2D class (analogous to FloatArray from home work 1)
#include "Image2D.h"  // global functions for drawing Table2D objects as images
#include "lab09.h"

using namespace std;

// GLOBAL PARAMETERS AND SPECIALISED DATA TYPES
Point shift[4] = {Point(1,0), Point(0,1), Point(-1,0), Point(0,-1)}; // shifts between neighboring pixels


// declarations of global variables used in lab 9 
Table2D<RGB> im;       // an image (2d table of RGB values - type RGB is defined in Image2D.h)
Table2D<int> region;   // 2D array storing binary mask for pixels (value 1 means "in", 0 is "out")
List<Point> contour;   // list of "contour" points
bool closedContour=false; // a flag indicating if contour was closed 

// useful operators
bool operator==(const RGB& a, const RGB& b) {return (a.r==b.r) && (a.g==b.g) && (a.b==b.b);}

/////////////////////////////////////////////////////////////////////
/// Global functions to be modified in lab09 ////////////////////////
/////////////////////////////////////////////////////////////////////

// GUI calls this function when a user left-clicks on an image pixel while in "Contour" mode
void addToContour(Point p) 
{
	if(closedContour == false)
		contour.append(p);
}

// GUI calls this function when a user right-clicks on an image pixel while in "Contour" mode
void addToContourLast(Point p)
{
	if (contour.isEmpty()) return;
	// add your code below to "close" the contour
    contour.append(p);
	contour.append(contour.retrieve(1));

	closedContour = true;


}

// GUI calls this function when button "Clear" is pressed, or when new image is loaded
void reset_segm()
{
	cout << "resetting 'contour' and 'region'" << endl;
	// removing all region markings
	region.reset(im.getWidth(),im.getHeight(),0);

	// add your code below to remove all points from the "contour"
	while(!contour.isEmpty())
		contour.popBack();

	closedContour = false;
}

// GUI calls this function when a user middle-clicks on an image pixel while in "Region" mode
// It marks in 'region' a square-shaped subset of pixels adjecent to 'seed' (side=40)
void addSquare(Point seed)
{
	// The code below marks one pixel (seed.x,seed.y) as part of the "region."
	// (Note that draw() function in main.cpp displays all 'region=1' pixels in blue.)
    //
	// GOAL: Change the code below so that, instead of marking just one pixel,
	//       it marks pixels in a square around the seed.
	//       The square should have size 40x40 and be centered at (seed.x, seed.y).
	//
	region[seed]=1;  // seed is a Point; there are 2 overloaded operators[] in Table2D.h 
	                 // this line is equivalent to "region[seed.x][seed.y]=1;" 
	for(int i = -20; i<=20; i++)
		for(int j = -20; j<=20; j++)
			if(region.pointIn(seed.x +i, seed.y +j))
			{
				region[seed.x+i][seed.y+j]=2;
			}

	cout << "added a square region" << endl;
}

// GUI calls this function when a user right-clicks on an image pixel while in "Region" mode.
// It marks in 'region' a set of same-color pixels adjacent to the 'seed'. The neighboring pixels 
// are traversed using DEPTH-FIRST-SEARCH starting at the 'seed'. 
// Unlike previous function "addSquare()", the shape of the added region depends on the image. 
void floodFill_DFS(Point seed)
{
	int counter = 0;                   
	Stack<Point> active_front;        
	active_front.push(seed);
	
	// "mark" all adjecent pixels of the same color in 2D table "region" while traversing them 
	// using DEPTH-FIRST_SEARCH (LIFO order) traversal - use "Stack"
	while (!active_front.isEmpty())
	{
		Point p = active_front.pop();
		region[p]=1;  // pixel p is extracted from the "active_front" and added to "region", but
		counter++;    // then, all "appropriate" neighbors of p are added to "active_front" (below)
		for (int i=0; i<4; i++) // goes over 4 neighbors of pixel p
		{   // uses overloaded operator "+" for Points (see Basics2D.h) and array of 'shifts' (see the top of file)
			Point q = p + shift[i]; // to compute a "neighbor" of pixel p
			if (im.pointIn(q) && region[q]==0 && im[q]==im[seed]) 
			{ // we checked if q is inside image range and that its "color" matches "seed"
			  // Why do we also need condition region[q]==0 ???? 
				active_front.push(q); 
				region[q]=2;  // "region" value 2 is used in "draw()" to visualise pixels that are 
			}                 // inside "active_front"; note that all pixels in "active front"
		}                     // are eventually extracted and their "region" value is set to 1. 
		if (view && counter%60==0) {draw(); Pause(20);} // visualization, skipped if checkbox "view" is off
	}
	cout << "flood filled region of size " << counter << " using DFS traversal (LIFO order, Stack)" << endl;
}

// GUI calls this function when a user left-clicks on an image pixel while in "Region" mode.
// It marks in 'region' a set of same-color pixels adjacent to the 'seed'. The neighboring pixels 
// are traversed using BREADTH-FIRST-SEARCH starting at the 'seed'. 
// This function differs from floodFill_DFS() only by the order of traversal of adjecent pixels.
void floodFill_BFS(Point seed)
{
    // INSTEAD OF CODE BELOW THAT MARKS ONLY ONE PIXEL IN "REGION"...

	// "mark" all adjecent pixels of the same color to 2D array "region" while traversing them 
	// using BREADTH-FIRST_SEARCH (FIFO order) - use "Queue" instead of "Stack"
    // ...

	int counter = 0;                   
	Queue<Point> active_front;        
	active_front.enqueue(seed);
	
	// "mark" all adjecent pixels of the same color in 2D table "region" while traversing them 
	// using DEPTH-FIRST_SEARCH (LIFO order) traversal - use "Stack"
	while (!active_front.isEmpty())
	{
		Point p = active_front.dequeue();
		region[p]=1;  // pixel p is extracted from the "active_front" and added to "region", but
		counter++;    // then, all "appropriate" neighbors of p are added to "active_front" (below)
		for (int i=0; i<4; i++) // goes over 4 neighbors of pixel p
		{   // uses overloaded operator "+" for Points (see Basics2D.h) and array of 'shifts' (see the top of file)
			Point q = p + shift[i]; // to compute a "neighbor" of pixel p
			if (im.pointIn(q) && region[q]==0 && im[q]==im[seed]) 
			{ // we checked if q is inside image range and that its "color" matches "seed"
			  // Why do we also need condition region[q]==0 ???? 
				active_front.enqueue(q); 
				region[q]=2;  // "region" value 2 is used in "draw()" to visualise pixels that are 
			}                 // inside "active_front"; note that all pixels in "active front"
		}                     // are eventually extracted and their "region" value is set to 1. 
		if (view && counter%60==0) {draw(); Pause(20);} // visualization, skipped if checkbox "view" is off
	}


	region[seed]=1; // equivalent to region[seed.x][seed.y]=1; (see Table2D.h)

	// replace the "cout" statement below to indicate the number of "marked" pixels added into "region" using BFS.
	cout << "added one pixel to region" << endl;
}
