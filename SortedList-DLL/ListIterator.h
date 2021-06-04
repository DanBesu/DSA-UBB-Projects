#pragma once
#include "SortedIndexedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
    SortedIndexedList& list;
	explicit ListIterator( SortedIndexedList& list);

	Node* current;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;

    void last();
    void prev();
    TComp remove();
};


