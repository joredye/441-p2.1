#pragma once
#include "scanner.h"
#include "StringTable.h"
#include "tokStack.h"
#include "grammar.h"

class parser{

    public:
    parser();
    void parse(string fn);    

    private:
    
    scanner scn;
    StringTable strtbl;
    tokStack tokstk;
        
    //parser(scanner _scn, StringTable _strtbl, tokStack _tokstk) : scn(_scn), strtbl(_strtbl), tokstk(_tokstk){};
    
    int chooseProd(token topToken, token inputToken);
    void pushRHS(int prodnum);
    int checkFinish(/*?*/);
     
};


//THERE COULD BE OTHERS
