#include <assert.h>
#include <iostream>
#include "../SortedMap.h"
#include "../SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());

    SortedMap map2(relatie1);
    pair<TKey, TValue> el1 (1, 6) ;
    pair<TKey, TValue> el2 (3, 4) ;
    pair<TKey, TValue> el3 (5, 2) ;

    map2.add(1, 6);
    map2.add(3, 4);
    map2.add(5, 2);
//    map2.printMap();

    SMIterator iterator = map2.iterator();
    iterator.first();
    assert(iterator.getCurrent() == el1);
    iterator.next();
    iterator.previous();
    assert(iterator.getCurrent() == el1);
    iterator.previous();

}

