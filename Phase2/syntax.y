%{
    #include <cstdio>
    #include <cstdlib>
    #include "lexLib.hpp" 
    #include "symtable.h"
    #include <string>
    #include "yaccHeader.hpp"
    int yylex();
    FILE* yacc_out;
    extern int yylineno;
    extern char* yytext;
    int scope = 0;
    int max_scope = 0;
    extern SymbolTable symbolTable;  
    
%}

%start program

%union {
    char* stringConst;
    int intConst;
    double realConst;
    struct expr* exprV;
    class Symbol* symbol_P ;
}
%initial-action
{
    yacc_out = fopen("yacc_output.txt", "w");
};

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
%token NEGATIVE_VAL

%right EQUALS
%left OR
%left AND
%nonassoc DOUBLE_EQUALS NOT_EQUALS
%nonassoc LESS LESS_EQUALS GREATER GREATER_EQUALS
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%left NOT PLUS_PLUS MINUS_MINUS NEGATIVE_VAL
%left PERIOD DOUBLE_PERIOD
%left LEFT_PARENTHESIS LEFT_BRACKET
%left RIGHT_PARENTHESIS RIGHT_BRACKET

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%type <symbol_P> expression 
%type <symbol_P> term
%type <symbol_P> assignexpr
%type <symbol_P> primary
%type <symbol_P> lvalue
%type <symbol_P> member
%type <symbol_P> call
%type <symbol_P> callsuffix
%type <symbol_P> normcall
%type <symbol_P> methodcall
%type <symbol_P> elist
%type <symbol_P> indexed
%type <symbol_P> indexedelem
%type <symbol_P> openblock
%type <symbol_P> block
%type <symbol_P> funcdef
%type <symbol_P> const
%type <symbol_P> idlist
%type <symbol_P> ifstmt
%type <symbol_P> whilestmt
%type <symbol_P> forstmt
%type <symbol_P> returnstmt

%%

program:    stmts                                       { fprintf(yacc_out,"liststmt -> stmt\n"); fclose(yacc_out);}
            |/* empty */                              { fprintf(yacc_out,"empty program\n"); fclose(yacc_out);}
            ;

stmts:      stmt                                        { fprintf(yacc_out,"liststmt -> liststmt stmt\n");}
            | stmts stmt                                { fprintf(yacc_out,"liststmt -> stmt\n");}
            ;

stmt:       expression SEMICOLON                        { fprintf(yacc_out,"stmt -> expr;\n");}
            | ifstmt                                    { fprintf(yacc_out,"stmt -> ifstmt;\n");}
            | whilestmt                                 { fprintf(yacc_out,"stmt -> whilestmt;\n");}
            | forstmt                                   { fprintf(yacc_out,"stmt -> forstmt;\n");}
            | returnstmt                                { fprintf(yacc_out,"stmt -> returnstmt;\n");}
            | BREAK SEMICOLON                           { fprintf(yacc_out,"stmt -> breakstmt;\n");}
            | CONTINUE SEMICOLON                        { fprintf(yacc_out,"stmt -> continuestmt;\n");}
            | block                                     { fprintf(yacc_out,"stmt -> blockstmt;\n");} 
            | funcdef                                   { fprintf(yacc_out,"stmt -> functstmt;\n");}
            | SEMICOLON                                 { fprintf(yacc_out,"stmt -> semicolon;\n");}
            ;

expression: assignexpr                                  { fprintf(yacc_out,"expr -> assignexpr\n");}
          | term                                        { fprintf(yacc_out,"expr -> term\n");}
          | expression PLUS expression                  { fprintf(yacc_out,"expr -> +\n");}
          | expression MINUS expression                 { fprintf(yacc_out,"expr -> -\n");}
          | expression MULTIPLY expression              { fprintf(yacc_out,"expr -> *\n");}
          | expression DIVIDE expression                { fprintf(yacc_out,"expr -> /\n");}
          | expression MOD expression                   { fprintf(yacc_out,"expr -> %\n");}
          | expression DOUBLE_EQUALS expression         { fprintf(yacc_out,"expr -> ==\n");}
          | expression NOT_EQUALS expression            { fprintf(yacc_out,"expr -> !=\n");}
          | expression LESS expression                  { fprintf(yacc_out,"expr -> <\n");}
          | expression GREATER expression               { fprintf(yacc_out,"expr -> >\n");}
          | expression LESS_EQUALS expression           { fprintf(yacc_out,"expr -> <=\n");}
          | expression GREATER_EQUALS expression        { fprintf(yacc_out,"expr -> >=\n");}
          | expression AND expression                   { fprintf(yacc_out,"expr -> AND\n");}
          | expression OR expression                    { fprintf(yacc_out,"expr -> OR\n");} 
          ;


