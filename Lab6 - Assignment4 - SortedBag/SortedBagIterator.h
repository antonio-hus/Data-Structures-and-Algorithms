#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
    const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

    // Linked List Structure
    SortedBag::Node* list;
    SortedBag::Node* currentNode;

    // Creating the HashTable Linked Lists
    SortedBag::Node* mergeLists(SortedBag::Node* list1, SortedBag::Node* list2);
    void mergeHashTable();

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

