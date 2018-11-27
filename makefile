.RECIPEPREFIX = >

p.out: main.cpp parser.h parser.cpp token.h token.cpp tokStack.h tokStack.cpp StringTableEntry.h StringTable.h StringTable.cpp scanner.h scanner.cpp grammar.h  
>g++ -std=c++11 -o p.out main.cpp parser.h parser.cpp token.h token.cpp tokStack.h tokStack.cpp StringTableEntry.h StringTable.h StringTable.cpp scanner.h scanner.cpp grammar.h 
