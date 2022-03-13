//
// Created by andrzej on 2/4/20.
//
#include <iostream>
#include "Grammar.h"

void Grammar::makeFirstSets() {
    bool changed;
    First.clear();
    First.resize(rulesByNonterminal.size());
    do {
        changed = false;
        for (int Xidx=rulesByNonterminal.size() - 1; Xidx >= 0; Xidx--) {
            RulesForNonterminal &rules = rulesByNonterminal[Xidx];
            for (int XruleIdx= rules.size() - 1; XruleIdx >= 0; XruleIdx--) {
                bool reschanged = addFirstOfRule(First[Xidx], rules[XruleIdx]);
                if (reschanged)
                    changed = true;
            }
        }
    }
    while (changed);
}

void Grammar::makeFirstSets_k(int k) {
    bool changed;
    Firstk.clear();
    for (int i=0; i<rulesByNonterminal.size(); i++)
    {
        TTokenSet tokenSet(k, tokentCount);
        Firstk.push_back(tokenSet);
    }
    do {
        changed = false;
        for (int Xidx=rulesByNonterminal.size() - 1; Xidx >= 0; Xidx--) {
            RulesForNonterminal &rules = rulesByNonterminal[Xidx];
            for (int XruleIdx= rules.size() - 1; XruleIdx >= 0; XruleIdx--) {
                bool reschanged = addFirstOfRule_k(Firstk[Xidx], rules[XruleIdx]);
                if (reschanged)
                    changed = true;
            }
        }
    }
    while (changed);
}


void Grammar::makeFollowSets() {
    Follow.clear();
    Follow.resize(rulesByNonterminal.size());
    Follow[0].addEps();
    bool changed;
    do {
        changed = false;
        for (int Aidx=0; Aidx < rulesByNonterminal.size(); Aidx++) {
            RulesForNonterminal &rules = rulesByNonterminal[Aidx];
            for (int ruleIdx=0; ruleIdx < rules.size(); ruleIdx++) {
                for (int Bidx=0; Bidx < rules[ruleIdx].v.size(); Bidx++) {
                    RuleElem elem = rules[ruleIdx].v[Bidx];
                    if (elem.kind != ekNonterminal) continue;
                    if (addFirstOfRule(Follow[elem.number], rules[ruleIdx], Bidx + 1))
                        changed = true;
                }
            }
        }
    }
    while (changed);
}

void Grammar::makeFollowSets_k(int k) {
    Followk.clear();
    for (int i=0; i<rulesByNonterminal.size(); i++)
    {
        TTokenSet tokenSet(k, tokentCount);
        Followk.push_back(tokenSet);
    }
    Followk[0].eps = true;
    bool changed;
    do {
        changed = false;
        for (int Aidx=0; Aidx < rulesByNonterminal.size(); Aidx++) {
            RulesForNonterminal &rules = rulesByNonterminal[Aidx];
            for (int ruleIdx=0; ruleIdx < rules.size(); ruleIdx++) {
                for (int Bidx=0; Bidx < rules[ruleIdx].v.size(); Bidx++) {
                    RuleElem elem = rules[ruleIdx].v[Bidx];
                    if (elem.kind != ekNonterminal) continue;
                    if (addFirstOfRule_k(Followk[elem.number], rules[ruleIdx], Bidx + 1))
                        changed = true;
                }
            }
        }
    }
    while (changed);
}

bool Grammar::addFirstOfRule(TokenSet &outSet, OneRule& rule, int startIndex) {
    bool changed = false;
    bool isEps=true;
    for (int Yidx=startIndex; Yidx < rule.v.size(); Yidx++) {
        RuleElem Y = rule.v[Yidx];
        if (Y.kind==ekTerminal)
        {
            isEps=false;
            bool retchanged = outSet.add(Y.number);
            if (retchanged) changed=true;
            break;
        }
        else
        {
            bool retchanged = outSet.addAllButEpsilon(&First[Y.number]);
            if (retchanged) changed=true;
            if (!First[Y.number].existsEps())
            {
                isEps=false;
                break;
            }
        }
    }
    if (isEps)
    {
        bool retchanged = outSet.addEps();
        if (retchanged) changed=true;
    }
    return changed;
}

bool Grammar::addFirstOfRule_k(TTokenSet &outSet, OneRule& rule, int startIndex) {
    TTokenSet tempSet(outSet.getk(), outSet.getSize());
    tempSet.eps = true;
    for (int Yidx=startIndex; Yidx < rule.v.size(); Yidx++) {
        RuleElem Y = rule.v[Yidx];
        if (Y.kind==ekTerminal)
        {
            tempSet.append(Y.number);
        }
        else
        {
            tempSet.concat(Firstk[Y.number]);
        }
        if (!tempSet.concatenable()) break;
    }
    return outSet.unionWith(tempSet);
}

void Grammar::print(const GramNames *names)
{
    for (int i=0; i<rulesByNonterminal.size(); i++)
        for (int j=0; j<rulesByNonterminal[i].size(); j++)
        {
            rulesByNonterminal[i][j].print(i,names);
        }
}

void Grammar::addNonTerminal()
{
    RulesForNonterminal rfn;
    rulesByNonterminal.push_back(rfn);
}

void Grammar::addRule(int nonTerminal, const OneRule& rule)
{
    rulesByNonterminal[nonTerminal].push_back(rule);
}