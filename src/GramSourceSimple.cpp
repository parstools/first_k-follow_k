//
// Created by andrzej on 2/4/20.
//
#include "iostream"
#include  <unordered_map>
#include "GramSourceSimple.h"

string trim(const string& str)
{
    const string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

string trimLeft(const string& str)
{
    const auto strBegin = str.find_first_not_of(" \t");
    if (strBegin == string::npos)
        return ""; // no content
    return str.substr(strBegin, str.length() - strBegin);
}

string trimRight(const string& str)
{
    const auto strEnd = str.find_last_not_of(" \t");
    if (strEnd == string::npos)
        return ""; // no content
    return str.substr(0, strEnd + 1);
}

string getNTbefore(string line)
{
    auto pos = line.find("->");
    if (pos==string::npos) return "";
    string ntname = line.substr(0,pos);
    return trim(ntname);
}

bool isWS(char c) {
    return (c==' ' || c=='\t');
}

vector<string> getRuleStr(string line)
{
    vector<string> ruleElemsStr;
    size_t pos = line.find("->");
    if (pos==string::npos) ruleElemsStr;
    pos+=2;
    while (pos<line.length())
    {
        while (pos < line.length() && (isWS(line[pos])))
            pos++;
        size_t posEnd = pos + 1;
        while (posEnd < line.length() && (!isWS(line[posEnd])))
            posEnd++;
        ruleElemsStr.push_back(line.substr(pos, posEnd - pos));
        pos = posEnd+1;
    }
    return ruleElemsStr;
}

void GramSourceSimple::load(vector<string> lines){
    delete names;
    names = new GramNames;
    unordered_map<string,int> ntmap;
    for (string line: lines)
    {
        string ntname = getNTbefore(line);
        if (ntname=="") continue;
        auto it = ntmap.find(ntname);
        if (it == ntmap.end()) {
            ntmap[ntname]=names->nontermNames.size();
            names->nontermNames.push_back(ntname);
            gramIntf->addNonTerminal();
        }
    }
    unordered_map<string,int> tmap;
    for (string line: lines)
    {
        string ntname = getNTbefore(line);
        if (ntname=="") continue;
        vector<string> ruleElemsStr = getRuleStr(line);
        OneRule rule;
        for (string elemStr: ruleElemsStr)
        {
            RuleElem elem;
            auto it = ntmap.find(elemStr);
            if (it != ntmap.end())
            {
                elem.kind = ekNonterminal;
                elem.number = it->second;
                rule.v.push_back(elem);
            }
            else {
                auto it2 = tmap.find(elemStr);
                if (it2 != tmap.end())
                {
                    elem.kind = ekTerminal;
                    elem.number = it2->second;
                    rule.v.push_back(elem);
                }
                else
                {
                    tmap[elemStr]=names->termNames.size();
                    elem.kind = ekTerminal;
                    elem.number = names->termNames.size();
                    rule.v.push_back(elem);
                    names->termNames.push_back(elemStr);
                    gramIntf->addTerminal();
                }
            }
        }
        auto it3 = ntmap.find(ntname);
        gramIntf->addRule(it3->second, rule);
    }
}