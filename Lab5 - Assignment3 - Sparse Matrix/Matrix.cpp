#include "Matrix.h"
#include <exception>
using namespace std;

/// MATRIX CLASS IMPLEMENTATION
// PRIVATE METHODS

void Matrix::resize() {

    // Special case for empty list
    if(this->capacity == 0) {

        // Updating capacity
        this->capacity ++;

        // Allocating the new list
        auto* newElements = new DLLANode;
        this->nodes = newElements;

        // Updating the first empty element
        this->firstEmpty = 0;
        this->nodes[firstEmpty].prev = -1;
        this->nodes[firstEmpty].next = -1;
        return;
    }

    // Double the size and move all elements inside the new list
    int newCapacity = this->capacity*2;
    auto* newElements = new DLLANode[newCapacity];
    for(int i=0; i<this->size; ++i){
        newElements[i] = this->nodes[i];
    }

    // Initialize all newly allocated elements as empty
    this->firstEmpty = this->size;
    for (int i = this->size; i < newCapacity; ++i) {
        newElements[i].prev = i - 1;
        newElements[i].next = i + 1;
    }

    // Update the last node's next pointer to -1 to mark the end of the list
    newElements[newCapacity - 1].next = -1;

    // Redirect the old list pointer and update properties
    delete[] this->nodes;
    this->nodes = newElements;
    this->capacity = newCapacity;
}

int Matrix::allocate() {

    // Getting the first empty position
    int newPosition = this->firstEmpty;
    if(newPosition == -1) return -1;

    // Finding and setting up the next first empty spot
    this->firstEmpty = this->nodes[firstEmpty].next;
    if(this->firstEmpty != -1)
        this->nodes[firstEmpty].prev = -1;

    // "Initializing" or new element's container
    this->nodes[newPosition].prev = -1;
    this->nodes[newPosition].next = -1;
    return newPosition;
}

void Matrix::free(int position) {

    // Removing the pointer to the previous element
    this->nodes[position].prev = -1;

    // Marking current node as the first empty for overwriting
    this->nodes[position].next = this->firstEmpty;
    if(this->firstEmpty != -1)
        this->nodes[firstEmpty].prev = position;
    this->firstEmpty = position;
}

void Matrix::insertAtPosition(int position, Matrix::Triple element) {

    int newPosition = this->allocate();
    if(newPosition == -1){
        this->resize();
        newPosition = this->allocate();
    }

    this->nodes[newPosition].info = element;
    if(position == 0){

        if(this->head == -1){

            // The list was empty so the new element becomes the head ( and also the tail )
            this->head = newPosition;
            this->tail = newPosition;
        }else{

            // The list was populated already, hence we need to insert before the head
            // Setting up the pointers accordingly
            this->nodes[newPosition].next = this->head;
            this->nodes[this->head].prev = newPosition;
            this->head = newPosition;
        }

    }else{

        // Traversing the list to the desired position
        int currentNodePosition = this->head;
        int currentPosition = 0;
        while(currentNodePosition != -1 && currentNodePosition < position - 1){
            currentNodePosition = this->nodes[currentPosition].next;
            currentPosition ++;
        }

        // If the position was reached
        if(currentNodePosition != -1){

            // Setting up the pointers of the new Element
            int nextNodePosition = this->nodes[currentNodePosition].next;
            this->nodes[newPosition].next = nextNodePosition;
            this->nodes[newPosition].prev = currentNodePosition;
            this->nodes[currentNodePosition].next = newPosition;

            // Element is the last in the list, set it to be the tail
            if(nextNodePosition == -1)
                this->tail = newPosition;

            // Element is not the last so update the next nodes pointer to prev
            else{
                this->nodes[currentNodePosition].prev = newPosition;
            }
        }
    }

    this->size ++;
}

// PUBLIC METHODS
Matrix::Matrix(int nrLines, int nrCols):
capacity(0), size(0), head(-1), tail(-1), firstEmpty(-1), linesCount(nrLines), colsCount(nrCols){}


int Matrix::nrLines() const {
	return linesCount;
}


int Matrix::nrColumns() const {
	return colsCount;
}


TElem Matrix::element(int i, int j) const {

    // Checking index validity
    if((i<0 || i>linesCount) || (j<0 || j>colsCount)){
        throw exception();
    }

    // Traversing the DLL to get the element at the given position
    int currentNodePosition = this->head;
    while(currentNodePosition != -1){

        // Checking if the element matches the line and column
        if(this->nodes[currentNodePosition].info.line == i && this->nodes[currentNodePosition].info.column == j){
            return this->nodes[currentNodePosition].info.value;
        }

        // Getting the next element
        currentNodePosition = this->nodes[currentNodePosition].next;
    }

    // Element not found
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {

    // Checking index validity
    if ((i < 0 || i > linesCount) || (j < 0 || j > colsCount)) {
        throw exception();
    }

    TElem oldvalue = NULL_TELEM;

    // Finding the most suitable place for the new element, or the element itself
    int currentNodePosition = this->head;
    int newPosition = 0;
    while(currentNodePosition != -1){

        // Checking if the element matches the line and column
        if(this->nodes[currentNodePosition].info.line == i && this->nodes[currentNodePosition].info.column == j){
            break;

        // Element not found and can be inserted in this position
        }else{
            if(this->nodes[currentNodePosition].info.line > i || (this->nodes[currentNodePosition].info.line == i && this->nodes[currentNodePosition].info.line >= j))
                break;
        }

        // Getting the next element
        currentNodePosition = this->nodes[currentNodePosition].next;
    }

    // If the element already exists, update its value or remove it if the new value is 0
    if (currentNodePosition != -1 && this->nodes[currentNodePosition].info.line == i && this->nodes[currentNodePosition].info.column == j) {

        oldvalue = this->nodes[currentNodePosition].info.value;

        if (e == NULL_TELEM) {
            // Remove the existing node
            this->free(currentNodePosition);
        }

        else {
            // Update the value of the existing node
            this->nodes[currentNodePosition].info.value = e;
        }
    }

    // Otherwise, insert the new element if the new value is not 0
    else if (e != 0) {

        Triple newElement;
        newElement.line = i;
        newElement.column = j;
        newElement.value = e;

        // Inserting the new Element
        insertAtPosition(newPosition, newElement);
    }

    return oldvalue;
}
