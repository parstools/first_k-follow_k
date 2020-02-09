cmake_minimum_required(VERSION 3.15)
project(testsets)

set(CMAKE_CXX_STANDARD 14)

add_executable(testsets main.cpp BitSet.cpp BitSet.h Grammar.cpp Grammar.h
        GramNames.cpp GramNames.h GramSource.cpp GramSource.h GramSourceSimple.cpp GramSourceSimple.h
        IGrammar.h Rules.cpp Rules.h TBitSet.cpp TBitSet.h TokenSet.cpp TokenSet.h
        TTokenSet.cpp TTokenSet.h)