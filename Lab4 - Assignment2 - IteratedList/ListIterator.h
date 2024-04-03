// This module defines the List Iterator

/// DEFINITIONS SECTION
#pragma once

class IteratedList;
typedef int TElem;

/// IMPORTS SECTION
// Libraries
#include <exception>
// User Defined Modules
#include "IteratedList.h"

/// CLASS DEFINITION
class ListIterator{
private:

    // CLASS PROPERTIES
	SLLNode* currentNodePtr;
	const IteratedList& list;

    // CLASS OPERATOR OVERLOADS
    bool operator!=(ListIterator other);

    friend class IteratedList;
	ListIterator(const IteratedList& list);

public:

    // CLASS ITERATOR INDEX MANIPULATION METHODS
	void first();
	void next();

    // CLASS VALIDATOR METHODS
	bool valid() const;

    // CLASS GETTER METHODS
    TElem getCurrent() const;
};


