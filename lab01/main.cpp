#include "cs1037lib-window.h"
#include "cs1037lib-image.h"
#include <iostream>
using namespace std;


void main()
{
SetWindowTitle("Lab 1");
SetWindowVisible(true);             // Show main window 

int map = LoadImage("london.png");  // Load image from file
DrawImage(map,0,0);                 // Draw image at xy position (0,0)

int godzilla = LoadImage("stamp.png");


while (!WasWindowClosed())
{ 
                int x,y,button;
                if (GetMouseInput(&x,&y,&button))
				{
                    if (button == 1)
						DrawImage(godzilla,(x-((GetImageSizeX(godzilla))/2)),(y-((GetImageSizeY(godzilla))/2)));		                  
				}
}


DeleteImage(map);                   // Free memory used by image
DeleteImage(godzilla);
}