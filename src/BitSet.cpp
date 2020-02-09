//
// Created by andrzej on 2020-02-04
//

#include "BitSet.h"

pair<int,BitSet::WORD> BitSet::getBitCoord(int n) {
    pair<int,WORD> p;
    int nWord = n / Align;
    int nBit = n % Align;
    WORD mask = WORD(1)<<nBit;
    return make_pair(nWord, mask);
}

bool BitSet::get(int n) {
    if (n>=size) return false;
    auto p = getBitCoord(n);
    return (words[p.first] & p.second)!=0;
}

void BitSet::rawset(int n) {
    auto p = getBitCoord(n);
    if (n>=size)
    {
        size = n+1;
        int sizeWords = (size + Align - 1) / Align;
        if (sizeWords>words.size())
            words.resize(sizeWords);
    }
    words[p.first] |= p.second;
}

void BitSet::rawclear(int n) {
    if (n>=size) return;
    auto p = getBitCoord(n);
    words[p.first] &= ~p.second;
}

bool BitSet::set(int n) {
    auto p = getBitCoord(n);
    if (n>=size)
    {
        size = n+1;
        int sizeWords = (size + Align - 1) / Align;
        if (sizeWords>words.size())
            words.resize(sizeWords);
    }
    bool wasSet = (words[p.first] & p.second)!=0;
    words[p.first] |= p.second;
    return !wasSet;
}

bool BitSet::clear(int n) {
    if (n>=size) return false;
    auto p = getBitCoord(n);
    bool wasSet = (words[p.first] & p.second)!=0;
    words[p.first] &= ~p.second;
    return wasSet;
}

void BitSet::clear() {
    size = 0;
    words.clear();
}

bool BitSet::orset(BitSet &other) {
    int commonSize = min(size, other.size);
    int commonSizeWords = (commonSize + Align - 1) / Align;
    bool res = false;
    for (int i=0; i<commonSizeWords; i++) {
        WORD diff = other.words[i] & ~words[i];
        if (diff) res=true;
        words[i] |= other.words[i];
    }
    if (other.size>size)
    {
        int newSizeWords = (other.size + Align - 1) / Align;
        int sizeWords = words.size();
        words.resize(newSizeWords);
        for (int i=sizeWords; i<newSizeWords; i++) {
            if (other.words[i]) res=true;
            words[i] = other.words[i];
        }
        size = other.size;
    }
    return res;
}

bool BitSet::andset(BitSet &other) {
    int commonSize = min(size, other.size);
    int commonSizeWords = (commonSize + Align - 1) / Align;
    bool res = false;
    for (int i=0; i<commonSizeWords; i++) {
        WORD diff = words[i] & ~other.words[i];
        if (diff) res=true;
        words[i] &= other.words[i];
    }
    if (other.size<size)
    {
        for (int i=other.size; i<size; i++)
            if (words[i]) res=true;
        words.resize(commonSizeWords);
        size = other.size;
    }
    return res;
}
