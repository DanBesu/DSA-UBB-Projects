#include "SMIterator.h"
#include <exception>
using namespace std;

// θ(N) - n being the initial capacity
SortedMap::SortedMap(Relation r) {
	this->relation = r;

    this->capacity = INITIAL_CAPACITY;
    this->root = NULL_NODE;
    this->firstEmpty = 0;
    this->nrElements = 0;

	this->left = new int[INITIAL_CAPACITY];
    this->right = new int[INITIAL_CAPACITY];
    this->info = new TElem[INITIAL_CAPACITY];

	for(int i = 0; i < INITIAL_CAPACITY; ++i){
	    this->info[i] = NULL_TPAIR;
        this->left[i] = i+1;
	}
    this->left[INITIAL_CAPACITY - 1] = NULL_NODE;
}

// theta(1)
void SortedMap::initNode(int newPosition, TKey k, TValue v) {
    this->info[newPosition] = TElem{k, v};
    this->left[newPosition] = NULL_NODE;
    this->right[newPosition] = NULL_NODE;
}

TValue SortedMap::add(TKey k, TValue v) {
    if(this->left[firstEmpty] == NULL_NODE)
        resize();
    int newPosition = this->firstEmpty;

    // 1. EMPTY CASE
    if(this->root == NULL_NODE){
        this->root = newPosition;
        this->firstEmpty = this->left[firstEmpty];
        this->initNode(newPosition, k, v);
    }
    else{
        int current = this->root;
        // iterates until the key was found, or the current has no children on the respective side
        while(true){
            // 2. FOUND KEY
            if(this->info[current].first == k){
                TValue oldValue = this->info[current].second;
                this->info[current].second = v;
                return oldValue;
            }
            // 3. "SMALLER" KEY ( if "<" go left )
            if(this->relation(k, this->info[current].first)){
                // if the current has no children on left, and k is "<", put it left
                if(this->left[current] == NULL_NODE){
                    this->firstEmpty = this->left[firstEmpty];
                    this->left[current] = newPosition;
                    this->initNode(newPosition, k, v);
                    break;
                }
                current = this->left[current];//
            } // 4. "GREATER" KEY if ">" go right
            else{
                // if the current has no children on right, and k is ">", put it right
                if(this->right[current] == NULL_NODE){
                    this->firstEmpty = this->left[firstEmpty];
                    this->right[current] = newPosition;
                    this->initNode(newPosition, k, v);
                    break;
                }
                current = this->right[current];
            }
        }
    }
    this->nrElements++;
	return NULL_TVALUE;
}

// O(n)
TValue SortedMap::search(TKey k) const {
    int current = this->root;
    while(current != NULL_NODE && this->info[current].first != k){
        if(this->relation(k, this->info[current].first)){
            current = this->left[current];
        } else{
            current = this->right[current];
        }
    }
    if(current != NULL_NODE)
        return this->info[current].second;
	return NULL_TVALUE;
}

// O(h)
std::pair<int,int> SortedMap::findMax(int current, int parent) {
    while(this->right[current] != NULL_NODE) {
        parent = current;
        current = this->right[current];
    }
    return {current, parent};
}

