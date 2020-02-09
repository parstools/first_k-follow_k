//
// Created by andrzej on 2/4/20.
//
#include <iostream>
#include "Rules.h"

void RuleElem::print(const GramNames *names) {
    if (kind==ekTerminal)
        cout <<names->termNames[number]<<" ";
    else
        cout <<names->nontermNames[number]<<" ";
}

void OneRule::print(int ntIndex, const GramNames *names) {
    cout << names->nontermNames[ntIndex] << "->";
    for (int i=0; i<v.size(); i++)
        v[i].print(names);
    cout << endl;
}