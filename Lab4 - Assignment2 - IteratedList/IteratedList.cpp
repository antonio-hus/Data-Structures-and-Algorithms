// HEADER FILES
#include "ListIterator.h"
#include "IteratedList.h"

/// CLASS PUBLIC METHOD IMPLEMENTATION
// CLASS CONSTRUCTORS & DESTRUCTORS
IteratedList::IteratedList(): head(nullptr) {}
// BC=WC=TC: Theta(1) - Initializing class properties is done in constant time

IteratedList::~IteratedList() {

    // Freeing the List
    while(this->head != nullptr){

        // Temporary Pointer
        SLLNode* pointer = this->head->next;

        // Free the node
        delete[] this->head;

        // Get the next Node
        this->head = pointer;
    }
}
// BC=WC=TC: Theta(listSize) - Traversing the entire list

// CLASS PROPERTIES
int IteratedList::size() const {

    // Initially counter is zero
	int counter = 0;

    // Traversing the SLL to get the number of nodes
    SLLNode* pointer = this->head;
    while(pointer != nullptr){
        pointer = pointer->next;
        counter ++;
    }

    // Returning the node count
    return counter;
}
// BC=WC=TC: Theta(listSize) - Traversing the entire list to get its size

bool IteratedList::isEmpty() const {

    // Singly Linked List is empty if the head is the null pointer
	return this->head == nullptr;
}
// BC=WC=TC: Theta(1) - Accessing class properties is done in constant time

// CLASS GETTERS & SETTERS
ListIterator IteratedList::first() const {

    // First node of the list is the head node
	return ListIterator(*this);
}
// BC=WC=TC: Theta(1) - Accessing class properties is done in constant time

TElem IteratedList::getElement(ListIterator pos) const{

    // Throwing an exception for an invalid position
    if(!pos.valid()) throw std::exception();

    // Getting the current on the specified position
    ListIterator iterator = this->first();
    while(iterator != pos)
        iterator.next();

    // Returning the Node's data
    return iterator.getCurrent();
}
// BC=WC=TC: Theta(pos) - Traversing the list up to the specified position

TElem IteratedList::setElement(ListIterator pos, TElem e) {

    // Throwing an exception for an invalid position
    if(!pos.valid()) throw std::exception();

    // Getting the current on the specified position
    ListIterator iterator = this->first();
    while(iterator != pos)
        iterator.next();

    // Updating the Node's new data
    TElem oldData = iterator.currentNodePtr->data;
    iterator.currentNodePtr->data = e;

    // Returning the Node's old data
    return oldData;
}
// BC=WC=TC: Theta(pos) - Traversing the list up to the specified position

// CONTAINER ELEMENT ADDITION METHODS
void IteratedList::addToEnd(TElem e) {

    // If the list is empty, add to beginning
    if(this->isEmpty()){
        this->addToBeginning(e);
        return;
    }

    // Getting to the end of the list
    ListIterator iterator = this->first();
    while(iterator.currentNodePtr->next != nullptr)
        iterator.next();

    // Allocating and initializing a new node
    auto* newNode = new SLLNode;
    newNode->data = e;
    newNode->next = nullptr;

    // Updating the previous Node's next pointer
    iterator.currentNodePtr->next = newNode;
}
// BC=WC=TC: Theta(listSize) - Traversing the list up to the listSize

void IteratedList::addToBeginning(TElem e) {

    // Allocating and initializing a new node
    auto* newNode = new SLLNode;
    newNode->data = e;
    newNode->next = this->head;

    // Updating the head pointer
    this->head = newNode;
}
// BC=WC=TC: Theta(1) - Allocating memory & Accessing class properties is done in constant times

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    // Throwing an exception for an invalid position
    if(!pos.valid()) throw std::exception();

    // Getting the current pointer on the Node of the specified position
    ListIterator iterator = this->first();
    while(iterator != pos)
        iterator.next();

    auto* newNode = new SLLNode;
    newNode->data = e;
    newNode->next = pos.currentNodePtr->next;

    // Updating the previous Node's next pointer
    pos.currentNodePtr->next = newNode;
    pos.currentNodePtr = pos.currentNodePtr->next;

}
// BC=WC=TC: Theta(pos) - Traversing the list up to the specified position

// CONTAINER ELEMENT REMOVAL METHODS
TElem IteratedList::remove(ListIterator& pos) {
    // Throwing an exception for an invalid position
    if(!pos.valid()) throw std::exception();

    // If removing the first node
    if (pos.currentNodePtr == this->head) {
        this->head = this->head->next;
        TElem data = pos.currentNodePtr->data;
        delete[] pos.currentNodePtr;
        pos.currentNodePtr = this->head;
        return data;
    }

    // Getting the current pointer on the Node of the specified position
    ListIterator iterator = this->first();
    while(iterator.currentNodePtr->next != pos.currentNodePtr) {
        iterator.next();
    }

    // Removing the node on pos ( redirecting Node on pos-1 to Node on pos+1 )
    iterator.currentNodePtr->next = pos.currentNodePtr->next;

    // Getting removed Node's data
    TElem data = pos.currentNodePtr->data;

    // Freeing the removed Node
    delete[] pos.currentNodePtr;

    // Redirecting pos to the next Node if possible ( otherwise invalid iterator = nullptr )
    if(iterator.currentNodePtr->next != nullptr)
        pos.currentNodePtr = iterator.currentNodePtr->next;
    else pos.currentNodePtr = nullptr;

    // Returning the removed Node's data
    return data;
}
// BC=WC=TC: Theta(pos) - Traversing the list up to the specified position

// CONTAINER ELEMENT QUERY METHODS
ListIterator IteratedList::search(TElem e) const {

    // Initializing a new iterator
    ListIterator iterator = this->first();

    // Finding the first occurrence of the element
    while (iterator.valid() && iterator.currentNodePtr->data != e) {
        iterator.next();
    }

    // Element not found - Return an invalid iterator
    if (!iterator.valid()) {

        iterator.currentNodePtr = nullptr;
        return iterator;

    // Element found - Return the iterator at that location
    }else{

        return iterator;
    }
}
// BC = Theta(1) - The element is found in the head
// WC = Theta(listSize) - The element is found in the end of the list or not found at all
// TC = O(listSize)
