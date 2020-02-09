//
// Created by andrzej on 2/9/20.

#include <iostream>
#include "TBitSet.h"

TBitSet::TBitSet(int dim, int size): dim(dim), size(size) {
    widthWords = (size+Align-1)/Align;
    widthBits = widthWords*Align;
    if (size==1)
        words.resize(widthWords);
    else
        words.resize(size);
}

bool TBitSet::isEmpty() {
    int initsize;
    if (size==1)
        initsize = widthWords;
    else
        initsize = size;
    if (words.size()>initsize) return false;
    for (int i=0; i<initsize; i++)
        if (words[i])return false;
    return true;
}

pair<int,TBitSet::WORD> TBitSet::getBitCoord(int nBit)
{
    pair<int,WORD> p;
    int nWord = nBit / Align;
    int nBitInWord = nBit % Align;
    WORD mask = WORD(1)<<nBitInWord;
    return make_pair(nWord, mask);
}

bool TBitSet::addSequence(const vector<int> &sequence) {
    if (sequence.size() != dim) throw "bad sequence size";
    int beginBlock = 0;
    for (int i=0; i<dim-1; i++)
    {
        int Index = beginBlock + sequence[i];
        beginBlock = words[Index];
        if (!beginBlock) {
            beginBlock = words.size();
            words[Index] = beginBlock;
            int newBlockSize;
            if (i<dim-2)
                newBlockSize = size;
            else
                newBlockSize = widthWords;
            words.resize(beginBlock+ newBlockSize);
        };
    }
    auto p = getBitCoord(sequence.back());
    bool wasSet = (words[beginBlock+p.first] & p.second)!=0;
    words[beginBlock+p.first] |= p.second;
    return !wasSet;
}

bool TBitSet::existsSequence(const vector<int> &sequence) {
    if (sequence.size() != dim) throw "bad sequence size";
    int beginBlock = 0;
    for (int i=0; i<dim-1; i++)
    {
        beginBlock = words[beginBlock + sequence[i]];
        if (!beginBlock) return false;
    }
    auto p = getBitCoord(sequence.back());
    return (words[beginBlock+p.first] & p.second)!=0;
}

void TBitSet::printSequence(const vector<int> &sequence) {
    for (int i=0; i < sequence.size(); i++)
    {
        cout << sequence[i];
        if (i < sequence.size() - 1)
            cout << " ";
        else
            cout << ",";
    }
}

void TBitSet::promoteTo(TBitSet *output, int lastIndex) {
    vector<vector<int>> sequences;
    getSequences(sequences);
    for (auto &seq: sequences) {
        seq.push_back(lastIndex);
        output->addSequence(seq);
    }
}

void TBitSet::recursiveGetSequences(int beginBlock, vector<int> &sequence, vector<vector<int>> &sequences, int maxlen) {
    int d = sequence.size();
    if (d+1<dim)
    {
        for (int j=0; j<size; j++)
            if (int newbeginBlock = words[beginBlock+j])
            {
                sequence.push_back(j);
                if (maxlen>=0 && sequence.size()>=maxlen)
                    sequences.push_back(sequence);
                else
                    recursiveGetSequences(newbeginBlock, sequence, sequences, maxlen);
                sequence.pop_back();
            }
    }
    else for (int j=0; j<size; j++)
        {
            auto p = getBitCoord(j);
            if ((words[beginBlock+p.first] & p.second)!=0)
            {
                sequence.push_back(j);
                sequences.push_back(sequence);
                sequence.pop_back();
            }
        }
}

void TBitSet::getSequences(vector<vector<int>> &sequences, int maxlen) {
    vector<int> sequence;
    recursiveGetSequences(0, sequence, sequences, maxlen);
}

bool TBitSet::unionWith(TBitSet &other) {
    vector<vector<int>> sequences;
    other.getSequences(sequences);
    bool result = false;
    for (auto &seq: sequences)
        if (addSequence(seq))
            result=true;
    return result;
}

bool TBitSet::equal(TBitSet *other) {
    return (dim==other->dim)&&(size==other->size)&&(words==other->words);
}

void TBitSet::set(TBitSet *other) {
    dim=other->dim;
    size=other->size;
    words=other->words;
}

void TBitSet::concatTwo(TBitSet &begins, TBitSet &ends) {
    vector<vector<int>> sequencesBeg,sequencesEnd;
    begins.getSequences(sequencesBeg);
    ends.getSequences(sequencesEnd, dim-begins.dim);
    for (auto & begSeq:sequencesBeg)
        for (auto & endSeq:sequencesEnd)
        {
            vector<int> seq = begSeq;
            seq.insert(seq.end(), endSeq.begin(), endSeq.end());
            addSequence(seq);
        }
}