term:       LEFT_PARENTHESIS expression RIGHT_PARENTHESIS     { fprintf(yacc_out,"expr -> (term)\n");}
            | MINUS expression %prec NEGATIVE_VAL             { fprintf(yacc_out,"expr -> -term\n");}
            | NOT expression                                  { fprintf(yacc_out,"expr -> !term\n");}
            | PLUS_PLUS lvalue                          {   if ($2 != NULL && $2->type != USERFUNC && $2->type != LIBFUNC) {
                                                                 fprintf(yaccout, "term -> PLUS_PLUS lvalue\n");}
                                                             else if ($2->type == USERFUNC || $2->type == LIBFUNC) {
                                                                 fprintf(stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
             | lvalue PLUS_PLUS                          {   if ($1 != NULL && $1->type != USERFUNC && $1->type != LIBFUNC) {
                                                                 fprintf(yaccout, "term -> lvalue PLUS_PLUS\n");}
                                                             else if ($1->type == USERFUNC || $1->type == LIBFUNC) {
                                                                 fprintf(stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
             | MINUS_MINUS lvalue                        {   if ($2 != NULL && $2->type != USERFUNC && $2->type != LIBFUNC) {
                                                                 fprintf(yaccout, "term -> MINUS_MINUS lvalue\n");}
                                                             else if ($2->type == USERFUNC || $2->type == LIBFUNC) {
                                                                 fprintf(stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
             | lvalue MINUS_MINUS                        {   if ($1 != NULL && $1->type != USERFUNC && $1->type != LIBFUNC) {
                                                                 fprintf(yaccout, "term -> lvalue MINUS_MINUS\n");}
                                                             else if ($1->type == USERFUNC || $1->type == LIBFUNC) {
                                                                 fprintf(stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
            | primary                                         { fprintf(yacc_out,"expr -> primary\n");}
            ;

assignexpr: lvalue EQUALS expression                          { }

primary:    lvalue                                      { fprintf(yacc_out,"primary -> lvalue\n")}
            | call                                      { fprintf(yacc_out,"primary -> call\n")}
            | objectdef                                 { fprintf(yacc_out,"primary -> objectdef\n")}
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS{ fprintf(yacc_out,"primary -> (funcdef)\n")}
            | const                                     { fprintf(yacc_out,"primary -> const\n")}
            ;


lvalue:     ID                                          { }                                                                   
            | LOCAL ID                                  { symbolTable.local_lvalue($2,scope,yylineno,1);
                                                          fprintf(yacc_out,"lvalue -> id\n");}
            | DOUBLE_COLON ID                           { fprintf(yacc_out,"lvalue -> id\n");}
            | member                                    { fprintf(yacc_out,"lvalue -> id\n");}
            ;

member:     lvalue PERIOD ID                            { }
            | lvalue LEFT_BRACKET expression RIGHT_BRACKET    { }
            | call PERIOD ID                            { }
            | call LEFT_BRACKET expression RIGHT_BRACKET      { }
            ;

call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   { }
            | lvalue callsuffix                             { }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { }
            ;

callsuffix: normcall                                    { }
            | methodcall                                { }
            ;

normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    { }

methodcall: DOUBLE_PERIOD ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   { }

elist:      expression                                        { }
            | elist COMMA expression                          { }
            ;

objectdef:  LEFT_BRACKET elist RIGHT_BRACKET            { }
            | LEFT_BRACKET indexed RIGHT_BRACKET        { }
            | LEFT_BRACKET RIGHT_BRACKET                { }
            ;

indexed:    indexedelem                                 { }
            | indexedelem COMMA indexedelem             { }

indexedelem:LEFT_CBRACKET expression COLON expression RIGHT_CBRACKET    { }

openblock:  LEFT_CBRACKET stmt                          { }
            | openblock stmt                            { }
            ;

block:      LEFT_CBRACKET                               { } 
            RIGHT_CBRACKET { } { }
            | openblock RIGHT_BRACKET { } { }
            ;

funcdef:    FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block { }
            | FUNCTION LEFT_PARENTHESIS RIGHT_PARENTHESIS block         { }
            ;

const:      INT                                         { }
            | REAL                                      { }
            | STRING                                    { }
            | NIL                                       { }
            | TRUE                                      { }
            | FALSE                                     { }
            ;

idlist:     ID                                          { }
            | idlist COMMA ID                           { }
            ;   

ifstmt: IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS stmt %prec LOWER_THAN_ELSE {}
       | IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS stmt ELSE stmt {}
       ;

whilestmt:  WHILE LEFT_PARENTHESIS expression RIGHT_PARENTHESIS stmt      { }

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expression SEMICOLON elist RIGHT_PARENTHESIS stmt    { }

returnstmt: RETURN expression SEMICOLON                        { }  
            | RETURN SEMICOLON                           { }
            ;

%%


