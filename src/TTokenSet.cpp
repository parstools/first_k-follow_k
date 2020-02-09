//
// Created by andrzej on 2/9/20.
//

#include <iostream>
#include "TTokenSet.h"

TTokenSet::TTokenSet(int k, int size):k(k), size(size) {
    for (int i=1; i<=k; i++) {
        TBitSet bitSet(i,size);
        levels.push_back(bitSet);
    }
}

bool TTokenSet::addSequence(const vector<int> &sequence) {
    if (sequence.size() > k) throw "too big sequence";
    return levels[sequence.size() - 1].addSequence(sequence);
}

bool TTokenSet::existsSeqence(const vector<int> &sequence) {
    if (sequence.size() > k) throw "too big sequence";
    return levels[sequence.size() - 1].existsSequence(sequence);
}

bool TTokenSet::append(int token) {
    vector<TBitSet> altlevels;
    TBitSet bitSet(1,size);
    if (eps)
    {
        bitSet.addSequence({token});
    }
    altlevels.push_back(bitSet);
    for (int i=0; i<k-1; i++)
    {
        TBitSet bitSet(i+2,size);
        levels[i].promoteTo(&bitSet,token);
        altlevels.push_back(bitSet);
    }
    int result = eps;
    eps = false;
    for (int i=0; i<k-1; i++) {
        if (!levels[i].equal(&altlevels[i])) result = true;
        levels[i].set(&altlevels[i]);
    }
    if (levels[k-1].unionWith(altlevels[k-1])) result = true;
    return result;
}

bool TTokenSet::concat(TTokenSet &secondSet) {
    vector<TBitSet> altlevels;
    for (int i = 0; i < k; i++) {
        TBitSet bitSet(i + 1, size);
        altlevels.push_back(bitSet);
    }

    bool result = false;
    if (eps)
    {
        if (!secondSet.eps) {
            eps = false;
            result = true;
        }
        for (int i = 0; i < k; i++)
            altlevels[i].set(&secondSet.levels[i]);
    }
    for (int i = 0; i < k-1;i++)
        for (int j = 0; j < k;j++)
        {
            int tmplevel = min(k,i + j + 2);
            TBitSet bitSet(tmplevel, size);
            bitSet.concatTwo(levels[i], secondSet.levels[j]);
            altlevels[tmplevel-1].unionWith(bitSet);
        }

    for (int i=0; i<k-1; i++) {
        if (!levels[i].equal(&altlevels[i])) result = true;
        levels[i].set(&altlevels[i]);
    }
    if (levels[k-1].unionWith(altlevels[k-1])) result = true;
    return result;
}

void TTokenSet::print(const GramNames *names) {
    if (eps)
        cout << "eps,";
    for (int i=0; i<k; i++) {
        vector<vector<int>> sequences;
        levels[i].getSequences(sequences);
        for (auto &seq: sequences) {
            for (int i=0; i<seq.size(); i++) {
                cout << names->termNames[i];
                if (i<seq.size()-1)cout << " ";
            }
            cout <<",";
        }
    }
}

bool TTokenSet::concatenable() {
    if (eps) return true;
    for (int i=0; i<k-1; i++)
        if (!levels[i].isEmpty()) return true;
    return false;
}

bool TTokenSet::unionWith(TTokenSet &other) {
    bool changed = false;
    if (!eps && other.eps) {
        eps = true;
        changed = true;
    }
    for (int i=0; i<k; i++)
        if (levels[i].unionWith(other.levels[i])) changed = true;
    return changed;
}