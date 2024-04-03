// This module defines the Queue Class
#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

// INCLUDES SECTION BELOW
// Libraries
#include <exception>
#include <iostream>

// CLASS DEFINITION BELOW
class Queue{
private:
    // CLASS STRUCTURE
    // Dynamic Array Based Structure
    int capacity, size;
    TElem* elements;

    // Indexes for Rear and Front of the Circular Array
    int frontIndex, rearIndex;

    // HELPER METHODS
    // Resize operation, enlarges and shrinks the capacity of the array when needed
    // If the array is full => double its capacity
    // If the array is half empty => half its capacity
    void resize();

    // Checks if the circular array is full
    // Returns true if the array's rear index will meet the front index in the next push operation
    // False otherwise
    bool isFull() const;

public:
    // Class Constructor
	Queue();

	// Pushes an element to the end of the queue
	void push(TElem e);

	// Returns the element from the front of the queue
	// Throws exception if the queue is empty
	TElem top() const;

	// Removes and returns the element from the front of the queue
	// Throws exception if the queue is empty
	TElem pop();

	// Checks if the queue is empty
	bool isEmpty() const;

	// Destructor
	~Queue();

    // EXTRA OPERATION
    // returns the middle element of the queue (if the queue has an even number of elements, return either of the two "middle elements")
    // throws an exception if the queue is empty
    TElem getMiddle() const;
};

#include "Queue.cpp"
