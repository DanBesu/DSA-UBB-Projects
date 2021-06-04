#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

// θ(INIT_CAPACITY)
SortedMap::SortedMap(Relation r) {

    this->relation = r;
    this->nrElements = 0;
    this->capacity = INIT_CAPACITY;
    this->elements = new TElem[capacity];
    this->next = new int[capacity];
    this->head = -1;

    for(int i = 0; i < this->capacity - 1; ++i){
        this->next[i] = i+1;
    }

    this->next[this->capacity - 1] = -1;
    this->firstEmpty = 0;
}

// θ(N * 2) - where N is the current capacity
void SortedMap::resize() {
    TElem* newElementArray = new TElem[this->capacity*2];
    int* newNext = new int[this->capacity*2];

    for(int i = 0; i < this->capacity; ++i){
        newElementArray[i] = this->elements[i];
        newNext[i] = this->next[i];
    }
    newNext[firstEmpty] = this->capacity;
    for(int i = this->capacity; i < this->capacity*2 - 1; ++i){
        newNext[i] = i + 1;
    }
    newNext[this->capacity*2 - 1] = -1;

    TElem* oldElements = this->elements;
    int* oldNext = this->next;

    this->elements = newElementArray;
    this->next = newNext;
    this->capacity *= 2;

    delete oldElements;
    delete oldNext;
}

// O(n)
TValue SortedMap::add(TKey k, TValue v) {
    if(this->next[this->firstEmpty] == -1)
        resize();

    int current1 = this->head;
    int current2 = this->head;

    while(current2 != -1 && this->relation(this->elements[current2].first, k)){
        if(this->elements[current2].first == k){
            // update value at existent key
            TValue oldValue = this->elements[current2].second;
            this->elements[current2].second = v;
            return oldValue;
        }
        current1 = current2;
        current2 = this->next[current2];
    }

    // key not found
    int nextOfFirstEmpty = this->next[this->firstEmpty];
    this->elements[this->firstEmpty] = pair<TKey, TValue>(k, v); // ANY CASE: put the value on the first available position
    this->next[this->firstEmpty] = current2;
    if(current1 != -1 && current1 != current2) { // MIDDLE CASE: update the previous element (if we dont have to manage the head)
        this->next[current1] = this->firstEmpty;
    }
    if(current2 == this->head) { // HEAD CASE: update the head
        this->head = this->firstEmpty;
    }
    this->firstEmpty = nextOfFirstEmpty;
    this->nrElements++;
	return NULL_TVALUE;
}

// O(n)
TValue SortedMap::search(TKey k) const {

    int current = this->head;
    while(current != -1 && this->elements[current].first != k){
        current = this->next[current];
    }
    return current == -1 ? NULL_TVALUE : elements[current].second;
}

// O(n)
TValue SortedMap::remove(TKey k) {
	int current1 = this->head;
    int current2 = this->head;

    while(current2 != -1 && this->elements[current2].first != k){
        current1 = current2;
        current2 = this->next[current2];
	}
	if(current2 == -1){ // non-existent element or empty map
        return NULL_TVALUE;
	}

	if(current2 == this->head){
	    this->head = this->next[current2];
	}

	this->next[current1] = this->next[current2];
	this->next[current2] = this->firstEmpty;
	this->firstEmpty = current2;
    this->nrElements -= 1;

	return this->elements[current2].second;
}

// θ(1)
int SortedMap::size() const {
	return this->nrElements;
}

// θ(1)
bool SortedMap::isEmpty() const {
    return this->nrElements == 0;
}

// θ(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

// θ(1)
SortedMap::~SortedMap() {
	delete[] this->elements;
	delete[] this->next;
}

// θ(n)
void SortedMap::printMap() {
    int current = this->head;
    while(current != -1){
        cout << this->elements[current].first << "-" << this->elements[current].second << '\n';
        current = this->next[current];
    }
    cout << "done\n";
}

// O(n)
int SortedMap::searchPrevious(int index) const{
    int current1 = this->head;
    int current2 = this->head;

    while(current2 != -1 && current2 != index){
        current1 = current2;
        current2 = this->next[current2];
    }
    return current1;
}
