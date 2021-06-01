#include "MultiMap.h"
#include "MultiMapIterator.h"
#include "ValueIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// Theta(INITIAL_HASH_SIZE)
MultiMap::MultiMap() {
	this->table = new Node*[INITIAL_HASH_SIZE];

	for (int i=0; i < INITIAL_HASH_SIZE; i++)
	    this->table[i] = nullptr;

	this->hashCounter = INITIAL_HASH_SIZE;
	this->hashSize = INITIAL_HASH_SIZE;
    this->nrElements=0;
}

// O(nrNodes in hashPosition)
void MultiMap::add(TKey c, TValue v) {

	int hashPosition = this->hashFunction(c);
    bool foundKey  = false;

    // CASE 1: empty position => create the head (newNode will be on table[hashPosition])
    if (this->table[hashPosition] == nullptr){
        Node* newNode = new Node;
        newNode->key = c;
        newNode->values[newNode->length] = v;
        newNode->length++;
        newNode->next = this->table[hashPosition];
        this->table[hashPosition] = newNode;
    }
    else{
        // CASE 2: key found => put the new value here
        Node* current = this->table[hashPosition];
        while (current != nullptr){
            if (current->key == c){
                if (current->length == current->capacity)
                    resizeArray(current);
                current->values[current->length] = v;
                current->length++;
                foundKey= true;
            }
            current = current->next;
        }
        // CASE 3: key not found, but the sll has a head
        if (!foundKey) {
            Node *newNode = new Node;
            newNode->key = c;
            newNode->values[newNode->length] = v;
            newNode->length++;
            // put the node to the beginning of the sll for better complexity
            newNode->next = this->table[hashPosition];
            this->table[hashPosition] = newNode;
        }
    }
    this->nrElements++;
    if (checkOverload())
        this->resizeHash();
}
// O(n + nr of nodes in the sll) - n is the number of pairs having the key k
bool MultiMap::remove(TKey c, TValue v) {

	int hashPosition = this->hashFunction(c);
    if (this->table[hashPosition] == nullptr)
        return false;

    // HEAD CASE
    if (this->table[hashPosition]->key == c) {
        // ONE ELEMENT CASE: if there is only one element in the value array,
        // delete the whole node, else just a value
        if (this->table[hashPosition]->length >= 2) { // more than one element
            for (int i  =0; i < this->table[hashPosition]->length; i++) {
                if (this->table[hashPosition]->values[i] == v) {
                    // delete just a value and decrease the size
                    this->table[hashPosition]->values[i] = this->table[hashPosition]->values[this->table[hashPosition]->length - 1];
                    this->table[hashPosition]->length--;
                    this->nrElements--;
                    return true;
                }
            }
        }
        else{ // only one element in the array of the given key => delete the node
            Node* nextNode = this->table[hashPosition]->next;
            delete[] this->table[hashPosition]->values;
            delete this->table[hashPosition];
            this->table[hashPosition] = nextNode;
            this->nrElements--;
            return true;
        }
    }
    // NODE IN APPROX MIDDLE OF THE SLL
    Node* current = this->table[hashPosition];
    Node* previous = current;
    while (current != nullptr){
        if (current->key == c){
            // ONE ELEMENT CASE
            if (current->length >= 2) { // more than one element
                for (int i=0; i<current->length; i++){
                    if (current->values[i] == v){
                        current->values[i] = current->values[current->length - 1];
                        current->length--;
                        this->nrElements--;
                        return true;
                    }
                }
            }
            else{ // just one element
                previous->next = current->next;
                delete[] current->values;
                delete current;
                this->nrElements--;
                return true;
            }
        }
        previous = current;
        current = current->next;
    }
    return false;
}

// O(n) n = number of keys having the same hash value as k
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values;
    int hashPosition = this->hashFunction(c);

    // empty hashPosition
    if (this->table[hashPosition] == nullptr)
        return values;

    // search for the key in the sll of the hashPosition
    Node* current = this->table[hashPosition];
    while (current!= nullptr){
        if (current->key == c){
            for (int i = 0; i<current->length; i++)
                values.push_back(current->values[i]);
            return values;
        }
        current = current->next;
    }
	return values; // key not found
}


// Theta(1)
int MultiMap::size() const {
	return this->nrElements;
}

// Theta(1)
bool MultiMap::isEmpty() const {
    return this->nrElements == 0;
}

// Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

ValueIterator MultiMap::valueIterator(TKey k) const {
    return ValueIterator(*this, k);
}

// Theta(n) n items added
MultiMap::~MultiMap() {
	for (int i = 0; i < this->hashSize; i++){
        Node* node;
        if (this->table[i] != nullptr) // delete the values of the node
            delete[] this->table[i]->values;
        while (this->table[i] != nullptr){ // delete the node itself
            node = this->table[i]->next;
            delete this->table[i];
            this->table[i] = node;
        }
	}
	delete[] this->table;
}

// Theta(1)
int MultiMap::hashFunction(TKey c) const {
    return c < 0 ? (c * -1) % this->hashCounter : c % this->hashCounter;
}

// Theta(1)
bool MultiMap::checkOverload() const {
    return (double)this->nrElements / (double)this->hashSize >= HASH_LOAD_FACTOR;
}

// Theta(n+m), n = total number of key value pairs added to the map, m = number of hash table slots
void MultiMap::resizeHash() {
    Node** newArray = new Node*[this->hashSize * RESIZE_MULTIPLICATION_FACTOR];
    this->hashCounter *= RESIZE_MULTIPLICATION_FACTOR;

    for (int i = 0; i< this->hashSize * RESIZE_MULTIPLICATION_FACTOR; i++){
        newArray[i] = nullptr;
    }

    Node* current;
    for (int i = 0; i < this->hashSize; i++){
        current = this->table[i];
        while (current != nullptr) {
            // find the new hashPosition and update the node
            int newHashPosition = this->hashFunction(current->key);
            Node* newNode = new Node;
            newNode->key = current->key;
            newNode->length = current->length;

            // resize the array of values if needed
            while (current->length > newNode->capacity)
                resizeArray(newNode);
            // move the values in newNode
            for (int indexValue = 0; indexValue < current->length; indexValue++)
                newNode->values[indexValue] = current->values[indexValue];
            // put the new node at the beginning of sll as head
            newNode->next = newArray[newHashPosition];
            newArray[newHashPosition] = newNode;

            current = current->next;
        }
    }
    // delete the old data
    for (int i = 0; i < this->hashSize; i++){
        Node* node;
        if (this->table[i] != nullptr) // delete the values of the node
            delete[] this->table[i]->values;
        while (this->table[i] != nullptr){ // delete the node itself
            node = this->table[i]->next;
            delete this->table[i];
            this->table[i] = node;
        }
    }
    delete[] table;
    this->hashSize *= RESIZE_MULTIPLICATION_FACTOR;
    this->table = newArray;
}

// Theta(n) - n being the length of the array
void MultiMap::resizeArray(Node*& current) {
    auto* newElements = new TValue[current->capacity * 2];
    for (int i=0; i<current->length; i++){
        newElements[i] = current->values[i];
    }
    current->capacity = current->capacity * 2;
    delete[] current->values;
    current->values = newElements;
}


