#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m):
multime(m), current(m.root), stackCapacity(10), stackTop(-1){

    // Initializing the stack
    stack = new SortedSet::BSTNode*[stackCapacity];
    SortedSet::BSTNode* node = m.root;

    // Initial Traversal to the leftmost child
    while (node != nullptr) {
        if (stackTop == stackCapacity - 1) {
            resizeStack();
        }
        stack[++stackTop] = node;
        node = node->leftChild;
    }

    // Getting the current element
    if (stackTop != -1) {
        current = stack[stackTop];
    }
}
// BC: Theta(1) - Root has no left child
// WC: Theta(setSize) - Initial traversal to the leftmost node in a degenerate chained tree
// TC: O(setSize)

void SortedSetIterator::resizeStack() {
    int newCapacity = stackCapacity * 2;
    auto** newStack = new SortedSet::BSTNode*[newCapacity];
    for (int i = 0; i < stackCapacity; ++i) {
        newStack[i] = stack[i];
    }
    delete[] stack;
    stack = newStack;
    stackCapacity = newCapacity;
}
// BC=WC=TC: Theta(stackSize) - Resizing operation for the current stack capacity

void SortedSetIterator::first() {
    stackTop = -1;
    SortedSet::BSTNode* node = this->multime.root;
    while (node != nullptr) {
        if (stackTop == stackCapacity - 1) {
            resizeStack();
        }
        stack[++stackTop] = node;
        node = node->leftChild;
    }
    if (stackTop != -1) {
        current = stack[stackTop];
    } else {
        current = nullptr;
    }
}
// BC: Theta(1) - Root has no left child
// WC: Theta(setSize) - Initial traversal to the leftmost node in a degenerate chained tree
// TC: O(setSize)

void SortedSetIterator::next() {

    // Throwing an exception in case the iterator is not valid
    if (!valid()) {
        throw exception();
    }

    // Otherwise getting the next node in order
    SortedSet::BSTNode* node = stack[stackTop--];
    if (node->rightChild != nullptr) {
        node = node->rightChild;
        while (node != nullptr) {
            if (stackTop == stackCapacity - 1) {
                resizeStack();
            }
            stack[++stackTop] = node;
            node = node->leftChild;
        }
    }
    if (stackTop != -1) {
        current = stack[stackTop];
    } else {
        current = nullptr;
    }

}
// BC: Theta(1) - No right child and no further traversal needed
// WC: Theta(h) - Right child exists, and traversal to the leftmost node in the right subtree
// TC: O(h) - Traversal to the leftmost node, where h is the height of the tree

TElem SortedSetIterator::getCurrent()
{
    // Throwing an exception in case the iterator is not valid
    if (!valid()) {
        throw exception();
    }

    // Otherwise returning the current node's information
	return this->current->info;
}
// BC=WC=TC: Theta(1) - Accessing class parameters is done in constant time

bool SortedSetIterator::valid() const {
	return this->current != nullptr;
}
// BC=WC=TC: Theta(1) - Accessing class parameters is done in constant time

SortedSetIterator::~SortedSetIterator() {
    delete[] stack;
}
// BC=WC=TC: Theta(1) - Deallocating class parameters is done in constant time