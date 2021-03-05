#include "sequence2.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>//standard c++ library
#include <cassert>

using namespace std;
// CONSTRUCTOR and DESTRUCTOR
namespace main_savitch_4 {
  // Postcondition: The sequence has been initialized as an empty sequence.
// The insert/attach functions will work efficiently (without allocating
// new memory) until this capacity is reached.
  sequence::sequence(sequence::size_type initial_capacity) {
      m_data= new value_type[initial_capacity]; // new operator initializes the memory and returns the address of the newly allocated and initialized memory to the pointer variable.Parameter tells us how many items to allocate for the dynamic array.
      m_capacity = initial_capacity; //sequence initialized
      m_track=0; //setting to empty sequence
      m_current_index=0; //initialized index
    
  }
  //Precondition:The amount of memory is allocated
  //Postcondition: The sequence that is being constrcuted has been initialized
  // with the same items and capacity as source
  sequence::sequence(const sequence& source)
  {
      //The amount of memory allocated for source determines how much memory to allocate for the new dynamic array
      m_data= new value_type[source.m_capacity]; //new operator initializes the memory and returns the address of the newly allocated and initialized memory to the pointer variable.Parameter tells us how many items to allocate for the dynamic array.
      m_capacity = source.m_capacity; //same capacity as source
      m_track= source.m_track;
      m_current_index=source.m_current_index;
      copy(source.m_data, source.m_data+m_track,m_data); //copying items into new allocated array
     
  }
  sequence::~sequence(){
      delete[] m_data; //deletes array when destructor is called
  }
  // MODIFICATION MEMBER FUNCTIONS for the sequence class:
  //Postcondition: The sequence's current capacity is changed to the 
// new_capacity (but not less that the number of items already on the
// sequence). The insert/attach functions will work efficiently (without
// allocating new memory) until this new capacity is reached.
void sequence::resize(size_type new_capacity)
{
    value_type *big_array; //pointing to larger array to fit the larger capacity 
    if(new_capacity ==m_capacity)
    { return;
    } //nothing to return because the allocated memory is already the right size.

    if (new_capacity>m_track) 
    {
        big_array=new value_type[new_capacity];
        copy(m_data, m_data+m_track, big_array);
        delete [] m_data; //return the old array to heap
    m_data=big_array;
    m_capacity = new_capacity; 
        
    } //We can't allocate less than anything we are using

     else if (new_capacity < m_track){ //you can't allocate anything less
         new_capacity = m_track;
     }
    } 


//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
void sequence::start()
{
    if(size()>0)
    m_current_index=0;
}
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item on the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
void sequence::advance()
{
    if (m_current_index == m_track) //there is no current item if the item is the last item
    m_current_index=0;
    else m_current_index++; //otherwise, new item comes after
}
//     Postcondition: A new copy of entry has been inserted in the sequence before
//     the current item. If there was no current item, then the new entry has 
//     been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
void sequence::insert(const value_type& entry)
{
    //The first action of the insert function is to ensure that there is room for a new item
    if(m_track==m_capacity)
    resize(m_track+1); //increase size
    if(!is_item()) //if not the current item
    m_current_index=0; //setting infront of sequence
    
    for(int i =m_track; i> m_current_index; i--) //shifting items
      m_data[i]=m_data[i-1];
      m_data[m_current_index] = entry; //inserting entry ti new empty current_index
      m_track++;
}
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
void sequence:: attach(const value_type& entry)
{
    if(m_track==m_capacity)
    resize(m_track+1);//making it bigger
    if(!is_item()) //if no current item
   
    m_current_index= m_track-1; //entry after the current is used
    m_current_index++;
   
    for( int i = m_track; i > m_current_index; i--) //entry after the current
    m_data[i] = m_data[i-1];
    m_data[m_current_index] = entry; //inserting entry to new empty current_index
    m_track++;
   }

//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.
void sequence::remove_current( )
{
    assert(is_item()==true);
    for(int i= m_current_index;i<m_track-1;i++) //shift items
    
        m_data[i]= m_data[i+1];
        m_track--; //one less
    
    
}
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//     Postcondition: The return value is the number of items on the sequence.
sequence::size_type sequence::size( ) const
{
   return m_track; //return number of items
}
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
 bool sequence::is_item( ) const
 {
     //indicates whether there's another item for current 
     return (m_current_index < m_track) ? true : false;

 }
 //     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item on the sequence.
sequence::value_type sequence::current( ) const
{
    assert(is_item()== true);
    return m_data[m_current_index]; //inserted item is current item
}
void sequence::operator =(const sequence& source)
{
    value_type *big_array; //represents pointer to our new data
    //check for possible self-assignment
    if(this==&source) 
    return;
     //If necessary allocate a dynamic array of a different size
    big_array=new value_type[source.m_capacity];
    //use the copy function to copy data from the source
    copy(source.m_data,source.m_data+source.m_track,big_array);
    delete[] m_data;
    m_data= big_array;
    m_track=source.m_track;
    m_capacity=source.m_capacity;
    if (source.is_item()) //current
    m_current_index=source.m_current_index; 
    else m_current_index = m_track;

}


//EXTRA CREDIT
 sequence operator+(const sequence& s1, const sequence& s2)

{
    sequence answer(s1.size()+s2.size()); //the function declares a bag of sufficient size
    answer +=s1;
    answer +=s2;
    return answer;
}

sequence::value_type sequence::operator[] (sequence::size_type x) const
{
    assert(x<m_capacity);
    assert(x<m_track);
    return m_data[x];
}
void sequence::operator +=(const sequence& source)
{
    //the+= operatorstarts by ensuring that there is enough room for the new items
     if (m_track + source.m_track>m_capacity)
     resize(m_track+source.m_track);
      copy(source.m_data, source.m_data+source.m_track,m_data+m_track);
      m_track+=source.m_track;
    
     
}

}



