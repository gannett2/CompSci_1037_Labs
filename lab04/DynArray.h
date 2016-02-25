/////////////////////////////////////////////////////////////////////////////////////////////
// THIS FILE DEFINES CLASS "DynArrayChar" REPRESENTING ARRAY WITH ELEMENTS OF TYPE "char". //                                                                       //  
/////////////////////////////////////////////////////////////////////////////////////////////

template <class Item>
class DynArray {
public:
        // constructing/copying of 1d arrays 
    DynArray();    // creates an empty array of zero width 
    DynArray(int size); // initialized array of given size (values are not initialized)
    ~DynArray(); // destructor

        // basic quiry functions
    int getSize() const {return m_size;} 
	                                       
        // operators allowing access of items in "DynArray a" using syntax` "a[x]"
    Item& operator[](int x) const;  // PRECONDITION: index "x" must be in-range
 
        // functions for resizing/resetting arrays
    void resize(int new_size); // creates new container (but values are not initialized)
 
private:
    Item* m_container;
    int m_size;
};
#include "DynArrayImpl.h"
