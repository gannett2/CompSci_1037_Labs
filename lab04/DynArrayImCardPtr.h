////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS FILE DEFINES CLASS "DynArrayImCardPtr" REPRESENTING ARRAY WITH ELEMENTS OF TYPE "ImageCard*". //                                                                       //  
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ImageCard.h"


class DynArrayImCardPtr {
public:
        // constructing/copying of 1d arrays 
    DynArrayImCardPtr();    // creates an empty array of zero width 
    DynArrayImCardPtr(int size); // initialized array of given size (values are not initialized)
    ~DynArrayImCardPtr(); // destructor

        // basic quiry functions
    int getSize() const {return m_size;} 
	                                       
        // operators allowing access of items in "DynArray a" using syntax` "a[x]"
    ImageCard*& operator[](int x) const;  // PRECONDITION: index "x" must be in-range
 
        // functions for resizing/resetting arrays
    void resize(int new_size); // creates new container (but values are not initialized)
 
private:
    ImageCard** m_container;
    int m_size;
};