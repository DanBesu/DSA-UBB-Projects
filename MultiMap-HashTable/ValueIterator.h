#pragma once
#include "MultiMap.h"
#include "MultiMapIterator.h"
class MultiMap;

class ValueIterator {

    friend class MultiMap;

private:
    const MultiMap& col;
    TKey key;
    int currentArrayPosition;
    int hashPosition;
    Node* keyNode;
//    ValueIterator(const MultiMap map, TKey i);
    explicit ValueIterator(const MultiMap& c, TKey k);

public:
    TElem getCurrent()const;
    bool valid() const;
    void next();
    void first();
};

