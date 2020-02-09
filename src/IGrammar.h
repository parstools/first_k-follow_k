//
// Created by andrzej on 2020-2-5
//
#pragma once
#include "Rules.h"

class IGrammar {
public:
    virtual void addNonTerminal() = 0;
    virtual void addTerminal() = 0;
    virtual void addRule(int nonTerminal, const OneRule& rule) = 0;
};
