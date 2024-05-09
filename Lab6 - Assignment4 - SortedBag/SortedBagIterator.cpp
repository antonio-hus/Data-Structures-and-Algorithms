#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <iostream>
#include <exception>

using namespace std;

SortedBag::Node* SortedBagIterator::mergeLists(SortedBag::Node* list1, SortedBag::Node* list2) {
    SortedBag::Node* currentL1 = list1;
    SortedBag::Node* currentL2 = list2;
    SortedBag::Node* headLR = nullptr;
    SortedBag::Node* tailLR = nullptr;

    while(currentL1 != nullptr && currentL2 != nullptr){

        auto* newNode = new SortedBag::Node;
        newNode->next = nullptr;

        if(bag.relation(currentL1->key, currentL2->key)){
            newNode->key = currentL1->key;
            currentL1 = currentL1->next;
        }
        else {
            newNode->key = currentL2->key;
            currentL2 = currentL2->next;
        }

        // Resulting linked list is empty
        if(headLR == nullptr){
            headLR = newNode;
            tailLR = newNode;
        }

        // Adding the next elements
        else {
            tailLR->next = newNode;
            tailLR = newNode;
        }
    }

    // One of the currentNodes is null
    // We will keep the other one in a separate variable
    SortedBag::Node* remainingNode;
    if(currentL1 == nullptr) remainingNode = currentL2;
    else remainingNode = currentL1;

    while(remainingNode != nullptr){

        auto* newNode = new SortedBag::Node;
        newNode->next = nullptr;
        newNode->key = remainingNode->key;

        // Resulting linked list is empty
        if(headLR == nullptr){
            headLR = newNode;
            tailLR = newNode;
        }

        // Adding the next elements
        else {
            tailLR->next = newNode;
            tailLR = newNode;
        }

        remainingNode = remainingNode->next;
    }

    if(tailLR != nullptr)
        tailLR->next = nullptr;
    return headLR;
}
// BC=WC=TC: Theta(sizeList1 + sizeList2) - Merging the two new lists by copying all elements

void SortedBagIterator::mergeHashTable() {
    SortedBag::Node* merged = nullptr;

    for (int i = 0; i < bag.tableCapacity; ++i) {
        merged = mergeLists(merged, bag.elements[i]);
    }

    this->list = merged;
}
// BC=WC=TC: Theta(tableSize) - Triangular sum complexity of merging all lists

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	mergeHashTable();
    first();
}
// BC=WC=TC: Theta(tableSize)

TComp SortedBagIterator::getCurrent() {

    // Throwing an exception if the iterator is not valid
    if(!valid())
        throw exception();

    // Otherwise returning the element at the current position
	return this->currentNode->key;
}
// BC=WC=TC: Theta(1) - Accessing class components is done in constant time

bool SortedBagIterator::valid() {
	return this->currentNode != nullptr;
}
// BC=WC=TC: Theta(1) - Accessing class components is done in constant time

void SortedBagIterator::next() {

    // Throwing an exception if the iterator is not valid
    if(!valid())
        throw exception();

    // Otherwise getting to the next position
	this->currentNode = this->currentNode->next;
}
// BC=WC=TC: Theta(1) - Updating class components is done in constant time

void SortedBagIterator::first() {
	this->currentNode = this->list;
}
// BC=WC=TC: Theta(1) - Updating class components is done in constant time

