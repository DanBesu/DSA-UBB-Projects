#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

// O(h)  (where h is the height of the tree)
SMIterator::SMIterator(const SortedMap& mapionar) : map(mapionar){
    this->stackCapacity = STACK_INITIAL_CAPACITY;
    this->stackSize = 0;
    this->nodeStack = new int[this->stackCapacity];
    this->currentNode = NULL_NODE;

    this->first();
}

// O(h)
void SMIterator::first() {
    this->stackSize = 0;
    // push all the left nodes into the stack
    int node = this->map.root;
    while(node != NULL_NODE){
        if(this->stackSize == this->stackCapacity)
            this->resizeStack();
        // push into the stack
        this->nodeStack[this->stackSize++] = node;
        node = this->map.left[node];
    }
    // set the current node as the top of the stack
    if(this->stackSize)
        this->currentNode = this->nodeStack[this->stackSize - 1];
    else
        this->currentNode = NULL_NODE;
}

// O(h)  (where h is the height of the tree)
void SMIterator::next(){
    if(this->stackSize == 0)
        throw std::exception();

    // pop the stack and save the value into a node
    int node = this->nodeStack[--this->stackSize];
    // go in the right subtree of the node and push on the stack all the nodes on the left branch
    if(this->map.right[node] != NULL_NODE){
        node = this->map.right[node];
        while(node != NULL_NODE){
            if(this->stackSize == this->stackCapacity)
                this->resizeStack();
            this->nodeStack[this->stackSize++] = node;
            node = this->map.left[node];
        }
    }
    // set the current node as the top of the stack
    if(this->stackSize)
        this->currentNode = this->nodeStack[this->stackSize - 1];
    else
        this->currentNode = NULL_NODE;
}

// θ(1)
bool SMIterator::valid() const{
    return this->currentNode != NULL_NODE;
}

// θ(1)
TElem SMIterator::getCurrent() const{
    if(this->currentNode == NULL_NODE)
        throw std::exception();
    else
        return this->map.info[this->currentNode];
}

// θ(N)
void SMIterator::resizeStack(){
    this->stackCapacity *= 2;
    int * newStack = new int[this->stackCapacity];
    for(int i = 0; i < this->stackSize; ++i)
        newStack[i] = this->nodeStack[i];
    delete[] nodeStack;
    nodeStack = newStack;
}

// θ(N)
SMIterator::~SMIterator(){
    delete[] this->nodeStack;
}
