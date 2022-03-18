#include <iostream>
#include "TokenSet.h"
#include "Rules.h"
#include "Grammar.h"
#include "GramSourceSimple.h"
#include "TTokenSet.h"

Grammar grammar;

int main() {
    GramSourceSimple simpleSource(&grammar);
    //simpleSource.load({"Wyrazenie -> liczba + Wyrazenie","Wyrazenie -> liczba"});
    //simpleSource.load({"E->a W b X Y c d Z","W->w","X->x","Y->y","Z->z"});
    //simpleSource.load({"E->B A C","A->a","A->","B->b","C->c"});
    simpleSource.load({"E-> A c B d","A->a","A->","B->b"});
    //simpleSource.load({"Wyrażenie -> liczba OpcjonalnePlusWyrażenie","OpcjonalnePlusWyrażenie -> ","OpcjonalnePlusWyrażenie -> '+' Wyrażenie"})
    grammar.print(simpleSource.names);
    grammar.makeFirstSets();
    grammar.makeFollowSets();
    grammar.makeFirstSets_k(2);
    grammar.makeFollowSets_k(2);
    cout<<"First:"<<endl;
    for (int i=0; i<grammar.First.size(); i++) {
        cout << i << ":";
        grammar.First[i].print(simpleSource.names);
        cout << endl;
    }
    cout<<"Follow:"<<endl;
    for (int i=0; i<grammar.Follow.size(); i++) {
        cout << i << ":";
        grammar.Follow[i].print(simpleSource.names);
        cout << endl;
    }
    cout<<"First k:"<<endl;
    for (int i=0; i<grammar.Firstk.size(); i++) {
        cout << i << ":";
        grammar.Firstk[i].print(simpleSource.names);
        cout << endl;
    }
    cout<<"Follow k:"<<endl;
    for (int i=0; i<grammar.Followk.size(); i++) {
        cout << i << ":";
        grammar.Followk[i].print(simpleSource.names);
        cout << endl;
    }
    cout <<flush;
    return 0;
}
