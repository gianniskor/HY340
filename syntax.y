%{
    int yylex(void);
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;    
%}

%start program

%union {
    char *stringConst;
    int intConst;
    double realConst;
    /*
        struct gia list kai symtable
    */
}

%token <stringConst> ID STRING
%token <intConst> INT 
%token <realConst> REAL 

%token LEFT_PARENTHESIS "("
%token RIGHT_PARENTHESIS ")"
%token LEFT_BRACKET "["
%token RIGHT_BRACKET "]"
%token LEFT_CBRACKET "{"
%token RIGHT_CBRACKET "}"

%token SEMICOLON ";"
%token COMMA ","
%token COLON ":"
%token DOUBLE_COLON "::"
%token PERIOD "."
%token DOUBLE_PERIOD ".."

%token PLUS "+"
%token MINUS "-"
%token MULTIPLY "*"
%token DIVIDE "/"
%token PLUS_PLUS "++"
%token MINUS_MINUS "--"
%token MOD "%"
%token EQUALS "="

%token DOUBLE_EQUALS "=="
%token NOT_EQUALS "!="
%token LESS "<"
%token GREATER ">"
%token LESS_EQUALS "<="
%token GREATER_EQUALS ">="

%token AND "and"
%token NOT "not"
%token OR "or"

%token IF "if"
%token ELSE "else"
%token WHILE "while"
%token TRUE "true"
%token FALSE "false"
%token NIL "nil"
%token RETURN "return"
%token FUNCTION "function"
%token BREAK "break"
%token CONTINUE "continue"
%token LOCAL "local"
%token FOR "for"

%right EQUALS
%left OR
%left AND
%nonassoc EQUALS NOT_EQUALS
%nonassoc LESS LESS_EQUALS GREATER GREATER_EQUALS
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%left NOT PLUS_PLUS MINUS_MINUS NEGATIVE_VAL
%left PERIOD DOUBLE_PERIOD
%left LEFT_PARENTHESIS LEFT_BRACKET
%left RIGHT_PARENTHESIS RIGHT_BRACKET




