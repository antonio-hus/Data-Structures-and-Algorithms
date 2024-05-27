#pragma once

/// TYPE DEFINITIONS
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111

/// SORTED SET ITERATOR CLASS DECLARATION
class SortedSetIterator;

/// SORTED SET CLASS DECLARATION
class SortedSet {
	friend class SortedSetIterator;
private:

    /// BST BASED REPRESENTATION
    // Node Structure
    typedef struct BSTNode{
        TComp info;
        BSTNode* leftChild;
        BSTNode* rightChild;
    }BSTNode;

    // BST Root
    BSTNode* root;

    // Container Information
    int setSize;

    /// SORTED CONTAINER RELATION
    Relation relation;

    /// HELPER FUNCTIONS
    void deallocateRec(BSTNode* node);

public:

	// Constructor
	explicit SortedSet(Relation r);

	// Adds an element to the sorted set
	// If the element was added, the operation returns true, otherwise (if the element was already in the set)
	// It returns false
	bool add(TComp e);

	// Removes an element from the sorted set
	// If the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	// Checks if an element is in the sorted set
	bool search(TElem elem) const;

	// Returns the number of elements from the sorted set
	int size() const;

	// Checks if the sorted set is empty
	bool isEmpty() const;

	// Returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// Destructor
	~SortedSet();
};
