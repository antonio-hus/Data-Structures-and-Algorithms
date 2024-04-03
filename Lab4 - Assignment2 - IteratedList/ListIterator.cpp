// HEADER FILES
#include "ListIterator.h"
#include "IteratedList.h"

/// PRIVATE CLASS METHODS IMPLEMENTATION
ListIterator::ListIterator(const IteratedList& list) : list(list), currentNodePtr(list.head){}
// BC=WC=TC: Theta(1) - Initializing class properties is done in constant time

bool ListIterator::operator!=(ListIterator other) {
    return this->currentNodePtr != other.currentNodePtr;
}
// BC=WC=TC: Theta(1) - Accessing class properties is done in constant time

/// PUBLIC CLASS METHODS IMPLEMENTATION
// CLASS ITERATOR INDEX MANIPULATION METHODS
void ListIterator::first() {
    this->currentNodePtr = this->list.head;
}
// BC=WC=TC: Theta(1) - Updating class properties is done in constant time

void ListIterator::next() {

    // Throwing an exception for an invalid iterator
	if(!this->valid())
        throw std::exception();

    // Getting the next node in the Linked List
    this->currentNodePtr = this->currentNodePtr->next;
}
// BC=WC=TC: Theta(1) - Updating class properties is done in constant time

// CLASS VALIDATOR METHODS
bool ListIterator::valid() const {

    // The iterator becomes invalid when the current pointer is null - Finished traversing all elements
	return this->currentNodePtr != nullptr;
}
// BC=WC=TC: Theta(1) - Accessing class properties is done in constant time

// CLASS GETTER METHODS
TElem ListIterator::getCurrent() const {

    // Throwing an exception if the current index is invalid
    if(!this->valid())
        throw std::exception();

    // Returning the data of the current Node
    return this->currentNodePtr->data;
}
// BC=WC=TC: Theta(1) - Accessing class properties is done in constant time