// O(h) - h = height of the tree
TValue SortedMap::remove(TKey k) {
    if(this->root == NULL_NODE) return NULL_TVALUE;

	int parent = this->root, current = this->root;
    while(current != NULL_NODE){
        if(this->info[current].first == k){
            // CASE 1: NO CHILDREN
            if(this->left[current] == NULL_NODE && this->right[current] == NULL_NODE){
                // compare with the parent
                if(this->relation(this->info[current].first, this->info[parent].first)){
                    // current < parent
                    this->left[parent] = NULL_NODE;
                } else { // current > parent
                    this->right[parent] = NULL_NODE;
                }
                if(this->root == current) // ROOT CASE
                    this->root = NULL_NODE;
            }
            // CASE 2.1: ONLY ONE CHILD - left
            else if(this->left[current] != NULL_NODE && this->right[current] == NULL_NODE){
                // current < parent
                if(this->relation(this->info[current].first, this->info[parent].first)){
                    this->left[parent] = this->left[current];
                } else { // current > parent
                    this->right[parent] = this->left[current];
                }
                if(this->root == current) // ROOT CASE
                    this->root = this->left[current];
            }
            // CASE 2.2: ONLY ONE CHILD - right
            else if(this->left[current] == NULL_NODE && this->right[current] != NULL_NODE){
                // current < parent
                if(this->relation(this->info[current].first, this->info[parent].first)){
                    this->left[parent] = this->right[current];
                } else { // current > parent
                    this->right[parent] = this->right[current];
                }
                if(this->root == current) // ROOT CASE
                    this->root = this->right[current];
            }
            // CASE 3: TWO CHILDREN: find the max on left subtree
            else{
                // find the max, check if the max has a child on the left side
                pair<int, int> maxFound = findMax(this->left[current], current);
                int max = maxFound.first, maxParent = maxFound.second;

                // 3.1 max is the child of current => just move the right of current to max
                if(current == maxParent){
                    this->right[max] = this->right[current];
                }
                // 3.2 max is not the child of current
                else{
                    // if max has a left child, move that to the right of its parent
                    if(this->left[max] != NULL_NODE){
                        this->right[maxParent] = this->left[max];
                    }
                    else{ // otherwise, Null
                        this->right[maxParent] = NULL_NODE;
                    }
                    // change the max with the current node to be removed
                    if(this->relation(this->info[current].first, this->info[parent].first)){ // current < parent
                        this->left[parent] = max;
                    } else { // current > parent
                        this->right[parent] = max;
                    }
                    // pass the children from current to max
                    this->left[max] = this->left[current];
                    this->right[max] = this->right[current];
                }
                if(this->root == current) // ROOT CASE
                    this->root = max;
            }
            // move firstEmpty to this position
            this->left[current] = this->firstEmpty;
            this->firstEmpty = current;
            this->nrElements--;
            return this->info[current].second;
        }
        else if(this->relation(k, this->info[current].first)){
            parent = current;
            current = this->left[current];
        }
        else{
            parent = current;
            current = this->right[current];
        }
    }
	return NULL_TVALUE;
}

//θ(1)
int SortedMap::size() const {
	return this->nrElements;
}

//θ(1)
bool SortedMap::isEmpty() const {
	return this->nrElements == 0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

// θ(N)
SortedMap::~SortedMap() {
	delete[] this->info;
	delete[] this->left;
	delete[] this->right;
}

// θ(N * 2) - where N is the current capacity
void SortedMap::resize() {
    TElem* newInfo = new TElem[this->capacity * 2];
    int* newLeft = new int[this->capacity * 2];
    int* newRight = new int[this->capacity * 2];

    for(int i = 0; i < this->capacity; ++i){
        newInfo[i] = this->info[i];
        newLeft[i] = this->left[i];
        newRight[i] = this->right[i];
    }
    newLeft[firstEmpty] = this->capacity;
    for(int i = this->capacity; i < this->capacity*2 - 1; ++i){
        newLeft[i] = i + 1;
    }
    newLeft[this->capacity * 2 - 1] = -1;

    TElem* oldElements = this->info;
    int* oldLeft = this->left;
    int* oldRight = this->right;

    this->info = newInfo;
    this->left = newLeft;
    this->right = newRight;
    this->capacity *= 2;

    delete oldElements;
    delete oldLeft;
    delete oldRight;
}


// o(n) - n being the number of nodes
int SortedMap::getValueRange() const {
    if(this->nrElements == 0)
        return -1;
    int max = this->info[root].second, min = this->info[root].second;

    TValue* queue;
    queue = new TValue [this->size() * 2];
    int qFront = this->size(), qRear = this->size();
    int qSize = 1;

    queue[qFront] = this->root; // q.push(root)
    while(qSize > 0){
        int current = queue[qFront];

        if(this->info[current].second < min){
            min = this->info[current].second;
        }
        if(this->info[current].second > max){
            max = this->info[current].second;
        }
        // q.pop()
        qFront++;
        qSize--;

        if(this->left[current] != NULL_NODE){
            // q.push(left child)
            qRear++;
            qSize++;
            queue[qRear] = this->left[current];
        }
        if(this->right[current] != NULL_NODE){
            // q.push(right child)
            qRear++;
            qSize++;
            queue[qRear] = this->right[current];
        }
    }
    return max - min;
}
