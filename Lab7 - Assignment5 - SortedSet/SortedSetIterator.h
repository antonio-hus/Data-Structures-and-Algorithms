#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

    /// BST IN-ORDER TRAVERSAL STRUCTURE
    SortedSet::BSTNode* current;

    SortedSet::BSTNode** stack;
    int stackCapacity, stackTop;
    void resizeStack();

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
    ~SortedSetIterator();
};

