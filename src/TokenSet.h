//
// Created by andrzej on 2020-02-04
//
#pragma once
#include <string>
#include <set>
#include "GramNames.h"

using namespace std;

class TokenSet {
private:
    bool eps=false;
    std::set<int> bits;
public:
    TokenSet(){}
    bool exists(int tokeIndex);
    bool existsEps();
    bool add(int tokeIndex);
    bool addEps();
    bool addAll(TokenSet *other);
    bool addAllButEpsilon(TokenSet *other);
    void print(const GramNames *names);
};


