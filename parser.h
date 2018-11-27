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
    
    bool pEOF;
    bool pERR;
    bool pEMP;

    //my functions
    void print(token inTok);
    void p_error(int prodnum);

        
    int chooseProd(token topToken, token inputToken);
    void pushRHS(int prodnum);
    int checkFinish(/*?*/);
     
};


//THERE COULD BE OTHERS
