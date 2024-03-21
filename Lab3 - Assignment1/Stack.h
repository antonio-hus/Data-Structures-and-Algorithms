#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -111111

// INCLUDES SECTION
// Libraries
#include <exception>

// CLASS STACK DEFINITION
class Stack
{
private:

    // Dynamic Array Based Structure
	int capacity, size;
    TElem* elements;

    // Resizes the DynamicArray to the appropriate size
    void resize_double();
    void resize_halve();

public:

	// Constructor
	Stack();

    // Copy Constructor
    Stack(Stack& other);
	
	// Pushes an element to the top of the Stack
	void push(TElem e);
	
	// Returns the element from the top of the Stack
	// Throws exception if the stack is empty
	TElem top() const;
	   
	// Removes and returns the element from the top of the Stack
	// Throws exception if the stack is empty
	TElem pop();
	   
	// Checks if the stack is empty
	bool isEmpty() const;
	
	// Destructor
	~Stack();
};

#include "Stack.cpp"
