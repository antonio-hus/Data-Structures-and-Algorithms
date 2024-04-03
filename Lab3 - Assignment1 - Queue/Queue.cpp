// This module implements the Queue Class Methods
/// HEADER FILE & NAMESPACES
#include "Queue.h"
using namespace std;

/// PRIVATE CLASS METHODS IMPLEMENTATION
void Queue::resize(){

    // Doubling the capacity
    int new_capacity = 2 * this->capacity;
    auto* new_elements = new TElem[new_capacity];

    // Indexes for traversing the new array / old array
    int i=0;
    int j=frontIndex;

    // Do until we reach the point we began from ( Circular Array )
    do{
        // Copying the elements
        new_elements[i] = this->elements[j];

        // Getting the next indexes
        j = (j+1) % this->capacity;
        i++;
    }while(j!=frontIndex);

    // Assigning the elements pointer to the new memory area
    delete[] this->elements;
    this->elements = new_elements;

    // Assigning the new indexes
    this->frontIndex = 0;
    this->rearIndex = i - 1;

    // Fixing the new capacity
    this->capacity = new_capacity;
}
// BC=WC=TC: Theta(queueSize) - We have to copy each element of the queue inside the new memory location

bool Queue::isFull() const{
    return (this->rearIndex+1)%this->capacity == this->frontIndex;
}
// BC=WC=TC: Theta(1) - Accessing class parameters is done in constant time

/// PUBLIC CLASS METHODS IMPLEMENTATION
Queue::Queue() {
    // Dynamic Array Based Structure
	this->capacity = 1;
    this->size = 0;
    this->elements = new TElem[this->capacity];

    // Indexes for Rear and Front of the Circular Array
    this->frontIndex=0;
    this->rearIndex=0;
}
// BC=WC=TC: Theta(1) - Initializing parameters and allocating memory is done in constant time


void Queue::push(TElem elem) {

    // If the array is full, resize correspondingly
	if(this->isFull()) this->resize();

    // Adding to the rear the new Element and increasing the size
    this->elements[rearIndex] = elem;
    this->size ++;

    // Updating the new rear index
    this->rearIndex = (this->rearIndex + 1) % this->capacity;
}
// BC=WC=TC: Theta(1) - Amortized Complexity
// We will rarely need to increase the capacity, so we analyze over a sequence of operations (n)
// The resize operation is performed only when size becomes a power of 2.
// Thus, we will have n constant time operations plus a cost of (1+2+..2^log2(n) =2n ) for resizing
// Dividing by our n operations we get a constant time for the average operation


TElem Queue::top() const {

    // Throws an exception for getting the top of the empty queue
	if(this->isEmpty())
        throw exception();

    // Returning the top element
	return this->elements[this->frontIndex];
}
// BC=WC=TC: Theta(1) - Accessing array elements is done in constant time

TElem Queue::pop() {

    // Throws an exception for popping the empty queue
	if(this->isEmpty())
        throw exception();

    // Removing it from the Queue and decreasing its size
    this->frontIndex = (this->frontIndex + 1) % this->capacity;
    this->size --;

    // Returning the previous top element
	return this->elements[(this->frontIndex - 1) % this->capacity];
}
// BC=WC=TC: Theta(1) - Amortized Complexity - Similar analysis to the case of 'push' operation

bool Queue::isEmpty() const {
	return this->size == 0;
}
// BC=WC=TC: Theta(1) - Accessing class parameters is done in constant time

Queue::~Queue() {
	delete[] this->elements;
}
// BC=WC=TC: Theta(1) - Freeing memory is done in constant time

// EXTRA OPERATION
TElem Queue::getMiddle() const {

    // Throws an exception for popping the empty queue
    if(this->isEmpty())
        throw exception();

    // Getting the middleIndex
    int middleIndex = 0;
    if(this->frontIndex > this->rearIndex)
        middleIndex = (this->frontIndex + this->rearIndex % this->capacity) / 2;
    else middleIndex = (this->frontIndex + this->rearIndex) / 2;
    return this->elements[middleIndex];
}
// BC=WC=TC: Theta(1) - Accessing class properties is done in constant time