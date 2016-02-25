/////////////////////////////////////////////////////////////////////////////////////////////
// THIS FILE DEFINES CLASS "DynArrayChar" REPRESENTING ARRAY WITH ELEMENTS OF TYPE "char". //                                                                       //  
/////////////////////////////////////////////////////////////////////////////////////////////


class DynArrayChar {
public:
        // constructing/copying of 1d arrays 
    DynArrayChar();    // creates an empty array of zero width 
    DynArrayChar(int size); // initialized array of given size (values are not initialized)
    ~DynArrayChar(); // destructor

        // basic quiry functions
    int getSize() const {return m_size;} 
	                                       
        // operators allowing access of items in "DynArray a" using syntax` "a[x]"
    char& operator[](int x) const;  // PRECONDITION: index "x" must be in-range
 
        // functions for resizing/resetting arrays
    void resize(int new_size); // creates new container (but values are not initialized)
 
private:
    char* m_container;
    int m_size;
};