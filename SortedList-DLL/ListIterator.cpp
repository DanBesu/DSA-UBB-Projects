#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(SortedIndexedList& list) : list(list) {
	if(this->list.isEmpty())
	    this->current = nullptr;
	else
        this->current = list.head;
}

void ListIterator::first(){
	this->current = list.head;
}

void ListIterator::last(){
    this->current = list.tail;
}

void ListIterator::next(){
    if(!this->valid()) throw std::exception();
    this->current = this->current->next;
}

TComp ListIterator::getCurrent() const{
    if(!this->valid()) throw std::exception();
    return this->current->info;
}

bool ListIterator::valid() const {
    return this->current != nullptr;
}

/// theta(1)
TComp ListIterator::remove() {
    if(!this->valid()) throw std::exception();

    Node* nextNode = this->current->next;
    TComp currentValue = this->list.removeElement(this->current);
    this->current = nextNode;
    return currentValue;
}


void ListIterator::prev() {
    if(!this->valid()) throw std::exception();
    this->current = this->current->prev;
}
