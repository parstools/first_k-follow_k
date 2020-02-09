#pragma once
#include <string>
#include <vector>
#include "GramNames.h"

using namespace std;

enum ElemKind{ ekTerminal,ekNonterminal };

struct RuleElem {
    ElemKind kind;
    int number;
    void print(const GramNames *names);
};

struct OneRule {
    vector<RuleElem> v;
    void print(int ntIndex, const GramNames *names);
};

typedef vector<OneRule> RulesForNonterminal;