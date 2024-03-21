/// HEADER FILE & NAMESPACE
#include "Stack.h"
using namespace std;

/// CLASS PRIVATE METHODS IMPLEMENTATION
void Stack::resize_double() {
    // Allocating size for the new elements
    int new_capacity = this->capacity *2;
    auto* new_elements = new TElem[new_capacity];

    // Migrating all elements to the new list
    for(int i=0; i < this->size; ++i)
        new_elements[i] = this->elements[i];

    // Free the old memory location
    delete[] this->elements;

    // Relocate pointer to new memory address
    this->elements = new_elements;
    this->capacity = new_capacity;
}
// BC=WC=TC: Theta(stackSize) - We have to relocate all elements of the Stack

void Stack::resize_halve() {
    // Allocating smaller size for the old elements
    int new_capacity = this->capacity / 2;
    auto* new_elements = new TElem[new_capacity];

    // Migrating all elements to the new list
    for (int i = 0; i < this->size; ++i)
        new_elements[i] = this->elements[i];

    // Free the old memory location
    delete[] this->elements;

    // Relocate pointer to new memory address
    this->elements = new_elements;
    this->capacity = new_capacity;
}
// BC=WC=TC: Theta(stackSize) - We have to relocate all elements no matter what

/// CLASS PUBLIC METHODS IMPLEMENTATION
Stack::Stack(){

    // Initially the stack is empty
    // Initial capacity is 1
    this->size = 0;
    this->capacity = 1;

    // Dynamically Allocating space for future Elements
	this->elements = new TElem[capacity];
}
// BC=WC=TC: Theta(1)

Stack::Stack(Stack &other) {

    // Initialize the capacity and size to the other's Stacks statistics
    this->capacity = other.capacity;
    this->size = other.size;

    // Make a deepcopy of the elements from the other Stack
    this->elements = new TElem[this->capacity];
    for(int i=0; i<this->size; ++i)
        this->elements[i] = other.elements[i];
}
// BC=WC=TC: Theta(stackSize) - We have to relocate all elements from the other Stack

void Stack::push(TElem e) {

    // If the Stack is full, double its size
    if(this->size == this->capacity)
        resize_double();

    // Add the new element on top of the Stack
	this->elements[this->size++] = e;
}
// BC=WC=TC: Theta(1) - Amortized Complexity
// We will rarely need to increase the capacity, so we analyze over a sequence of operations (n)
// The resize operation is performed only when size becomes a power of 2.
// Thus, we will have n constant time operations plus a cost of (1+2+..2^log2(n) =2n ) for resizing
// Dividing by our n operations we get a constant time for the average operation

TElem Stack::top() const {

    // If the Stack is empty, throw an exception
    if(this->isEmpty())
        throw exception();

    // Returns the element on top of the Stack
	return this->elements[this->size-1];
}
// BC=WC=TC: Theta(1) - Accessing Array Element is done in Constant Time

TElem Stack::pop() {

    // If the Stack is empty, throw an exception
    if(this->isEmpty())
        throw exception();

    // If the Stack is less than halve empty, halve its size
    if (this->size <= this->capacity / 2) {
        resize_halve();
    }

    // Decreasing the size of the Stack
    this->size--;

    // Returns the element on top of the Stack
	return this->elements[this->size];
}
// BC=WC=TC: Theta(1) - Amortized Complexity
// Similar to analysis of 'push' operation.

bool Stack::isEmpty() const {

    // Stack is empty if its size is 0
	return this->size == 0;
}
// BC=WC=TC: Theta(1) - Accessing Properties is done in Constant Time

Stack::~Stack() {

    // Free dynamically allocated elements
	delete[] this->elements;
}
// BC=WC=TC: Theta(1) - Memory Freeing is done in Constant Time

