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
int chooseProd(token topToken, token inputToken){
    
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
            return GR_ERR_TOPTOK;
        
    }      
    
    //no prod found
    return GR_ERR_NOPROD;

}
                  



    /*
pushRHS(prodNdx)
push the tokens on the RHS of the production indexed by the given index: remember,
push them in reverse order:
N -> aZb : push(b), push(Z), push(a)
    */ 


//---------------------------------
//          parser
//---------------------------------
void parser::parse(string fn){
    cout << "enters parse" << endl;
    scn.openSource(fn);
    token tok = scn.getNextToken(strtbl);
    
    tokstk.push(tok);
    
    tokstk.print();
    

}
