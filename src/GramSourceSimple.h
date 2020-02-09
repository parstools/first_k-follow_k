//
// Created by andrzej on 2020-2-4
//
#pragma once
#include "GramSource.h"

class GramSourceSimple: public GramSource {
public:
    GramSourceSimple(IGrammar *gramIntf):GramSource(gramIntf){};
    void load(vector<string> lines);
};
