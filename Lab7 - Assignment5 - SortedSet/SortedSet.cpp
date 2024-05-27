#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r): relation(r), setSize(0), root(nullptr) {}
// BC=WC=TC: Theta(1) - Setting class parameters is done in constant time

bool SortedSet::add(TComp elem) {

    // Start searching the relevant insertion position from the root of the tree
    BSTNode* current = this->root;
    BSTNode* prev = nullptr;
    while(current != nullptr){

        // Keep track of the parent
        prev = current;

        // Element is already found in the set
        if(current->info == elem)
            return false;

        // If the element respects the relation (e.g. '<=' ) go down the right branch
        else if(relation(current->info, elem)){
            current = current->rightChild;
        }

        // Else go down the left branch
        else{
            current = current->leftChild;
        }
    }

    // We reached the new position - initialize the new node
    auto* newNode = new BSTNode;
    newNode->info = elem;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;

    // Special Case - Tree is empty ( root == nullptr <=> prev == nullptr ) - Initialize root
    if(prev == nullptr){
        this->root = newNode;
    }

    // Base Case - Add the new node into the tree
    else{

        if(relation(prev->info, elem)) prev->rightChild = newNode;
        else prev->leftChild = newNode;
    }

    // Element successfully added
    this->setSize ++;
	return true;
}
// BC: Theta(1) - Element needs to be inserted in the root
// WC: Theta(setSize) - BST is in chained form ( degenerate tree )
// TC: O(setSize)

bool SortedSet::remove(TComp elem) {

    // Firstly, we search the element inside the tree
    // Whilst keeping track of its parent
    BSTNode* current = this->root;
    BSTNode* prev = nullptr;

    // Searching for the element and keeping track of the parent
    while (current != nullptr && current->info != elem) {
        prev = current;
        if (relation(current->info, elem)) {
            current = current->rightChild;
        } else {
            current = current->leftChild;
        }
    }

    // Element not found
    if (current == nullptr) {
        return false;
    }

    // Node with only one child or no child
    if (current->leftChild == nullptr || current->rightChild == nullptr) {

        // Getting ( if there is ) the child of the node
        BSTNode* child = (current->leftChild != nullptr) ? current->leftChild : current->rightChild;

        // If the node to be deleted is the root node
        if (prev == nullptr) {
            this->root = child;
        } else {

            // Update the parent to point to the child
            if (prev->leftChild == current) {
                prev->leftChild = child;
            } else {
                prev->rightChild = child;
            }
        }

        // Deallocating the removed node
        delete current;
    }

    // Node with two children
    else {

        // Find the minimum node in the right subtree
        BSTNode* replacementParent = current;
        BSTNode* replacement = current->rightChild;
        while (replacement->leftChild != nullptr) {
            replacementParent = replacement;
            replacement = replacement->leftChild;
        }

        // Replace current's value with replacement's value
        current->info = replacement->info;

        // Remove the replacement node
        if (replacementParent->leftChild == replacement) {
            replacementParent->leftChild = replacement->rightChild;
        } else {
            replacementParent->rightChild = replacement->rightChild;
        }

        // Deallocating the removed node ( in this case the replacement )
        delete replacement;
    }

    // Element removed successfully
    this->setSize--;
    return true;

}
// BC: Theta(1) - Element to remove is found in the head and has only one child
// WC: Theta(setSize) - Element to remove not found, is a leaf, or has two children
// TC: O(setSize)

bool SortedSet::search(TComp elem) const {

    // Start searching from the root of the tree
	BSTNode* current = this->root;
    while(current != nullptr){

        // Base Case
        // Check if the element is found on the current position
        if(current->info == elem)
            return true;

        // If the element respects the relation (e.g. '<=' ) search the right branch
        else if(relation(current->info, elem)){
            current = current->rightChild;
        }

        // Else search the left branch
        else{
            current = current->leftChild;
        }

    }

    // Element not found - return false
	return false;
}
// BC: Theta(1) - Element is the root of the tree
// WC: Theta(setSize) - BST is in chained form ( degenerate tree )
// TC: O(setSize)

int SortedSet::size() const {
	return this->setSize;
}
// BC=WC=TC: Theta(1) - Accessing class parameters is done in constant time

bool SortedSet::isEmpty() const {
	return this->setSize == 0;
}
// BC=WC=TC: Theta(1) - Accessing class parameters is done in constant time

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}
// BC=WC=TC: O(setSize) - Iterator initialization

void SortedSet::deallocateRec(BSTNode* node) {

    // Base Case
    if(node == nullptr)
        return;

    // Recursively deallocate in postorder
    deallocateRec(node->leftChild);
    deallocateRec(node->rightChild);
    delete node;
}
// BC=WC=TC: Theta(setSize) - We need to deallocate all the nodes of the tree

SortedSet::~SortedSet() {

    // Starting from the root we deallocate first the left child, then the right child and finally the root
    deallocateRec(this->root);
}
// BC=WC=TC: Theta(setSize) - We need to deallocate all the nodes of the tree


