#pragma once
#include<vector>
#include<utility>


//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
#define HASH_LOAD_FACTOR 0.7
#define RESIZE_MULTIPLICATION_FACTOR 2
#define INITIAL_HASH_SIZE 10
class MultiMapIterator;
class ValueIterator;

struct Node {
    int capacity = 30;
    TKey key=0;
    TValue* values = new TValue[capacity];
    int length=0;
    Node* next = nullptr;
};

class MultiMap
{
	friend class MultiMapIterator;
	friend class ValueIterator;

private:
	Node** table;
	int nrElements;
	int hashSize;
    int hashCounter;

	int hashFunction(TKey c) const;
	bool checkOverload() const;
	void resizeHash();
	void resizeArray(Node*& current);

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;
    ValueIterator valueIterator(TKey k) const;

	//descturctor
	~MultiMap();
};
