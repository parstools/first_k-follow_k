//
// Created by andrzej on 2020-2-4
//
#pragma once
#include "GramNames.h"
#include "IGrammar.h"

class GramSource {
protected:
    IGrammar *gramIntf;
public:
    GramNames *names = nullptr;
    GramSource(IGrammar *gramIntf):gramIntf(gramIntf){}
    ~GramSource();
};
