#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
#include <exception>

class Matrix {
private:

    // Triple Structure for holding our Sparse-Matrix Elements
    typedef struct {
        TElem value;
        int line, column;
    }Triple;

    // DLLA Node Structure
    typedef struct {
        Triple info;
        int next, prev;
    }DLLANode;

    // DLLA List Structure
    int firstEmpty, head, tail;
    int size, capacity;
    DLLANode* nodes;

    // Matrix Structure
    int linesCount, colsCount;

    // DLLA List Operations
    void resize();

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
