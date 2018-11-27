#pragma once
//------------------------------------------------------------------
//                             token.h
//------------------------------------------------------------------
// Defines:
// - Token ID constants for Terminals, Non-Terminals, and Errors
// - String representations of the above Token IDs for debugging
// - Token Structure and prototypes for free functions in token.cpp
//------------------------------------------------------------------

// structure declaration and constants for a token
#include <string>
#include "StringTableEntry.h"

const int TOK_CHAR_LIT = -6;
const int TOK_REAL_LIT = -5;
const int TOK_INT_LIT = -4;
const int TOK_IDENT = -3;
const int TOK_ENDSRC = -2;
const int TOK_SCANERR = -1;
const int TOK_AND = 0;
const int TOK_ARRAY = 1;
const int TOK_BEGIN = 2;
const int TOK_BOOLEAN = 3;
const int TOK_CASE = 4;
const int TOK_CHAR = 5;
const int TOK_CONST = 6;
const int TOK_DIV = 7;
const int TOK_DO = 8;
const int TOK_DOWNTO = 9;
const int TOK_ELSE = 10;
const int TOK_END = 11;
const int TOK_EOF = 12;
const int TOK_FALSE = 13;
const int TOK_FILE = 14;
const int TOK_FOR = 15;
const int TOK_FUNCTION = 16;
const int TOK_GOTO = 17;
const int TOK_IF = 18;
const int TOK_IN = 19;
const int TOK_INTEGER = 20;
const int TOK_LABEL = 21;
const int TOK_MAXINT = 22;
const int TOK_MOD = 23;
const int TOK_NIL = 24;
const int TOK_NOT = 25;
const int TOK_OF = 26;
const int TOK_OR = 27;
const int TOK_OUTPUT = 28;
const int TOK_PACK = 29;
const int TOK_PACKED = 30;
const int TOK_PROCEDURE = 31;
const int TOK_PROGRAM = 32;
const int TOK_READ = 33;
const int TOK_READLN = 34;
const int TOK_REAL = 35;
const int TOK_RECORD = 36;
const int TOK_REPEAT = 37;
const int TOK_SET = 38;
const int TOK_STRING = 39;
const int TOK_THEN = 40;
const int TOK_TO = 41;
const int TOK_TRUE = 42;
const int TOK_TYPE = 43;
const int TOK_UNTIL = 44;
const int TOK_VAR = 45;
const int TOK_WHILE = 46;
const int TOK_WITH = 47;
const int TOK_WRITE = 48;
const int TOK_WRITELN = 49;
const int TOK_PERIOD = 50;
const int TOK_LEFTPAR = 51;
const int TOK_RIGHTPAR = 52;
const int TOK_STAR = 53;
const int TOK_COLON = 54;
const int TOK_LTHAN = 55;
const int TOK_GTHAN = 56;
const int TOK_EQUAL = 57;
const int TOK_PLUS = 58;
const int TOK_MINUS = 59;
const int TOK_SLASH = 60;
const int TOK_LBRKT = 61;
const int TOK_RBRKT = 62;
const int TOK_COMMA = 63;
const int TOK_SEMIC = 64;
const int TOK_HAT = 65;
const int TOK_NOT_EQ = 66;
const int TOK_LT_EQ = 67;
const int TOK_GT_EQ = 68;
const int TOK_ASSIGN = 69;
const int TOK_DOTDOT = 70;

// Grammar Non-Terminal Tokens
const int E = 199;
const int NT_PROGRAM = 200;
const int NT_DECLARATIONS = 201;
const int NT_SUBPGM_DCLS = 202;
const int NT_CMPD_STMT = 203;
const int NT_ID_LIST = 204;
const int NT_ID_LIST_END = 205;
const int NT_TYPE = 206;
const int NT_STD_TYPE = 207;
const int NT_SUBPGM_DCL = 208;
const int NT_SUBPGM_HEAD = 209;
const int NT_ARGS = 210;
const int NT_PARM_LIST = 211;
const int NT_PARM_LIST_END = 212;
const int NT_OPT_STMTS = 213;
const int NT_STMT_LIST = 214;
const int NT_STMT_LIST_END = 215;
const int NT_STMT = 216;
const int NT_END_FOR = 217;
const int NT_PROC_OR_ASSIGN = 218;
const int NT_VARIABLE = 219;
const int NT_VAR_END = 220;
const int NT_PROC_STMT = 221;
const int NT_PROC_STMT_END = 222;
const int NT_EXPR_LIST = 223;
const int NT_EXPR_LIST_END = 224;
const int NT_EXPR = 225;
const int NT_EXPR_END = 226;
const int NT_RELOP = 227;
const int NT_SIMPLE_EXPR = 228;
const int NT_SIMPLE_EXPR_END = 229;
const int NT_ADD_OP = 230;
const int NT_TERM = 231;
const int NT_TERM_END = 232;
const int NT_MUL_OP = 233;
const int NT_FACTOR = 234;
const int NT_FACTOR_END = 235;
const int NT_SIGN = 236;
const int FIRST_NT = E;
const int LAST_NT = NT_SIGN;



