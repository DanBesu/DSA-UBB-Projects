#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

/// ADT  SortedList
/// (interface  with TPozition  =  Integer-IndexedList)
/// –using a  DLL  where elements are ordered based on a relation.

/// O(1)
SortedIndexedList::SortedIndexedList(Relation r) {
    this->head = nullptr;
    this->tail = nullptr;

    this->nrElements = 0;
    this->relation = r;
}

/// O(1)
int SortedIndexedList::size() const {
	return this->nrElements;
}

/// O(1)
bool SortedIndexedList::isEmpty() const {
	return this->nrElements == 0;
}

/// O(n)
TComp SortedIndexedList::getElement(int i) const{

    if(!this->validIndex(i)) throw exception();
    Node* current = this->head;
    int index = 0;
    while(index < i){
        current = current->next;
        index++;
    }
    return current->info;
}

/// O(n)
TComp SortedIndexedList::remove(int i) {

    // check for bad input
    if(!this->validIndex(i)) throw exception();

    // find the node to be deleted
    Node* current = this->head;
    int index = 0;
    while(index < i){
        current = current->next;
        ++index;
    }
    int deletedElement;

    // nrElements = 1
    if(current->prev == nullptr && current->next == nullptr){
        deletedElement = current->info;
        this->head = nullptr;
        this->tail = nullptr;
        delete current;
        this->nrElements--;
        return deletedElement;
    }
    // delete head
    else if(current->prev == nullptr){
        deletedElement = current->info;
        this->head = this->head->next;
        this->head->prev = nullptr;
        this->nrElements--;
        delete current;
        return deletedElement;
    }
    // delete tail
    else if(current->next == nullptr){
        deletedElement = current->info;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        this->nrElements--;
        delete current;
        return deletedElement;
    }
    // delete in the middle
    else{
        deletedElement = current->info;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        this->nrElements--;
        delete current;
        return deletedElement;
    }
}

/// O(n)
/// todo: explain crazy innovative idea
int SortedIndexedList::search(TComp e) const {

    Node* currentNode = this->head;
    int index = 0;

    while(currentNode != nullptr){
        if(currentNode->info == e)
            return index;
        currentNode = currentNode->next;
        index++;
    }
	return -1;
}

/// O(n)
void SortedIndexedList::add(TComp e) {
    Node* newNode = new Node;
    newNode->info = e;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
        this->nrElements++;
    }
    else{
        Node* current = this->head;
        while(current != nullptr){
            if(this->relation(e, current->info)){
                /// case: before the head
                if(current->prev == nullptr){
                    newNode->next = this->head;
                    current->prev = newNode;
                    this->head = newNode;
                    this->nrElements++;
                    break;
                }
                /// case: in the middle (go until e is "smaller than" an element and the element is not the tail)
                else {
                    current->prev->next = newNode;
                    newNode->prev = current->prev;
                    newNode->next = current;
                    current->prev = newNode;
                    this->nrElements++;
                    break;
                }
            }
            /// case: after the tail
            else{
                if(current->next == nullptr){
                    current->next = newNode;
                    newNode->prev = current;
                    this->tail = newNode;
                    this->nrElements++;
                    break;
                }
            }
            current = current->next;
        }
    }
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
/// theta(n)
SortedIndexedList::~SortedIndexedList() {
    if(this->head == nullptr) return;
    while(this->head != nullptr){
        Node* current = this->head;
        this->head = this->head->next;
        delete current;
    }
}

/// theta(1)
bool SortedIndexedList::validIndex(int i) const {
    return !(i < 0 || i >= this->nrElements);
}

/// O(n)
void SortedIndexedList::print_list() {
    Node* current = this->head;
    while(current != nullptr){
        cout << "val: " << current->info << '\n';
        current = current->next;
    }
}

/// theta(1)
TComp SortedIndexedList::removeElement(Node *currentElement) {

    TComp deletedElement = currentElement->info;

    // nrElements = 1
    if(currentElement->prev == nullptr && currentElement->next == nullptr){
        deletedElement = currentElement->info;
        this->head = nullptr;
        this->tail = nullptr;
        delete currentElement;
        this->nrElements--;
        return deletedElement;
    }
        // delete head
    else if(currentElement->prev == nullptr){
        deletedElement = currentElement->info;
        this->head = this->head->next;
        this->head->prev = nullptr;
        this->nrElements--;
        delete currentElement;
        return deletedElement;
    }
        // delete tail
    else if(currentElement->next == nullptr){
        deletedElement = currentElement->info;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        this->nrElements--;
        delete currentElement;
        return deletedElement;
    }
        // delete in the middle
    else{
        deletedElement = currentElement->info;
        currentElement->prev->next = currentElement->next;
        currentElement->next->prev = currentElement->prev;
        this->nrElements--;
        delete currentElement;
        return deletedElement;
    }

}
