
#include "cs1037assert.h"  // Our alternative to #include <cassert>  


template<class Item>
DynArray<Item> :: DynArray() 
: m_container(NULL), m_size(0){} 

template<class Item>
DynArray<Item> :: DynArray(int size) 
: m_container(NULL) {resize(size);} 

template<class Item>
DynArray<Item> :: ~DynArray() {if (m_container) delete[] m_container;}

template<class Item>
Item& DynArray<Item> :: operator[](int x) const
{
	Assert((x>=0)&&(x<=9), "List is out of bounds");
    return m_container[x];
}

template<class Item>
void DynArray<Item> :: resize(int new_size) 
{
    Assert( new_size>=0, "DynArray size is negative (in 'resize')" );
	if (m_container) delete [] m_container;
    m_size = new_size;
    if (m_size==0) m_container=NULL; 
    else m_container = new Item[m_size];
    return;
}
