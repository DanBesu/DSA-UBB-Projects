
#include "ValueIterator.h"

//
ValueIterator::ValueIterator(const MultiMap& c, TKey k): col(c), key(k){
    this->hashPosition = this->col.hashFunction(k);
    this->keyNode = nullptr;

    if(this->col.table[this->hashPosition] == nullptr){
        this->currentArrayPosition = -1;
    }

    Node* current = this->col.table[this->hashPosition];
    while(current != nullptr){
        if(current->key == k){
            this->currentArrayPosition = 0;
            this->keyNode = current;
        }
        current = current->next;
    }
    if(this->keyNode == nullptr){
        this->currentArrayPosition = -1;
    }
}
// Theta(1)
TElem ValueIterator::getCurrent() const {
    if(!this->valid()) throw exception();
    return TElem {this->key, this->keyNode->values[this->currentArrayPosition]};
}
// Theta(1)
bool ValueIterator::valid() const {
    return this->currentArrayPosition >= 0 && this->currentArrayPosition < this->keyNode->length;
}
// Theta(1)
void ValueIterator::next() {
    if(!this->valid()) throw exception();
    this->currentArrayPosition++;
}
// Theta(1)
void ValueIterator::first() {
    this->currentArrayPosition = 0;
}