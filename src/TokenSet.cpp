//
// Created by andrzej on 2020-02-04
//
#include "iostream"
#include "TokenSet.h"

bool TokenSet::exists(int tokeIndex) {
    return bits.get(tokeIndex);
}

bool TokenSet::existsEps() {
    return eps;
}
bool TokenSet::add(int tokeIndex) {
    return bits.set(tokeIndex);
}
bool TokenSet::addEps() {
    bool res = !eps;
    eps = true;
    return res;
}
bool TokenSet::addAll(TokenSet *other) {
    bool res = addAllButEpsilon(other);
    if (!eps && other->eps)
        res = true;
    eps |= other->eps;
    return res;
}

bool TokenSet::addAllButEpsilon(TokenSet *other) {
    return bits.orset(other->bits);
}

void TokenSet::print(const GramNames *names) {
    if (eps)
        cout << "eps ";
    for (int i=0; i<min(int(names->termNames.size()),bits.getSize()); i++)
    {
        if (bits.get(i))
            cout << names->termNames[i] <<" ";
    }
}