#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
#include <exception>

class Matrix {
private:

    // Representing the Line - Column - Value triples
    typedef struct {
        int line, column;
        TElem value;
    }Triple;

    // Representing a node of the DLLA
    class DLLANode{
    public:
        Triple info;
        int next, prev;
    };

    // DLLA Based Structure
    DLLANode* nodes;
    int capacity, size;
    int head, tail, firstEmpty;

    // Matrix Structure
    int linesCount, colsCount;

    // Helper Functions
    void resize();
    int allocate();
    void free(int position);
    void insertAtPosition(int position, Triple element);

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};
