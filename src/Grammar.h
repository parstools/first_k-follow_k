//
// Created by Andrzej on 2020-02-04.
//
#pragma once
#include "TokenSet.h"
#include "TTokenSet.h"
#include "Rules.h"
#include "GramSource.h"
#include "IGrammar.h"

class Grammar: public IGrammar {
    GramSource *source;
public:
    int tokentCount = 0;
    vector<RulesForNonterminal> rulesByNonterminal;
    vector<TokenSet> First;
    vector<TokenSet> Follow;
    vector<TTokenSet> Firstk;
    vector<TTokenSet> Followk;
    void makeFirstSets();
    void makeFirstSets_k(int k);
    void makeFollowSets();
    void makeFollowSets_k(int k);
    bool addFirstOfRule(TokenSet &outSet, OneRule& rule, int startIndex=0);
    bool addFirstOfRule_k(TTokenSet &outSet, OneRule& rule, int startIndex=0);
    bool checkLL1();
    void print(const GramNames *names);
    void addNonTerminal();
    void addTerminal() {tokentCount++;};
    void addRule(int nonTerminal, const OneRule& rule);
};
