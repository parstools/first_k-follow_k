//
// Created by andrzej on 2020-02-04.
//

#pragma once
#include <cstdint>
#include <vector>

using namespace std;

class BitSet {
private:
    typedef uintptr_t WORD;
    vector<WORD> words;
    static const int Align = sizeof(WORD) * 8;
    int size=0;
    pair<int,WORD> getBitCoord(int n);
public:
    int getSize(){return size;}
    BitSet(){}
    bool get(int n);
    bool set(int n);
    bool clear(int n);
    void rawset(int n);
    void rawclear(int n);
    void clear();
    bool orset(BitSet &other);
    bool andset(BitSet &other);
};