//---------------My Parser Error Constants-------------------

//matching production(s) found for the NT from the stack's top,
//but input token from scanner does not match any tokens in matching
//production(s) select set(s), and there is no default production
const int P_ERR_TOPTOK = 11630;


// input token from source file and token expected by parser do not match
const int P_ERR_MISMATCH = 11631;

// PDA stack is empty, but the source file has not been exhausted of tokens
const int P_ERR_STRAGGLERS = 11632;

// no productions are found for the NT from the top of the stack
const int P_ERR_NOPROD = 12073;


//in case I need more grammar error constants down the line...
const int P_FERR = P_ERR_TOPTOK;
const int P_LERR = P_ERR_NOPROD;




// Reserved Words & Tokens
const int NUM_RES_WORDS = 71;
const std::string RES_WORDS[NUM_RES_WORDS] = {
	"AND", "ARRAY", "BEGIN", "BOOLEAN", "CASE", "CHAR", "CONST", "DIV", "DO",
	"DOWNTO", "ELSE", "END", "EOF", "FALSE", "FILE", "FOR", "FUNCTION", "GOTO",
	"IF", "IN", "INTEGER", "LABEL", "MAXINT", "MOD", "NIL", "NOT", "OF", "OR",
	"OUTPUT", "PACK", "PACKED", "PROCEDURE", "PROGRAM", "READ", "READLN", "REAL",
	"RECORD", "REPEAT", "SET", "STRING", "THEN", "TO", "TRUE", "TYPE", "UNTIL", "VAR",
	"WHILE", "WITH", "WRITE", "WRITELN",
	".", "(", ")", "*", ":", "<", ">", "=", "+", "-", "/", "[", "]", ",", ";", "^"
	"<>", "<=", ">=", ":=", ".."
};

// other Token Ids (TOK# = 0 refers to TOK_AND) that have a negative value
const int NUM_OTHER_TOKIDS = 7;
const std::string OTHER_TOKIDS[NUM_OTHER_TOKIDS] = {
	"_uh_oh_zero", "_SCANERR", "_ENDSRC", "_IDENT", "_INT_LIT", "_REAL_LIT", "_CHAR_LIT"
};

// non-terminal tokens
const int NUM_NON_TERMS = 38;
const std::string NON_TERMINAL[NUM_NON_TERMS] = {
	"<E>","<PGM>","<DECLARATIONS>","<SUBPGM_DCLS>","<CMPD_STMT>","<ID_LIST>","<ID_LIST_END>","<DTYPE>","<STD_TYPE>","<SUBPGM_DCL>",
	"<SUBPGM_HEAD>","<ARGS>","<PARM_LIST>","<PARM_LIST_END>","<OPT_STMTS>","<STMT_LIST>","<STMT_LIST_END>","<STMT>","<END_FOR>",
	"<PROC_OR_ASSIGN>","<VARIABLE>","<VAR_END>","<PROC_STMT>","<PROC_STMT_END>","<EXPR_LIST>","<EXPR_LIST_END>","<EXPR>","<EXPR_END>",
	"<RELOP>","<SIMPLE_EXPR>","<SIMPLE_EXPR_END>","<ADD_OP>","<TERM>","<TERM_END>","<MUL_OP>","<FACTOR>","<FACTOR_END>","<SIGN>"
};

// token: represents a single word/symbol/identifier/literal from the source
struct token {
	token() { tokId = TOK_SCANERR; sref = NULL; }
	int	tokId;	          // token identifier: one of the TOK_ constants below
	StringTableRef	sref; // reference to an entry in the String Table
};

// prototypes for related free functions
void printToken(token tok);
std::string getTokenString(token tok);
