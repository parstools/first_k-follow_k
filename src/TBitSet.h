//
// Created by andrzej on 2020-2-9
//
//Tree BitSet
#pragma once
#include <cstdint>
#include <vector>

using namespace std;

class TBitSet {
    typedef uint32_t WORD;
    const int Align = sizeof(WORD)*8;
    vector<WORD> words;
    int dim;
    int size;
    int widthWords;
    int widthBits;
    pair<int,TBitSet::WORD> getBitCoord(int nBit);
    void printSequence(const vector<int> &sequence);
    void recursiveGetSequences(int beginBlock, vector<int> &sequence, vector<vector<int>> &sequences, int maxlen);
public:
    TBitSet(int dim, int size);
    int getSize(){return size;}
    int getDim(){return dim;}
    bool addSequence(const vector<int> &sequence);
    bool existsSequence(const vector<int> &sequence);
    void getSequences(vector<vector<int>> &sequences, int maxlen=-1);
    void print();
    void promoteTo(TBitSet *output, int lastIndex);
    bool unionWith(TBitSet &other);
    bool equal(TBitSet *other);
    void set(TBitSet *other);
    void concatTwo(TBitSet &begins, TBitSet &ends);
    bool isEmpty();
};

