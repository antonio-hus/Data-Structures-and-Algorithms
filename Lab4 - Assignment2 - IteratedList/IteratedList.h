// This module defines the Iterated List
/// DEFINITIONS SECTION
#pragma once
#define NULL_TELEM -11111;

typedef int TElem;
class ListIterator;

/// INCLUDES SECTION
// Libraries
#include <exception>
#include <iostream>

/// HELPER CLASSES DEFINITION
class SLLNode {
public:
    TElem data;
    SLLNode* next;
};

/// CLASS DEFINITION
class IteratedList {
private:

    // CLASS REPRESENTATION
    // Singly-Linked List Based Representation
    SLLNode* head;

	// CLASS ITERATOR
	friend class ListIterator;
public:

    // CONSTRUCTOR & DESTRUCTORS
	// Constructor
	IteratedList();
    // Destructor
    ~IteratedList();

    // CLASS PROPERTIES
	// Returns the number of elements from the list
	int size() const;
	// Verifies if the list is empty
	bool isEmpty() const;

    // CLASS GETTERS & SETTERS
	// Returns the first position from the list
	ListIterator first() const;
	// Returns the element from the given position
	// Throws an exception if the position is not valid
	TElem getElement(ListIterator pos) const;
	// Changes the element from the current position to the given one.
	// Returns the old value from the position
	// Throws exception if the position is not valid
	TElem setElement(ListIterator pos, TElem e);

    // CONTAINER ELEMENT ADDITION METHODS
	// Adds a new element to the end of the list
	void addToEnd(TElem e);
	// Adds a new element to the beginning of the list
	void addToBeginning(TElem e);
	// Adds a new element after the current element from the iterator
	// After addition, pos points to the newly added element
	// Throws an exception if pos is not valid
	void addToPosition(ListIterator& pos, TElem e);

    // CONTAINER ELEMENT REMOVAL METHODS
	// Removes the element from position pos
	// Returns the removed element
	// After removal pos is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed
	// Throws an exception if pos is not valid
	TElem remove(ListIterator& pos);

    // CONTAINER ELEMENT QUERY METHODS
	// Searches for the first occurrence of an element
	// Returns an iterator that points to the element, if it appears in the list, or an invalid iterator if the element is not in the list
	ListIterator search(TElem e) const;

};
