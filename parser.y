%{
    #include <cstdio>
    #include <cstdlib>
    #include <string>
    #include "symtable.h"

    extern FILE* yacout;
    extern int yyparse();
    extern int yylineno;

    int yylex();
    int scope = 0;
    int max_scope = 0;

%}

%union {
    string stringConst;
    int intConst;
    double realConst;
    struct expr* exprV;
    struct Symbol* symbol_P ;
}

%start program

%token <stringConst> ID STRING
%token <intConst> INT 
%token <realConst> REAL 

%token LEFT_PARENTHESIS
%token RIGHT_PARENTHESIS
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_CBRACKET
%token RIGHT_CBRACKET

%token SEMICOLON
%token COMMA
%token COLON
%token DOUBLE_COLON
%token PERIOD
%token DOUBLE_PERIOD

%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token PLUS_PLUS
%token MINUS_MINUS
%token MOD
%token EQUALS

%token DOUBLE_EQUALS
%token NOT_EQUALS
%token LESS
%token GREATER
%token LESS_EQUALS
%token GREATER_EQUALS

%token AND
%token NOT
%token OR

%token IF
%token ELSE
%token WHILE
%token TRUE
%token FALSE
%token NIL
%token RETURN
%token FUNCTION
%token BREAK
%token CONTINUE
%token LOCAL
%token FOR

%right EQUALS
%left OR
%left AND
%nonassoc EQUALS NOT_EQUALS
%nonassoc LESS LESS_EQUALS GREATER GREATER_EQUALS
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%left NOT PLUS_PLUS MINUS_MINUS
%left PERIOD DOUBLE_PERIOD
%left LEFT_PARENTHESIS LEFT_BRACKET
%left RIGHT_PARENTHESIS RIGHT_BRACKET

%type <exprV> expression
%type <exprV> expr
%type <exprV> term
%type <exprV> assignexpr
%type <exprV> primary
%type <exprV> lvalue
%type <exprV> member
%type <exprV> call
%type <exprV> callsuffix
%type <exprV> normcall
%type <exprV> methodcall
%type <exprV> elist
%type <exprV> indexed
%type <exprV> indexedelem
%type <exprV> openblock
%type <exprV> block
%type <exprV> funcdef
%type <exprV> const
%type <exprV> idlist
%type <exprV> ifstmt
%type <exprV> whilestmt
%type <exprV> forstmt
%type <exprV> returnstmt

%%

program:    stmts                                       { fprintf(yaccout, "program -> stmts\n");}
            |  /* empty */                              { fprintf(yaccout, "program -> EMPTY\n"); }
            ;

stmts:      stmt                                        { fprintf(yaccout, "stmts -> stmt\n"); }
            | stmts stmt                                { fprintf(yaccout, "stmts -> stmts stmt\n"); }
            ;

stmt:       expr SEMICOLON                              { fprintf(yaccout, "stmt -> expr SEMICOLON\n"); }
            | ifstmt                                    { fprintf(yaccout, "stmt -> ifstmt\n"); }
            | whilestmt                                 { fprintf(yaccout, "stmt -> whilestmt\n"); }
            | forstmt                                   { fprintf(yaccout, "stmt -> forstmt\n"); }
            | returnstmt                                { fprintf(yaccout, "stmt -> returnstmt\n"); }
            | BREAK SEMICOLON                           { fprintf(yaccout, "stmt -> BREAK\n"); }
            | CONTINUE SEMICOLON                        { fprintf(yaccout, "stmt -> CONTINUE\n"); }
            | block                                     { fprintf(yaccout, "stmt -> block\n"); } 
            | funcdef                                   { fprintf(yaccout, "stmt -> funcdef\n"); }
            ;

