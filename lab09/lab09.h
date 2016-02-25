#pragma once

// THIS FILE CONTAINS DECLARATIONS OF SOME GLOBAL VARIABLES AND FUNCTIONS DEFINED IN "lab09.cpp"
// THIS FILE MUST BE INCLUDED IN "main.cpp" and "lab09.cpp" AS BOTH USE THESE GLOBAL VARIABLES AND FUNCTIONS 

extern Table2D<RGB> im;       // an image object set in lab09.cpp, note that type RGB is defined in Image2D.h
extern Table2D<int> region;   // a binary 2D mask of 'region' points - set in lab09.cpp
extern List<Point> contour;   // a list of 'contour' points - set in lab09.cpp
extern bool closedContour;    // a flag indicating if contour was closed - set in lab09.cpp

void addToContour(Point click);
void addToContourLast(Point click);
void addSquare(Point seed);
void floodFill_DFS(Point seed);
void floodFill_BFS(Point seed);
void reset_segm();

extern bool view; // defined in main.cpp (boolean flag set by a check box)
void draw(Point mouse = Point(-1,-1)); // defined in main.cpp, but it is also called in lab09.cpp for visualisation 
