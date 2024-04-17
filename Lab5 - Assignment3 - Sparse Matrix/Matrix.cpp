#include "Matrix.h"
#include <iostream>
#include <exception>
using namespace std;

/// MATRIX CLASS IMPLEMENTATION
// PRIVATE METHODS
void Matrix::resize() {

    // Special case, list has 0 capacity
    int newCapacity;
    if(this->capacity == 0){
        newCapacity = 1;
    }else{
        newCapacity = this->capacity * 2;
    }

    // Doubling Capacity of the List
    auto* newElements = new DLLANode[newCapacity];

    // Copying the old elements
    for(int i=0; i<this->size; ++i){
        newElements[i] = this->nodes[i];
    }

    // Initializing the new elements
    for(int i=this->size; i<newCapacity; ++i){
        newElements[i].prev = i-1;
        newElements[i].next = i+1;
    }
    newElements[this->size].prev = -1;
    newElements[newCapacity-1].next = -1;

    // List was full, hence the first empty is the node at size
    this->firstEmpty = this->size;

    // Updating the parameters of the list
    if(this->capacity != 0)
        delete[] this->nodes;
    this->nodes = newElements;
    this->capacity = newCapacity;
}

// PUBLIC METHODS
Matrix::Matrix(int nrLines, int nrCols):
firstEmpty(-1), head(-1), tail(-1), size(0), capacity(0), linesCount(nrLines), colsCount(nrCols){}


int Matrix::nrLines() const {
	return linesCount;
}


int Matrix::nrColumns() const {
	return colsCount;
}


TElem Matrix::element(int i, int j) const {

    // Checking the validity of the index pair
    if((i<0 || i>=this->linesCount) || (j<0 || j>=this->colsCount))
        throw exception();

    // Parsing the DLLA to find the required value
    int currentNode = head;
    while(currentNode != -1){

        // Comparing the indexes
        if(this->nodes[currentNode].info.line == i && this->nodes[currentNode].info.column == j)
            return this->nodes[currentNode].info.value;

        // Getting the next value
        currentNode = this->nodes[currentNode].next;
    }

    // Element not found, return the NULL Value
    return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {

    // Checking the validity of the index pair
    if((i<0 || i>=this->linesCount) || (j<0 || j>=this->colsCount))
        throw exception();

    // Finding the specified pair or the most suitable position to insert it
    int currentNode = head;
    while(currentNode != -1){

        // Exact position matched
        if(this->nodes[currentNode].info.line == i && this->nodes[currentNode].info.column == j)
            break;

        // Most suitable position if the pair not matched
        if(this->nodes[currentNode].info.line > i || (this->nodes[currentNode].info.line == i && this->nodes[currentNode].info.column > j))
            break;

        // Getting the next value
        currentNode = this->nodes[currentNode].next;
    }

    auto oldValue = NULL_TELEM;
    if(currentNode != -1 && (this->nodes[currentNode].info.line == i && this->nodes[currentNode].info.column == j)){

        // Retaining the Old Value
        oldValue = this->nodes[currentNode].info.value;

        // Element found
        // Remove Element
        if(e==NULL_TELEM){

            // Nulling pointers
            this->nodes[currentNode].prev = -1;
            this->nodes[currentNode].next = -1;

            // The array was previously full
            if(this->firstEmpty == -1){
                this->firstEmpty = currentNode;
            }

            // The array already had an empty cell, link it
            else{
                this->nodes[currentNode].next = this->firstEmpty;
                this->nodes[firstEmpty].prev = currentNode;
                this->firstEmpty = currentNode;
            }

            // Decrease the size
            this->size--;
        }

        // Modify Element
        else{

            // Updating the element in place
            this->nodes[currentNode].info.value = e;
        }

        return oldValue;
    }

    // Introducing a new element
    else if (e != 0){

        // Resizing if the array is full ( no empty cells )
        if(this->firstEmpty == -1) resize();

        // Actual element to insert
        Triple el;
        el.line = i;
        el.column = j;
        el.value = e;

        // Inserting the element and linking
        // Special Case - Head is -1 - List is empty
        if(this->head == -1){

            // Initialize the element pointers
            this->nodes[firstEmpty].prev = -1;
            this->nodes[firstEmpty].next = -1;

            // Adding the element
            this->nodes[firstEmpty].info = el;

            // Updating the head and tail
            this->head = firstEmpty;
            this->tail = firstEmpty;

            // Getting the next first empty
            this->firstEmpty = this->nodes[firstEmpty].next;
        }

        // List already has elements
        else{

            // Saving newFirstEmpty
            int newFirstEmpty = this->nodes[firstEmpty].next;

            // Initializing our position
            this->nodes[firstEmpty].prev = -1;
            this->nodes[firstEmpty].next = -1;

            // Adding the element
            this->nodes[firstEmpty].info = el;

            // Configuring list pointers by case
            // Adding to the tail
            if (currentNode == -1) {
                this->nodes[firstEmpty].prev = this->tail;
                this->nodes[this->tail].next = firstEmpty;
                this->tail = firstEmpty;
            }

            // Adding to the head
            else if (currentNode == this->head) {
                this->nodes[firstEmpty].next = this->head;
                this->nodes[this->head].prev = firstEmpty;
                this->head = firstEmpty;
            }

            // Adding between nodes
            else {
                this->nodes[firstEmpty].next = currentNode;
                this->nodes[firstEmpty].prev = this->nodes[currentNode].prev;
                this->nodes[this->nodes[currentNode].prev].next = firstEmpty;
                this->nodes[currentNode].prev = firstEmpty;
            }

            // Getting the next free element
            this->firstEmpty = newFirstEmpty;
        }

        // Increasing the size
        this->size ++;

        // Nothing was previously on the position, return the null element
        return NULL_TELEM;
    }

    // In case both old and new element was 0
    return NULL_TELEM;
}
