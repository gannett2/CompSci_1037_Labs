#include "cs1037lib-window.h" // for basic drawing and keyboard/mouse input operations 
#include <iostream>    // for cout
#include "ImageCard.h"
#include <time.h>
#include "Bag.h"
#include "List.h"
using namespace std;

// global variables
List<ImageCard*> p;

// global function declarations
void draw_cards();
void init(int n);
void clear();
void left_click(Point click);
void right_click(Point click);
void sort();


int main()
{
	srand( (unsigned int) time( NULL ) ); // RANDOM NUMBER INITIALIZER
	init(5);
	draw_cards();
	cout << "'1'-'9' to get new cards\n left-click to toggle a card\n right click to remove a card\n click 's' to sort\n" << endl; 

	SetWindowTitle("Lab 6"); // see "cs1037lib-window.h"
	SetWindowVisible(true); 

	while (!WasWindowClosed())
	{
		char c;
		if (GetKeyboardInput(&c)) // check keyboard
		{ 
			if (c >= '1' && c <= '9') // if number pressed, set current_rect
			{
				clear();
				init(1+(c-'1'));
				draw_cards();
				cout << "selected number of rectangles = " << (1+(c-'1')) << endl;
			}
			else if (c == 's') // sorting the cards
			{
				sort();
			}
		}

		int x, y, button;
		if (GetMouseInput(&x, &y, &button)) // check mouse 
		{
			if (button == 1) left_click(Point(x,y)); // button 1 means the left button
			else if (button == 2) right_click(Point(x,y)); // button 2 means the right button
		}
	}
	clear();
	return 0;
}

void draw_cards()
{
	// Clear the window to white
	SetDrawColour(255,255,255); DrawRectangleFilled(0,0,1280,1024);

	SetDrawColour(255,0,0); 
	DrawText(CARD_WIDTH*2, CARD_HEIGHT-30, "list of (pointers to) cards");
	for (unsigned i=1; i<=p.getLength(); i++) if (p.retrieve(i)) p.retrieve(i)->drawAt(Point((CARD_WIDTH+10)*i,CARD_HEIGHT));
}

void init(int n)
{
	Bag<ImageCard *> bag(12);
	bag.add( new ImageCard(HEARTS,JACK) );
	bag.add( new ImageCard(HEARTS,QUEEN) );
	bag.add( new ImageCard(HEARTS,KING) );
	bag.add( new ImageCard(SPADES,JACK) );
	bag.add( new ImageCard(SPADES,QUEEN) );
	bag.add( new ImageCard(SPADES,KING) );
	bag.add( new ImageCard(CLUBS,JACK) );
	bag.add( new ImageCard(CLUBS,QUEEN) );
	bag.add( new ImageCard(CLUBS,KING) );
	bag.add( new ImageCard(DIAMONDS,JACK) );
	bag.add( new ImageCard(DIAMONDS,KING) );
	bag.add( new ImageCard(DIAMONDS,QUEEN) );
	for (int i=1; i<=n; i++) p.append(bag.getOne());
	while (!bag.isEmpty()) delete bag.getOne();	// deleting left-over cards 
}

void clear()
{
	while (!p.isEmpty()) {
		if (p.back()) delete p.popBack(); // removing a pointer from the list and deleteing a card
		else                 p.popBack(); // removing a NULL pointer from the lint
	}
}

void left_click(Point click)
{
	unsigned int i;
	for (i=1; i<=p.getLength(); i++) 
	{
		if (p.retrieve(i) && p.retrieve(i)->pointInCard(click)) 
		{
			if (p.retrieve(i)->isFaceUp()==false) p.retrieve(i)->setFaceUp();
			else								  p.retrieve(i)->setFaceDown();
			cout << "toggle card #" << i <<  endl;
			break; // no sense in selecting other cards once we hit the first one
		}
	}
	draw_cards();
}

void right_click(Point click) // should delete a card from 'p'
{	
	// (EXERCISE 4) ADD YOUR CODE FOR DELETING A CARD IN 'p' HERE 
	unsigned int i;
	for (i=1; i<=p.getLength(); i++) 
	{
		if (p.retrieve(i) && p.retrieve(i)->pointInCard(click)) 
		{
			delete p.retrieve(i);											
			p.replace(i,NULL);
			cout << "deleted card #" << i << endl;
		}
	}
	draw_cards();
}

void sort()  // EXERCISE 6: implement this function
{
	Bag<ImageCard*> b;
	int size = p.getLength();
	for(int i=1; i< size;i++) {
		b.add(p.popBack());
	}
	
	while(!b.isEmpty())
	{
		ImageCard *temp = b.getOne();
		for(int i=1; i<=p.getLength(); i++)
		{	
			if(*temp < *(p.retrieve(i)))
				temp = p.replace(i,temp);
		}
		p.append(temp);	
	}
		
	draw_cards();
}