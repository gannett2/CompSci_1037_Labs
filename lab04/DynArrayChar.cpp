#include "DynArrayChar.h"
#include "cs1037assert.h"  // Our alternative to #include <cassert>  


DynArrayChar :: DynArrayChar() 
: m_container(NULL), m_size(0){} 

DynArrayChar :: DynArrayChar(int size) 
: m_container(NULL) {resize(size);} 

DynArrayChar :: ~DynArrayChar() {if (m_container) delete[] m_container;}

char& DynArrayChar :: operator[](int x) const
{
	Assert((x>=0)&&(x<=9), "List is out of bounds");
    return m_container[x];
}

void DynArrayChar :: resize(int new_size) 
{
    Assert( new_size>=0, "DynArray size is negative (in 'resize')" );
	if (m_container) delete [] m_container;
    m_size = new_size;
    if (m_size==0) m_container=NULL; 
    else m_container = new char[m_size];
    return;
}
