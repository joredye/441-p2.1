//Joshua Reed Dyer
//2018-11-6, Tuesday

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
const int E = 199;
const int NT_PROGRAM = 200;
const int NT_DECLARATIONS = 201;
const int NT_SUBPGM_DCLS = 201;
const int NT_CMPD_STMT = 202;
const int NT_ID_LIST = 203;
const int NT_TYPE = 204;
const int NT_STD_TYPE = 205;
const int NT_SUBPGM_DCL = 206;
const int NT_SUBPGM_HEAD = 207;
const int NT_ARGS = 208;
const int NT_PARM_LIST = 209;
const int NT_OPT_STMTS = 210;
const int NT_STMT_LIST = 211;
const int NT_STMT = 212;
const int NT_END_FOR = 213;
const int NT_VARIABLE = 214;
const int NT_VAR_END = 215;
const int NT_PROC_STMT = 216;
const int NT_PROC_STMT_END = 217;
const int NT_EXPR_LIST = 218;
const int NT_EXPR = 219;
const int NT_EXPR_END = 220;
const int NT_RELOP = 221;
const int NT_SIMPLE_EXPR = 222;
const int NT_ADD_OP = 223;
const int NT_TERM = 224;
const int NT_MUL_OP = 225;
const int NT_FACTOR = 226;
const int NT_FACTOR_END = 227;
const int NT_SIGN = 228;


const int NUM_PRODS = 24;        // change this!!
const int PROD_LEN = 9;         // do NOT change this


const int PROD[NUM_PRODS][PROD_LEN] = {

	//0
        {NT_PROGRAM, TOK_PROGRAM, TOK_IDENT, TOK_SEMIC, NT_DECLARATIONS, NT_SUBPGM_DCLS, NT_CMPD_STMT, TOK_PERIOD, E}, 

        //1
	{NT_ID_LIST, TOK_IDENT, E, E, E, E, E, E, E },
	{NT_ID_LIST, NT_ID_LIST, TOK_COMMA, TOK_IDENT, E, E, E, E, E },
        
        //2
        {NT_DECLARATIONS, NT_DECLARATIONS, TOK_VAR, NT_ID_LIST, TOK_COLON, NT_TYPE, TOK_SEMIC, E, E},
        {NT_DECLARATIONS, E, E, E, E, E, E, E, E},
        
        //3 
        {NT_TYPE, NT_STD_TYPE,  E,  E,  E,  E,  E,  E,  E},
        {NT_TYPE, TOK_ARRAY, TOK_LBRKT, TOK_INT_LIT, TOK_DOTDOT, TOK_INT_LIT, TOK_RBRKT, TOK_OF, NT_STD_TYPE},

        //4
        {NT_STD_TYPE, TOK_INTEGER, E, E, E, E, E, E, E},
        {NT_STD_TYPE, TOK_REAL   , E, E, E, E, E, E, E},
        {NT_STD_TYPE, TOK_STRING , E, E, E, E, E, E, E},
        
        //5
        {NT_SUBPGM_DCLS, NT_SUBPGM_DCLS, NT_SUBPGM_DCL, TOK_SEMIC, E, E, E, E, E},
        {NT_SUBPGM_DCLS, E, E, E, E, E, E, E, E},
        
        //6
        {NT_SUBPGM_DCL, NT_SUBPGM_HEAD, NT_DECLARATIONS, NT_CMPD_STMT, E, E, E, E, E},
        
        //7 
        {NT_SUBPGM_HEAD, TOK_FUNCTION, TOK_IDENT, NT_ARGS, TOK_COLON, NT_STD_TYPE, TOK_SEMIC, E, E},
        {NT_SUBPGM_HEAD, TOK_PROCEDURE, TOK_IDENT, NT_ARGS, TOK_SEMIC, E, E, E, E},
        
        //8
        {NT_ARGS, TOK_LEFTPAR, NT_PARM_LIST, TOK_RIGHTPAR, E, E, E, E, E},
        {NT_ARGS, E, E, E, E, E, E, E, E},
        
        //9
        {NT_PARM_LIST, NT_ID_LIST, TOK_COLON, NT_TYPE, E, E, E, E, E},
        {NT_PARM_LIST, NT_PARM_LIST, TOK_SEMIC, NT_ID_LIST, TOK_COLON, NT_TYPE, E, E, E},
        
        //10
        {NT_CMPD_STMT, TOK_BEGIN, NT_OPT_STMTS, TOK_END, E, E, E, E, E},
        
        //11
        {NT_OPT_STMTS, NT_STMT_LIST, E, E, E, E, E, E, E},
        {NT_OPT_STMTS, E, E, E, E, E, E, E, E},
        
        //12
        {NT_STMT_LIST, NT_STMT, E, E, E, E, E, E, E},
        {NT_STMT_LIST, NT_STMT_LIST, TOK_SEMIC, NT_STMT, E, E, E, E, E}     
};

