#include "SortedBag.h"
#include "SortedBagIterator.h"

int SortedBag::hash(TElem element) const {
    if(element < 0) element *= -1;
    return element % this->tableCapacity;
}
// BC=WC=TC: Theta(1) - Accessing class elements is done in constant time

SortedBag::SortedBag(Relation r): tableCapacity(13), tableSize(0){

    // Initializing the relation
    this->relation = r;

    // Initializing the Linked Lists
    this->elements = new Node*[tableCapacity];
    for(int i=0; i<tableCapacity; i++){
        this->elements[i] = nullptr;
    }
}
// BC=WC=TC: Theta(tableCapacity) - Allocating the hash table's linked lists

void SortedBag::add(TComp e) {

    // Getting the Hash Table slot to insert at
    int hashedKey = hash(e);

    // Getting to position hashedKey
    // Finding the linked list node to insert at respecting the relation order
    Node* prevNode = nullptr;
    Node* currentNode = this->elements[hashedKey];
    while(currentNode!= nullptr && relation(currentNode->key,e)){
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    // Inserting in the head
    if(prevNode == nullptr){

        auto newNode = new Node;
        newNode->next = this->elements[hashedKey];
        newNode->key = e;

        this->elements[hashedKey] = newNode;
    }

    // Inserting in the tail
    else if(currentNode == nullptr){

        auto newNode = new Node;
        newNode->next = nullptr;
        newNode->key = e;

        prevNode->next = newNode;
    }

    // Inserting in the linked list
    else {

        auto newNode = new Node;
        newNode->next = currentNode;
        newNode->key = e;

        prevNode->next = newNode;
    }

    this->tableSize ++;
}
// BC: Theta(1) - Adding to the start of the corresponding Linked List
// WC: Theta(tableCapacity) - All elements of the table are in the same Linked List and we must add to the end
// TC: Theta(alpha) - Alpha is usually 1


bool SortedBag::remove(TComp e) {

    // Getting the Hash Table slot to remove from
    int hashedKey = hash(e);

    // Getting to position hashedKey
    // Finding the linked list node to remove
    Node* prevNode = nullptr;
    Node* currentNode = this->elements[hashedKey];
    while(currentNode!= nullptr && currentNode->key != e){
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    // Element was not found
    if(currentNode == nullptr) return false;

    // Element was found
    else{

        // Removing from the head
        if(prevNode == nullptr){

            this->elements[hashedKey] = currentNode->next;
            delete currentNode;
        }

        // Removing from the tail or from the linked list
        else {

            prevNode->next = currentNode->next;
            delete currentNode;
        }

        this->tableSize --;
        return true;
    }
}
// BC: Theta(1) - Removing from the start of the corresponding Linked List
// WC: Theta(tableCapacity) - All elements of the table are in the same Linked List
//                            and we must remove from the end or the element was not found
// TC: Theta(alpha) - Alpha is usually 1


bool SortedBag::search(TComp elem) const {

    // Getting the Hash Table slot to search at
    int hashedKey = hash(elem);

    // Getting to position hashedKey
    // Finding the linked list node
    Node* currentNode = this->elements[hashedKey];
    while(currentNode!= nullptr && currentNode->key != elem){
        currentNode = currentNode->next;
    }

    // Returning true only if the element was found in the list, otherwise false
    return currentNode != nullptr;
}
// BC: Theta(1) - Element found at the start of the corresponding Linked List
// WC: Theta(tableCapacity) - All elements of the table are in the same Linked List
//                            and we must search to the end or the element was not found
// TC: Theta(alpha) - Alpha is usually 1


int SortedBag::nrOccurrences(TComp elem) const {

    // Counting occurrences
    int count = 0;

    // Getting the Hash Table slot to search at
    int hashedKey = hash(elem);

    // Getting to position hashedKey
    // Finding the linked list node
    Node* currentNode = this->elements[hashedKey];
    while(currentNode!= nullptr){

        if(currentNode->key == elem) count ++;

        // Stopping after the end of elem sequence
        if(count > 0 && currentNode->key != elem) break;

        currentNode = currentNode->next;
    }

	return count;
}
// BC: Theta(1) - Elements were found at the start of the corresponding Linked List
// WC: Theta(tableCapacity) - All elements of the table are in the same Linked List
//                            and we must count at the end or the elements were not found
// TC: Theta(alpha) - Alpha is usually 1


int SortedBag::size() const {
	return this->tableSize;
}
// BC=WC=TC: Theta(1) - Accessing class elements is done in constant time

bool SortedBag::isEmpty() const {
	return this->tableSize == 0;
}
// BC=WC=TC: Theta(1) - Accessing class elements is done in constant time

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
// BC=WC=TC: Theta(tableSize*tableCapacity) - Initializing the iterator by merging the table's linked lists

SortedBag::~SortedBag() {

    // Deallocating the Hash Table
    for(int i=0; i<tableCapacity; i++){

        // For each hash table slot, free the linked list
        Node* currentNode = this->elements[i];
        while(currentNode!= nullptr){
            Node* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }

        // Set the pointer to nullptr after deleting the nodes
        this->elements[i] = nullptr;
    }
}
// BC=WC=TC: Theta(max(tableCapacity, tableSize)) - Deallocating the hash table's linked lists

/// EXTRA OPERATION
int SortedBag::distinctCount() const {

    int count = 0;

    // Going through the entire table
    for(int i=0; i<tableCapacity; i++){

        // Initially the lastValue is the null element
        int lastValue = NULL_TCOMP;

        // For each hash table slot we have a linked list
        // Inside the linked list, components are kept in order
        // Hence elements with the same value are in the same linked list, one after the other
        Node* currentNode = this->elements[i];
        while(currentNode!= nullptr){

            // If the value changed, increase the distinct count
            if(lastValue != currentNode->key){
                count++;
                lastValue = currentNode->key;
            }

            // Getting the next element
            currentNode = currentNode->next;
        }
    }

    // Returning the distinct numbers count
    return count;
}
// BC=WC=TC: Theta(max(tableCapacity, tableSize)) - We have to go through all elements of the table
