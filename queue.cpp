/* 
queue.cpp

Author: Andrew Valle

Short description of this file: This file contains the
definitions of the constructor, destructor, and functions
of the Queue class.
*/

#include "queue.h"

// constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// this is complete, you don't need to change it.
Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;   
   tail = 0;    
}

// destructor. releases resources. C++ will call it automatically.
// this is complete, you don't need to change it.
Queue::~Queue() {
   delete[] contents;
}

// insert a new Location at the end/back of our list   
void Queue::add_to_back(Location loc) {
   // FILL THIS IN
     
    contents[tail].row = loc.row;
    contents[tail].col = loc.col;
    tail++;
  
}

// return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {
   // FILL THIS IN
   head++;
   return contents[head-1];
}

// is this Queue empty? (did we extract everything added?)
// this is complete, you don't need to change it.
bool Queue::is_empty() {
   return head == tail;
}

