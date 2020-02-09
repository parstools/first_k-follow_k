//
// Created by andrzej on 2/9/20.
//

#ifndef PLLONE_TTOKENSET_H
#define PLLONE_TTOKENSET_H

#include "TBitSet.h"
#include "GramNames.h"

class TTokenSet {
    int k;
    int size;
    vector<TBitSet> levels;
public:
    bool eps=false;
    TTokenSet(int k, int size);
    int getSize() {return size;}
    int getk() {return k;}
    bool addSequence(const vector<int> &sequence);
    bool existsSeqence(const vector<int> &sequence);
    bool append(int token);
    bool concat(TTokenSet &secondSet);
    void print(const GramNames *names);
    bool concatenable();
    bool unionWith(TTokenSet &other);
};


#endif //PLLONE_TTOKENSET_H
