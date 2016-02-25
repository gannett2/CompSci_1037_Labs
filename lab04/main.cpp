#include "cs1037lib-window.h" // for basic drawing and keyboard/mouse input operations 
#include <iostream>    // for cout
#include <stdlib.h>    // for srand() 
#include <time.h>      // for time()
#include "Cstr.h"      // for simple "string" generation 
#include "ImageCard.h"
#include "DynArray.h"



using namespace std;

// global variables
DynArray<char> s, d;
DynArray<ImageCard*> c;


// global function declarations
void draw_cards();
void reset_cards(int n);
void clear_cards();
void left_click(Point click);
void right_click(Point click);

int main()
{
	srand( (unsigned int) time( NULL ) ); // initializing random number generator (used in Bags)
	reset_cards(3);
	draw_cards();
	cout << "'q' to quit\n '1'-'9' to get new cards\n left-click to toggle a card\n right click to remove a card\n" << endl; 
	

	SetWindowTitle("Lab 4");  // see "cs1037lib_window.h"
	SetWindowVisible(true); 

	char k;
	int x,y,btn;
	while (!WasWindowClosed())	{

		if (GetKeyboardInput(&k)) {// check keyboard
			if (k >= '1' && k <= '9') // if number pressed, set current_rect
			{
				reset_cards(k-'0');
				draw_cards();
				cout << "selected number of rectangles = " << (k-'0') << endl;
				//cout << s[20];
			}
		}

		if (GetMouseInput(&x, &y, &btn)) { // check mouse 
			if (btn == 1) left_click(Point(x,y)); // button 1 means the left button
			else if (btn == 2) right_click(Point(x,y)); // button 2 means the right button
		}
	}

	clear_cards();
	return 0;
}

void draw_cards()
{
	// Clear the window to white
	SetDrawColour(255,255,255); DrawRectangleFilled(0,0,1280,1024);

	SetDrawColour(255,0,0); 
	DrawText(CARD_WIDTH*2, CARD_HEIGHT-30, "cards in array 'c'");
	int i;
	for (i=0; i<c.getSize(); i++) if (c[i]) c[i]->drawAt(Point(CARD_WIDTH*2*(i+1),CARD_HEIGHT));
	for (i=0; i<d.getSize(); i++)           DrawText(CARD_WIDTH*2*(i+1),2*CARD_HEIGHT+2,to_Cstr("  card:  " << d[i] << " " << s[i]));
}

void reset_cards(int n)
{
	clear_cards();
	c.resize(n);
	d.resize(n);
	s.resize(n);
	int i;

	Suit suits[] = {SPADES, HEARTS, CLUBS, DIAMONDS};  // "Suit" and "Denomination" are specialized types of integers defined in "Card.h"
	Denomination denom[] = {N2,N3,N4,N5,N6,N7,N8,N9,N10,JACK,QUEEN,KING,ACE};
	for (i=0; i<c.getSize(); i++) c[i] = new ImageCard(suits[rand()%4],denom[rand()%13]); 
	for (i=0; i<d.getSize(); i++) d[i] = c[i]->toCharDenomination(); 
	for (i=0; i<s.getSize(); i++) s[i] = c[i]->toCharSuit(); 
}

void clear_cards()
{
	for (int i=0; i<c.getSize(); i++) 
		if (c[i]) { 
			delete c[i]; 
			c[i]=NULL; 
		}
}

void left_click(Point click)
{
	for (int i=0; i<c.getSize(); i++) 
	{
		if (c[i] && c[i]->pointInCard(click)) 
		{
			if (c[i]->isFaceUp()) c[i]->setFaceDown();
			else				  c[i]->setFaceUp();     
			cout << "toggle card #" << i+1 <<  endl;
			break; // skip remaining cards once we found one
		}
	}

	draw_cards();
}

void right_click(Point click) // should delete a card
{	
	for (int i=0; i<c.getSize(); i++) 
	{
		if (c[i] && c[i]->pointInCard(click)) 
		{
			delete c[i];
			c[i] = NULL;
			cout << "deleted card #" << i+1 <<  endl;
			break; // skip remaining cards  once we found one
		}
	}

	draw_cards();
}