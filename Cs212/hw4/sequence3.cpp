#include <cstdlib>
#include <cassert>
#include "node1.h"
#include "sequence3.h"

using namespace std;
namespace main_savitch_5
    {
// CONSTRUCTOR for the sequence class:
//  sequence( )
// Postcondition: The sequence has been initialized as an empty sequence.
    
sequence::sequence() //Run time analysis: This represents O(1) because everthing is constant
{
    //Everthing is being initialized
    m_head=NULL;
    m_tail=NULL;
    m_current_n=NULL;
    m_prev_n=NULL;
    m_total_n=0;
}
//Copy constuctor
sequence::sequence(const sequence& source) // Run time analysis: O(n) becuase this is linear time as it copies nodes one at a time
{
    list_copy(source.m_current_n, m_current_n, m_prev_n);
    list_copy(source.m_head, m_head, m_tail);
    m_total_n=source.size();
}
//Destructor
sequence::~sequence() //Run time analysis: O(1) becuase of constant time
{
    list_clear(m_head); //the list_clear function comes from node1.cpp
    m_prev_n= m_current_n= NULL;
    m_total_n=0;
}


         //Postcondition: The first item on the sequence becomes the current item
//(but if the sequence is empty, then there is no current item).
    void sequence::start() // Run time analysis: O(1) becuase of constant time
    {
    
         m_prev_n=NULL; // this represents if the sequence is empty there's no current item
        m_current_n= m_head; //the first item head is beco,ing the current item
       
    }

//Precondition: is_item returns true.
//Postcondition: If the current item was already the last item on the
//sequence, then there is no longer any current item. Otherwise, the new
//current item is the item immediately after the original current item.
    void sequence::advance() //Run time analysis: O(1) becuase of constant time
    {
        assert(is_item()); // checking if is_item is true so that current item can move to satisfy postcondition
        m_prev_n=m_current_n; //making current node be the previous item
        m_current_n=m_current_n -> link(); //moving the current item
    }
//Postcondition: A new copy of entry has been inserted in the sequence before
//the current item. If there was no current item, then the new entry has 
//been inserted at the front of the sequence. In either case, the newly
//inserted item is now the current item of the sequence.
    void sequence::insert(const value_type& entry) //Run time analysis: O(1) becuase we are dealing with constant time
    {
          if(m_total_n==0)
          {
              m_prev_n=NULL; // there is no previous item
              list_head_insert(m_head,entry); //inserting 
              m_current_n=m_head; //new entry has been inserted at the front of the sequence
              m_tail=m_head;

          }
          else if (is_item() == false|| m_current_n == m_head)
          {
              list_head_insert(m_head,entry);
              m_prev_n=NULL;
              m_current_n=m_head; //new entry has been inserted at the front of the sequence
          }
          else
          {
              list_insert(m_prev_n,entry);
              m_current_n=m_prev_n -> link();
          }
          ++m_total_n; //keeps moving to check
          // all of these functions work together to insert a new entry at the front of the sequence and makes that the current
          // and if there isn't a current, the new entry still gets placed at the front and becomes the new current.
    }

 //    Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry) //Run time analysis: O(1) becuase of constant time
    {
        //we will be adding an entry after the current item. However, if the current item is nonexistent then the item is attached at the end of the list
          if(m_total_n==0)
          {
              m_prev_n=m_head; 
              list_head_insert(m_head,entry); //insertion
              m_current_n=m_head; 
              m_tail= m_head;  
          }
          else if(is_item()==0 || m_current_n == m_tail)
          {
              m_prev_n=m_tail;
               list_insert(m_tail,entry); //insertion
             m_tail =m_tail -> link();
             m_current_n=m_tail;
          }
          else
          {
             m_prev_n= m_current_n;
             list_insert(m_current_n,entry); //insertion
             m_current_n=m_current_n-> link();
             
          }
          ++m_total_n;
    }

 //    Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.
          void sequence::remove_current() //Run time analysis: O(1) due to constant time
          {
              //We will be removing the current item and it will become the new current item.
                assert(is_item()); //is_item() is true
                if(m_total_n ==1)
                {
                    list_head_remove(m_head);
                    m_prev_n=m_current_n=m_tail=NULL;
                }
                else if (m_current_n == m_head)
                {
                    m_prev_n= NULL;
                    list_head_remove(m_head);
                    m_current_n= m_head;
                    
                }
                else if(m_current_n==m_tail)
                {
                    m_tail=m_prev_n;
                    list_remove(m_tail);
                    m_current_n=NULL;
                }
                else
                {
                    m_current_n=m_current_n -> link();
                    list_remove(m_prev_n);
                }
                --m_total_n;
                
          }


        //Postcondition: The return value is the number of items on the sequence.
           sequence::size_type sequence::size() const //O(1)
           {
                return m_total_n; //returns number of items on the sequence
           }
           //     Precondition: is_item() returns true.
//     Postcondition: The item returned is the current item on the sequence.
           sequence::value_type sequence::current()const //O(1)
           {
               assert(is_item()); //precondition
               return m_current_n -> data();
           }
           //    Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
     bool sequence::is_item() const //Run time analysis O(1)
     {
         //is_item() tells us there is an item in the current node
         return m_current_n != NULL;
     }

  
  
 // DYNAMIC MEMORY USAGE by the sequence:
//   If there is insufficient dynamic memory, then the following functions call
//   new_handler: The constructors, insert, attach, and the
//   assignment operator.

    void sequence::operator=(const sequence& source) // Run time analysis: O(n) because this is linear tim
    {
        //the operator= will make a list for the copy and orginal
        if (this ==&source) 
        {
            return;
        }
        
            list_clear(m_head);
            list_copy(source.m_head, m_head, m_tail);
            m_total_n= source.m_total_n;

            start();
            for(node* i = source.m_head; i !=NULL && i!=source.m_current_n; i= i-> link())
            {
                advance();
            }
        
        
    }
    }