#pragma once

#include <iostream>
#include "parser.h"

using namespace std;

//---------------------------------
//          constructor
//---------------------------------
parser::parser(){};



//---------------------------------
//          chooseProd()
//---------------------------------

int parser::chooseProd(token topToken, token inputToken){
    
    // for early escape check
    bool got_hit = false;
    int hit;
     
    for(int i = 0; i < GR_NUM_PRODS; i++){  
        
        if(topToken.tokId == GR_PROD[i][GR_LHS_NDX]){

            if(!got_hit){
                hit = GR_PROD[i][GR_LHS_NDX];     
            }
            got_hit = true;
            
            if(GR_PROD[i][GR_SELECT_FNDX] == E) //if first select set index is E, default
                return i;
            
            //otherwise, loop through select set, look for a match to inputTok
            for(int j = GR_SELECT_FNDX; j <= GR_SELECT_LNDX; j++){
                
                if(GR_PROD[i][j] == inputToken.tokId) //if found, return prod num
                    return i;
            }
        }
        //since every prod is grouped by the NT on the LHS, if we find a NT that
        //matches, but can't match the inputTok to any of the select sets, once 
        //we move onto the the next prod with a different LHS, we already know we 
        //have a "Parser: no production selected for Top Token" error
        if(got_hit && (GR_PROD[i][GR_LHS_NDX] != hit))
            return P_ERR_TOPTOK;
        
    }      

    //no prod found
    return P_ERR_NOPROD;
}
                  

//------------------------------
//          pushRHS()
//------------------------------
void parser::pushRHS(int prodnum){
    token *tokptr = NULL;
    
    for(int i = GR_RHS_LNDX; i >= GR_RHS_FNDX; i--){
        
        //ignore superfluous E's
        if(GR_PROD[prodnum][i] != E){  
            tokptr = new token;
            tokptr->tokId = GR_PROD[prodnum][i];      
            tokstk.push(*tokptr);
        }
    }
    
}


//----------------------------
//          parser
//----------------------------
void parser::parse(string fn){
    
    scn.openSource(fn);

    //initialization and "0th pass" display

    stktok.tokId = NT_PROGRAM;
    tokstk.push(stktok);
    intok = scn.getNextToken(strtbl);
    print(intok);

    //PDA Main Loop
    while(!pERR && !pEOF && !pEMP){
        
        stktok = tokstk.pop();
            
        if(stktok.tokId >= FIRST_NT && stktok.tokId <= LAST_NT){    //if NT...

            int prod = chooseProd(stktok, intok);   //...try to find prod
            
            if(prod >= P_FERR && prod <= P_LERR) //if not found, error
                p_error(prod);
            else
                pushRHS(prod);
        } 
        
        //if token is terminal...
        else{
            if(stktok.tokId != intok.tokId) //top of stack should match input token
                p_error(P_ERR_MISMATCH);
            else
                intok = getNextTok();
        }       
       
        //if stack is emptied, no need to print 
        if(tokstk.empty())
            pEMP = true;  
        else
            print(intok);
    }
    
    checkFinish();     
}



//----------------------------
//      checkFinish()
//----------------------------
// only error that isn't caught earlier
void parser::checkFinish(){
    if(pEMP && !pEOF)
        p_error(P_ERR_STRAGGLERS);
    else{
        cout << "Parser: success!" << endl;
    }
}      


//---------------------------------
//     "getNextToken()" wrapper
//---------------------------------
token parser::getNextTok(){
    token tok;
    tok = scn.getNextToken(strtbl);
    if(tok.tokId == TOK_SCANERR)
        p_error(TOK_SCANERR);
    if(tok.tokId == TOK_ENDSRC)
        p_error(TOK_ENDSRC);
    return tok;
}



//---------------------------
//      print() wrapper
//---------------------------
void parser::print(token inTok){
    cout << "PARSE: " << "inTok=" << inTok.tokId << " " << getTokenString(inTok) << endl;
    tokstk.print();
    cout << endl;
}



//---------------------------------
//      exit condition checker
//---------------------------------
// sets flags, and prints err messages and the offending tokens
void parser::p_error(int errnum){
    
    if(errnum == P_ERR_TOPTOK){
        cout << "Parse Error: no production selected for Top Token" << endl;
        pERR = true;
        cout << "Top Token= " << getTokenString(stktok) << endl;
        cout << "Input Token= " << getTokenString(intok) << endl;
    }
    else if(errnum == P_ERR_NOPROD){
        cout << "Parse Error: no productions for non-terminal" << endl;   
        pERR = true;
        cout << "Top Token= " << getTokenString(stktok) << endl;
        cout << "Input Token= " << getTokenString(intok) << endl;
    }
    else if(errnum == P_ERR_MISMATCH){
        cout << "Parse Error: input token found, but Top Token expected" << endl;
        pERR = true;
        cout << "Top Token= " << getTokenString(stktok) << endl;
        cout << "Input Token= " << getTokenString(intok) << endl;
    }
    else if(errnum == TOK_SCANERR){ 
        cout << "Parse Error: scan error reported" << endl;
        pERR = true;
        cout << "Top Token= " << getTokenString(stktok) << endl;
        cout << "Input Token= " << getTokenString(intok) << endl;
    }
    else if(errnum == TOK_ENDSRC){
        pEOF = true;
        //need to know if the stack is empty or not before it's an actual error
        if(!tokstk.empty()){
            cout << "Parse Error: unexpected end of source" << endl;
            pERR = true;
            cout << "Top Token= " << getTokenString(stktok) << endl;
            cout << "Input Token= " << getTokenString(intok) << endl; 
        }
    }
    else if(errnum == P_ERR_STRAGGLERS){
        cout << "Parse Error: unexpected tokens in source past end of program" << endl;
    }
}

 
