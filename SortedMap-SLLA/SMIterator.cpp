#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

// θ(1)
SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->current = map.head;
}

// θ(1)
void SMIterator::first(){
	this->current = map.head;
}

// θ(1)
void SMIterator::next(){
	if(!this->valid())
        throw exception();
	this->current = map.next[current];
}

// θ(1)
bool SMIterator::valid() const{
    return this->current != -1;
}

// θ(1)
TElem SMIterator::getCurrent() const{
    if(!this->valid())
        throw exception();
    return map.elements[current];
}

// O(n)
void SMIterator::previous() {
    if(!this->valid())
        throw exception();
    this->current = map.searchPrevious(this->current);
}
