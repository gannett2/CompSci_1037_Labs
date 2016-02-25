#include <iostream>
using namespace std;
 
// iterative method for computing power function b^e
int power_itr(int b, unsigned e)
{
	int r=1;
	for (unsigned i=0; i<e; i++)  // expanding out equation  b^e  as   b*b*b*b*...*b   (e times)
		r*=b;                       
	return r;
}

// recursive method for computing power function b^e
int power_rcr(int b, unsigned e)
{
	if (e>0) return b*power_rcr(b, e-1); // expanding out equation   b^e   as   b*b^(e-1)
	else     return 1;     // b^0 = 1; (stops a sequence of recursive calls once e=0)
}
 
void main()
{
     
      cout<<power_itr(2, 10) << endl;
      cout<<power_rcr(2, 10) << endl;
      cin.ignore();
 
}