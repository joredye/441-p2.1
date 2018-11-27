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
    
    //my objects
    token stktok;
    token intok; 
    bool pEOF = false;
    bool pERR = false;
    bool pEMP = false;

    //simple helpers and wrappers
    void print(token inTok);
    void p_error(int errnum);
    token getNextTok();
        
    //suggested functions
    int chooseProd(token topToken, token inputToken);
    void pushRHS(int prodnum);
    void checkFinish(); //easily modified to return signal of success/failure
};