expression: INT                                         { fprintf(yaccout, "expression -> INT\n"); }    
            | ID                                        { fprintf(yaccout, "expression -> ID\n"); }
            | expr PLUS expr                            { fprintf(yaccout, "expression -> expr PLUS expr\n"); }
            | expr MINUS expr                           { fprintf(yaccout, "expression -> expr MINUS expr\n"); }
            | expr MULTIPLY expr                        { fprintf(yaccout, "expression -> expr MULTIPLY expr\n"); }
            | expr DIVIDE expr                          { fprintf(yaccout, "expression -> expr DIVIDE expr\n"); }
            | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS   { fprintf(yaccout, "expression -> LEFT_PARENTHESIS expr RIGHT_PARENTHESIS\n"); }
            | MINUS expr %prec NOT                      { fprintf(yaccout, "expression -> MINUS expr\n"); }
            ;

expr:       expression SEMICOLON                        { fprintf(yaccout, "expr -> expression SEMICOLON")}

term:       LEFT_PARENTHESIS expr RIGHT_PARENTHESIS     { fprintf(yaccout, "term -> LEFT_PARENTHESIS expr RIGHT_PARENTHESIS\n"); }
            | MINUS expr                                { fprintf(yaccout, "term -> MINUS expr\n"); }
            | NOT expr                                  { fprintf(yaccout, "term -> NOT expr\n"); }
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
            | primary                                   { fprintf(yaccout, "term -> primary\n"); }
            ;

assignexpr: lvalue EQUALS expr                          {   if ($1 != NULL && $1->type != USERFUNC && $1->type != LIBFUNC) {
                                                                fprintf(yaccout, "assignexpr -> lvalue EQUALS expr\n");}
                                                            else if ($1->type == USERFUNC || $1->type == LIBFUNC) {
                                                                fprintf(stderr, "ERROR at line %d, with scope %d: Can't assign a function\n", yylineno, scope);
                                                            } }

primary:    lvalue
            | call                                      { fprintf(yaccout, "primary -> call\n"); }
            | objectdef                                 { fprintf(yaccout, "primary -> objectdef\n"); }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS{ fprintf(yaccout, "primary -> LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS\n"); }
            | const                                     { fprintf(yaccout, "primary -> const\n"); }
            ;

lvalue:     ID                                          { fprintf(yaccout, "lvalue -> ID\n");
                                                            lvalue_id();
                                                        }                                                                   
            | LOCAL ID                                  { fprintf(yaccout, "lvalue -> LOCAL ID\n"); }
            | DOUBLE_COLON ID                           { fprintf(yaccout, "lvalue -> DOUBLE_COLON ID\n"); }
            | member                                    { fprintf(yaccout, "lvalue -> member\n"); }
            ;

member:     lvalue PERIOD ID                            { fprintf(yaccout, "member -> lvalue PERIOD ID\n"); }
            | lvalue LEFT_BRACKET expr RIGHT_BRACKET    { fprintf(yaccout, "member -> lvalue LEFT_BRACKET expr RIGHT_BRACKET\n"); }
            | call PERIOD ID                            { fprintf(yaccout, "member -> call PERIOD ID\n"); }
            | call LEFT_BRACKET expr RIGHT_BRACKET      { fprintf(yaccout, "member -> call LEFT_BRACKET expr RIGHT_BRACKET\n"); }
            ;

call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   { fprintf(yaccout, "call -> call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS\n"); }
            | lvalue callsuffix                             {   if ($1 == NULL) {
                                                                    fprintf(stderr, "ERROR at line %d, with scope %d: Function has not been declared\n", yylineno, scope);
                                                                } fprintf(yaccout, "call -> lvalue callsuffix\n"); }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { fprintf(yaccout, "call -> LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS\n"); }
            ;

callsuffix: normcall                                    { fprintf(yaccout, "callsuffix -> normcall\n"); }
            | methodcall                                { fprintf(yaccout, "callsuffix -> methodcall\n"); }
            ;

normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    { fprintf(yaccout, "normcall -> LEFT_PARENTHESIS elist RIGHT_PARENTHESIS\n"); }

methodcall: DOUBLE_PERIOD ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   { fprintf(yaccout, "methodcall -> DOUBLE_PERIOD ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS\n"); }

