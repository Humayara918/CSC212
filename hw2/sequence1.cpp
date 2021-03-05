#include "sequence1.h"
#include <iostream>
using namespace std;

//typedef int value_type; //data type in the sequence
//typedef std::size_t size_type; //std::size_t can store the maximum size of a theoretically possible object
//size_type is the data type of any variable that keeps track of how many items are in a sequence

namespace main_savitch_3 {
    const sequence::size_type sequence::CAPACITY;
    //Postcondition: The sequence has been initialized as an empty sequence.
     sequence::sequence(){
           m_used=0; //since we are initializing as an empty sequence there will be "zero" data being used

           m_current_index= m_capacity -1; // Index starts with zero so we -1
           m_size=0;
           m_current=NULL;
     }
     //Postcondition: The first item on the sequence becomes the current item (but if the sequence is empty, then there is no current item)
     void sequence::start() {
        if (m_size != 0) {
            m_current= m_data[0]; // first value in array
            m_current_index = 0;
        }
        else {
            m_current = NULL; // no current item
        }
     }
     //Precondition: is_item returns true
     //Postcondition: If the current item was already the last item in the sequence, then there is no longer any current item. Otherwise, the new current item is the item immediately after the orginal current item.
     void sequence::advance(){
         if (is_item()) {
            if (m_current == m_data[m_size - 1]) {
                m_current = NULL;//no current
            }
            else {
                m_current_index++;
                m_current = m_data[m_current_index]; //new current item is the item after the orginal current item
        
            }
         }
     }
     //Precondition: size() <CAPACITY
     //Postcondition: A new copy of entry has been inserted in the sequence
    // before the current item. If there was no current item, then the new entry 
   // has been inserted at the front of the sequence. In either case, the newly
   //inserted item is now the current item of the sequence.
      void sequence::insert(const value_type& entry){
                if (size()<CAPACITY){
                    if (m_current != NULL){
                        int index = m_size; //shifitng elements to the right, 
                        int ref = m_current_index - 1; 
                        while(index > ref) { //iterates sequence to shift elements to the right
                            if (index != m_current_index) { //shift elemnts to the right
                                m_data[index] = m_data[index - 1]; //shfiting elements for entry to be placed
                                /*
                                    [1, 2, 3] = m_data
                                    2 = m_current
                                    1 = m_current_index
                                    4 = entry
                                    index = 3
                                    ref = 0
                                */
                            }
                            else {
                                m_data[index]= entry; //inserting new element
                            }
                            index--; //since we are moving back
                        }
                    } 
                    else{
                        int index = m_size;
                        while(index > -1) {
                            if (index != 0) {
                                m_data[index] = m_data[index - 1]; //shfiting elements for entry to be placed
                                
                            }
                            else {
                                m_data[index]= entry; //inserting new element 
                                m_current_index = 0;
                            }
                            index--;
                        }
                    } 
                    m_current= entry; //inserted into sequence
                    m_size++; //extra element was added that's why m_size++;
                }
    }
     //Precondition: size( ) < CAPACITY.
    //Postcondition: A new copy of entry has been inserted in the sequence after
    //the current item. If there was no current item, then the new entry has 
    //been attached to the end of the sequence. In either case, the newly
    //inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry) {
        if (m_current != NULL){
            if (m_current_index == m_size - 1) {
                m_data[m_current_index +1]= entry; //attaching new element towards the end of sequence
                m_current_index++;
            }
            else {
                int index = m_size, ref = m_current_index;
                while(index > m_current_index) {
                    if(index == m_current_index + 1) {        
                        m_data[m_current_index +1]= entry; //shift elements to right 
                        m_current_index++;
                    }
                    else {
                        m_data[index] = m_data[index - 1]; //inserting new element to the right of the current element 
                    }
                    index--;
                }
            }
        }
        else{
            m_data[m_size] = entry;
            m_current_index = m_size; 
        }
        m_current= entry;
        m_size++;
    }
                
           // Precondition: is_item returns true.
        //Postcondition: The current item has been removed from the sequence, and the
       //item after this (if there is one) is now the new current item.
                void sequence::remove_current(){
                        if(is_item()){
                            if(m_current_index + 1 != m_size)
                                m_current = m_data[m_current_index + 1]; //after removal, m_current becomes next element to the right
                            else {
                                m_current = NULL;
                            }
                             for (sequence::size_type i=m_current_index; i<m_size; i++) { //shift elements to the left
                                 m_data[i]=m_data[i+1]; //places new index value;
                             }
                             m_size--;
                        }
                }
                // CONSTANT MEMBER FUNCTIONS for the sequence class:
                //Postcondition: The return value is the number of items in the sequence
                sequence::size_type sequence::size() const {
                    return m_size;
                }
               //Postcondition: A true return value indicates that there is a valid
              //"current" item that may be retrieved by activating the current
             //member function (listed below). A false return value indicates that
            //there is no valid current item.
                bool sequence::is_item() const{
                    return m_current != NULL;
                }
                //Precondition: is_item( ) returns true.
               // Postcondition: The item returned is the current item in the sequence.
                sequence::value_type sequence::current() const{
                    return m_data[m_current_index];
                }
         }
     

