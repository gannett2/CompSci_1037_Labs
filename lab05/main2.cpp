#include <iostream>
using namespace std;


int funcC(int k)
{
	int a = (k*2)+4;
	int b = a - k*2;
	return b;
}
int funcB(int j)
{
	int a = funcC(j) + j;
	int b = funcC(a);
	return b;
}
int funcA(int i)
{
	int a = funcB(i);
	int b = funcC(a);
	return b;
}


int main()
{
	int a = 5;
	int b,c;

	b = funcB(a);
	c = funcA(b);

	a = funcC(a);

	cout<< a << " " << b << " " << c << endl;

	cin >> b;

	return 0;
}