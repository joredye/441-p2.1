#pragma once

#include <iostream>
#include "parser.h"

using namespace std;

//---------------------------------
//          constructor
//---------------------------------
parser::parser(){};

//---------------------------------
//          chooseProd
//---------------------------------
    /*
    chooseProd(topToken, inputToken): returns: index into the grammar array of the
production chosen, or return an error code (see 2 of the error messages above).
Search down the list to find the first production where the LHS equals the topToken.
Search the Select Set Members of a production to see if any matches the given
inputToken; or if the first member of the Select Set is E (meaning this is the default
token).
    */
int parser::chooseProd(token topToken, token inputToken){
    
    //loop through grammar table, comparing tok from stack to LHS 
    bool matched = false;
    int the_match;
     
    for(int i = 0; i < GR_NUM_PRODS; i++){
        
        if(topToken.tokId == GR_PROD[i][GR_LHS_NDX]){
            
            if(!matched){
                //record the first matching GR_PROD[][] token for early escape check
                the_match = GR_PROD[i][GR_LHS_NDX];           
            }
            matched = true;
            
            //if first select set index is E, default prod
            if(GR_PROD[i][GR_SELECT_FNDX] == E)
                return i;
            
            //otherwise, loop through select set, look for a match to inputTok
            for(int j = GR_SELECT_FNDX; j <= GR_SELECT_LNDX; j++){
                
                //if you find it, great: return the production number
                if(GR_PROD[i][j] == inputToken.tokId)
                    return i;
            }
        }
        //since every prod is grouped by the NT on the LHS, if we find a NT that
        //matches, but can't match the inputTok to any of the select sets, once 
        //we move onto the the next prod with a different LHS, we already know we 
        //have a "Parser: no production selected for Top Token" error
        if(matched && (GR_PROD[i][GR_LHS_NDX] != the_match))
            return P_ERR_TOPTOK;
        
    }      
    
    //no prod found
    return P_ERR_NOPROD;

}
                  



    /*
pushRHS(prodNdx)
push the tokens on the RHS of the production indexed by the given index: remember,
push them in reverse order:
N -> aZb : push(b), push(Z), push(a)
    */ 

void parser::pushRHS(int prodnum){
    token *tokptr = NULL;
    
    for(int i = GR_RHS_LNDX; i >= GR_RHS_FNDX; i--){
        if(GR_PROD[prodnum][i] != E){
            tokptr = new token;
            tokptr->tokId = GR_PROD[prodnum][i];      
            tokstk.push(*tokptr);
        }
    }
    
}


//---------------------------------
//          parser
//---------------------------------
void parser::parse(string fn){
    
    scn.openSource(fn);
    int k = 0;
    int num_loops = 3;
    bool firstpass = true; 

    token start;
    //start.tokId = NT_PROGRAM;
    //tokstk.push(start);
    
    token stktok;
    token intok ;   //= scn.getNextToken(strtbl);
    
    //PDA Main Loop
    for(k; k = num_loops; k++){
        //cout << "top " << k << ": " << endl;
        
        if(firstpass){
            start.tokId = NT_PROGRAM;
            tokstk.push(start);
            intok = scn.getNextToken(strtbl);
        }
        print(intok);
        
        stktok = tokstk.pop();
        
        //if token is nonterminal...
        if(stktok.tokId >= FIRST_NT && stktok.tokId <= LAST_NT){
         
            //...try to find a prod
            int prod = chooseProd(stktok, intok);
            
            //################ Need better prod detection?
            //  edge cases? TOK_SCANERR? 
            if(prod >= P_FERR && prod <= P_LERR){
                p_error(prod);
            }
            else{
                pushRHS(prod);
            }
        }
        
        //if token is terminal...
        else{
            
            //if first time through, don't need to scan next token
            /*
            if(!firstpass){
                intok = scn.getNextToken(strtbl);
            }
            */
            firstpass = false;
            
            
            if(stktok.tokId != intok.tokId){
                p_error(P_ERR_MISMATCH);
            }

        }
        
        cout << "bottom " << k << ": " << endl;
        print(intok);
    }
     
}





//---------------------------
//          print()
//---------------------------
void parser::print(token inTok){
    cout << "PARSE: " << "inTok=" << inTok.tokId << " " << getTokenString(inTok) << endl;
    tokstk.print();
    cout << endl;
}


//---------------------------------
//          grammar error
//---------------------------------
void parser::p_error(int prodnum){
    if(prodnum == P_ERR_TOPTOK){
        cout << "Parse Error: no production selected for Top Token" << endl;
    }
    else if(prodnum == P_ERR_NOPROD){
        cout << "Parse Error: no productions for non-terminal" << endl;   
    }
    else if(prodnum == P_ERR_MISMATCH){
        cout << "Parse Error: input token found, but Top Token expected" << endl;
    }
    
    pERR = true;
}

 