elist:      expr                                        { fprintf(yaccout, "elist -> expr\n"); }
            | elist COMMA expr                          { fprintf(yaccout, "elist -> elist COMMA expr\n"); }
            ;

objectdef:  LEFT_BRACKET elist RIGHT_BRACKET            { fprintf(yaccout, "objectdef -> LEFT_BRACKET elist RIGHT_BRACKET\n"); }
            | LEFT_BRACKET indexed RIGHT_BRACKET        { fprintf(yaccout, "objectdef -> LEFT_BRACKET indexed RIGHT_BRACKET\n"); }
            | LEFT_BRACKET RIGHT_BRACKET                { fprintf(yaccout, "objectdef -> LEFT_BRACKET RIGHT_BRACKET\n"); }
            ;

indexed:    indexedelem                                 { fprintf(yaccout, "indexed -> indexedelem\n"); }
            | indexedelem COMMA indexedelem             { fprintf(yaccout, "indexed -> indexedelem COMMA indexedelem\n"); }

indexedelem:LEFT_CBRACKET expr COLON expr RIGHT_CBRACKET    { fprintf(yaccout, "indexedelem -> LEFT_CBRACKET expr COLON expr RIGHT_CBRACKET\n"); }

openblock:  LEFT_CBRACKET stmt                          { scope++; if (max_scope < scope) {max_scope == scope; } 
                                                            fprintf(yaccout, "openblock -> LEFT_CBRACKET stmt\n"); }
            | openblock stmt                            { fprintf(yaccout, "openblock -> openblock stmt\n"); }
            ;

block:      LEFT_CBRACKET                               { scope++; if (max_scope < scope) {max_scope == scope; } } 
                            RIGHT_CBRACKET { scope--; } { fprintf(yaccout, "block -> LEFT_CBRACKET RIGHT_CBRACKET\n"); }
            | openblock RIGHT_BRACKET { scope--; }      { fprintf(yaccout, "block -> openblock RIGHT_BRACKET\n"); }
            ;

funcdef:    FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block { fprintf(yaccout, "funcdef -> FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block\n"); }
            | FUNCTION LEFT_PARENTHESIS RIGHT_PARENTHESIS block         { fprintf(yaccout, "funcdef -> FUNCTION LEFT_PARENTHESIS RIGHT_PARENTHESIS block\n"); }
            ;

const:      INT                                         { fprintf(yaccout, "const -> INT\n"); }
            | REAL                                      { fprintf(yaccout, "const -> REAL\n"); }
            | STRING                                    { fprintf(yaccout, "const -> STRING\n"); }
            | NIL                                       { fprintf(yaccout, "const -> NIL\n"); }
            | TRUE                                      { fprintf(yaccout, "const -> TRUE\n"); }
            | FALSE                                     { fprintf(yaccout, "const -> FALSE\n"); }
            ;

idlist:     ID                                          { fprintf(yaccout, "idlist -> ID\n"); }
            | idlist COMMA ID                           { fprintf(yaccout, "idlist -> idlist COMMA ID\n"); }
            ;   

ifstmt:     IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt             { fprintf(yaccout, "ifstmt -> IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt\n"); }
            | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt { fprintf(yaccout, "ifstmt -> IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt\n"); }
            ;

whilestmt:  WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt      { fprintf(yaccout, "whilestmt -> WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt\n"); }

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt    { fprintf(yaccout, "forstmt -> FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt\n"); }

returnstmt: RETURN expr SEMICOLON                        { fprintf(yaccout, "returnstmt -> RETURN expr SEMICOLON\n"); }  
            | RETURN SEMICOLON                           { fprintf(yaccout, "returnstmt -> RETURN SEMICOLON\n"); }
            ;

%%

int yyerror(const char* msg) {
    std::fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
    return 0;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = std::fopen(argv[1], "r");
        if (!yyin) {
            std::fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }
    
    yyparse();
    
    if (yyin && yyin != stdin) {
        std::fclose(yyin);
    }
    
    return EXIT_SUCCESS;
}