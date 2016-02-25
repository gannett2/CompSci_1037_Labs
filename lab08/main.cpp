#include "cs1037lib-window.h" // for basic drawing and keyboard/mouse input operations 
#include <iostream>    // for cout
#include "ImageCard.h"
#include <time.h>
#include "Bag.h"
#include "LinkedList_lab8.h"
using namespace std;

// global variables
LinkedList<ImageCard*> hand;

// global function declarations
void draw_cards();
void init(int n);
void clear();
void left_click(Point click);


int main()
{
	srand( (unsigned int) time( NULL ) ); // RANDOM NUMBER INITIALIZER
	init(12);
	draw_cards();
	cout << "'q' to quit\n 'n' to get new cards\n left-click to toggle a card\n " << endl; 
	SetWindowTitle("Lab 8"); // see "cs1037utils.h"
	SetWindowSize(1100,300);
	SetWindowVisible(true); 

	bool quit_requested = false;
	while (quit_requested == false)
	{
		char c;
		if (GetKeyboardInput(&c)) // check keyboard
		{ 
			if (c == 'q') quit_requested = true; // if asked to quit, break from loop 
			else if (c == 'n') // set new set of cards
			{
				clear();
				init(5+rand()%10);  // random number of cards between 5 and 14
				draw_cards();
				cout << "selected new cards " << endl;
			}
			// drawing cards in the list
			draw_cards();
		}

		int x, y, button;
		if (GetMouseInput(&x, &y, &button)) // check mouse 
		{
			if (button == 1) {
				left_click(Point(x,y)); // button 1 means the left button
				draw_cards();
			}
		}
	}
	clear();
	return 0;
}

void draw_cards()
{
	// Clear the window to white
	SetDrawColour(255,255,255); DrawRectangleFilled(0,0,1280,1024);


	
	LinkedList<ImageCard *>::Iterator i(hand.getHead());
	
    

	SetDrawColour(255,0,0); 
	DrawText(40,30,"Cards in linked list 'hand' :");

	// drawing the cards of the "hand" list

	// change code below for excercises 3-4 

	/*for (unsigned int k=1; k<=hand.size(); ++k) 
		if (here) 
		{
			here->value->drawAt(Point(10+k*(CARD_WIDTH+5),100));
			here = here->next;
		}*/

	for (unsigned int k=1; k<=hand.size(); ++k) 
		if (i.getValue()) 
		{
			i.getValue()->drawAt(Point(10+k*(CARD_WIDTH+5),100));
			i.operator++();
		}
}

void init(int n)
{
	int i,j;
	Suit s[] = {HEARTS,DIAMONDS,SPADES,CLUBS};
	Denomination d[] = {N2,N3,N4,N5,N6,N7,N8,N9,N10,JACK,QUEEN,KING,ACE};
	Bag<ImageCard *> tmp(52); 
	for (i=0; i<4; i++) for (j=0; j<13; j++) tmp.add(new ImageCard(s[i],d[j])); 

	for (i=1; i<=n; ++i) {
		hand.addTail(tmp.getOne());
		hand.retrieveTail()->setFaceUp();
	}
	while (!tmp.isEmpty()) delete tmp.getOne();
}

void clear()
{
	while (!hand.isEmpty()) delete hand.removeTail();
}

void left_click(Point click)
{
	LinkedList<ImageCard *>::Iterator i(hand.getHead());
	
	for (unsigned int k=1; k<=hand.size(); ++k)
	{
		if (i.getValue()->pointInCard(click)) {
			if (i.getValue()->isFaceUp()) i.getValue()->setFaceDown();
			else							  i.getValue()->setFaceUp();
			break;
		}
		i.operator++();
	}
	// excersice 4: replace the code above using "iterators", avoid calls to function "retrieve()"
	// ....

}
