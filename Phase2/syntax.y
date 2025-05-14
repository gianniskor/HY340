%code requires {
    #include "headerLib.h"
}


%{
    #include <cstdio>
    #include <cstdlib>
    #include "lexLib.hpp" 
    #include "symtable.h"
    #include <string>
    #include "yaccHeader.hpp"
    // #include "quad.h"
    // #include "expression"
    int yylex();
    FILE* yacc_out;
    extern int yylineno;
    extern char* yytext;
    int scope = 0;
    int max_scope = 0;
    extern SymbolTable symbolTable;  
    int tmpCount = 0;
%}

%start program

%union {
    char* stringConst;
    int intConst;
    double realConst;
    struct expr* exprV;
    class Symbol* symbol_P;
    int boolConst;
    /*Gia thn trith fash prosethikan 
    ta parakatw sto union*/
    unsigned int flowLabel_V;
    type_t * statementT;
    expr* expression;
    /*menei na dw to for_type*/
}
%initial-action
{   
    yacc_out = fopen("yacc_output.txt", "w");
};

%token <stringConst> ID STRING
%token <intConst> INT 
%token <realConst> REAL
%token <boolConst> TRUE FALSE

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
// %token TRUE "true"
// %token FALSE "false"
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

%type <exprV> expression 
%type <statementT> stmt 
%type <exprV> term //working on it
%type <exprV> assignexpr //done
%type <symbol_P> primary
%type <exprV> lvalue
%type <symbol_P> member
%type <symbol_P> call
%type <symbol_P> callsuffix
%type <symbol_P> normcall
%type <symbol_P> methodcall
%type <exprV> elist
%type <symbol_P> indexed
%type <symbol_P> indexedelem
%type <statementT> block 
%type <statementT> stmts
%type <symbol_P> funcdef
%type <exprV> const //done 
%type <symbol_P> idlist
%type <symbol_P> ifstmt
%type <symbol_P> whilestmt
%type <symbol_P> forstmt
%type <symbol_P> returnstmt

/*
  BUSULAS: 
  arithmitika done;
*/

%%

program:    stmts                                       { fprintf(yacc_out,"liststmt -> stmt\n"); fclose(yacc_out);}
            |/* empty */                              { fprintf(yacc_out,"empty program\n"); fclose(yacc_out);}
            ;

stmts:      stmt                                        { fprintf(yacc_out,"liststmt -> liststmt stmt\n");}
            | stmts stmt                                { fprintf(yacc_out,"liststmt -> stmt\n");}
            ;

stmt:       expression SEMICOLON                        { tmpCount = 0;
                                                          fprintf(yacc_out,"stmt -> expr;\n");}
            | ifstmt                                    { fprintf(yacc_out,"stmt -> ifstmt;\n");}
            | whilestmt                                 { fprintf(yacc_out,"stmt -> whilestmt;\n");}
            | forstmt                                   { fprintf(yacc_out,"stmt -> forstmt;\n");}
            | returnstmt                                { fprintf(yacc_out,"stmt -> returnstmt;\n");}
            | BREAK SEMICOLON                           { fprintf(yacc_out,"stmt -> breakstmt;\n");}
            | CONTINUE SEMICOLON                        { fprintf(yacc_out,"stmt -> continuestmt;\n");}
            | block                                     { fprintf(yacc_out,"stmt -> blockstmt;\n");
                                                          tmpCount = 0;
                                                          $$ = $1;
                                                        } 
            | funcdef                                   { fprintf(yacc_out,"stmt -> functstmt;\n");}
            | SEMICOLON                                 { fprintf(yacc_out,"stmt -> semicolon;\n");}
            ;


expression: assignexpr                                  { fprintf(yacc_out,"expr -> assignexpr\n");}
          | term                                        { fprintf(yacc_out,"expr -> term\n");}
          | expression PLUS expression                  { fprintf(yacc_out,"expr -> +\n");
                                                           $$ = evaluateNumber($1, $3, add);
                                                        }
          | expression MINUS expression                 { fprintf(yacc_out,"expr -> -\n");
                                                           $$ = evaluateNumber($1, $3, sub);
                                                        }   
          | expression MULTIPLY expression              { fprintf(yacc_out,"expr -> *\n");
                                                           $$ = evaluateNumber($1, $3, mul);
                                                        }       
          | expression DIVIDE expression                { fprintf(yacc_out,"expr -> /\n");
                                                           $$ = evaluateNumber($1, $3, div_op);
                                                        }         
          | expression MOD expression                   { fprintf(yacc_out,"expr -> %\n");
                                                           $$ = evaluateNumber($1, $3, mod);
                                                        }

          | expression DOUBLE_EQUALS expression         { fprintf(yacc_out,"expr -> ==\n");}
          | expression NOT_EQUALS expression            { fprintf(yacc_out,"expr -> !=\n");}
          | expression LESS expression                  { fprintf(yacc_out,"expr -> <\n");}
          | expression GREATER expression               { fprintf(yacc_out,"expr -> >\n");}
          | expression LESS_EQUALS expression           { fprintf(yacc_out,"expr -> <=\n");}
          | expression GREATER_EQUALS expression        { fprintf(yacc_out,"expr -> >=\n");}

          | expression AND expression                   { fprintf(yacc_out,"expr -> AND\n");}
          | expression OR expression                    { fprintf(yacc_out,"expr -> OR\n");} 
          ;

term:       LEFT_PARENTHESIS expression RIGHT_PARENTHESIS     { fprintf(yacc_out,"expr -> (term)\n");
                                                                $$ = $2;
                                                              }
            | MINUS expression %prec NEGATIVE_VAL             { fprintf(yacc_out,"expr -> -term\n");
                                                                $$ = evaluateUminus($2);
                                                              }
            | NOT expression                                  {
                                                               fprintf(yacc_out,"expr -> !term\n");
                                                              }
            | PLUS_PLUS lvalue                                {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluateNumber($2, oneoneoneone, add); //antrea ,dua lipa kosovo 1 , 2 i 3 augoustoy 
                                                                // ELA NA KLEISOYME TWRA EISITIRIA

                                                              }
             | lvalue PLUS_PLUS                               {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluateNumber($1, oneoneoneone, add);
                                                              }
             | MINUS_MINUS lvalue                             {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluateNumber($2, oneoneoneone, sub);
                                                              }
             | lvalue MINUS_MINUS                             {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluateNumber($1, oneoneoneone, sub);
                                                              }
            | primary                                         { fprintf(yacc_out,"expr -> primary\n");}
            ;

assignexpr: lvalue EQUALS expression                          { 
                                                                $$ = evaluateAssignExp($1, $3);
                                                                //table items;
                                                                //expr* e = $1;
                                                                //bool values;

                                                              }

primary:    lvalue                                      { fprintf(yacc_out,"primary -> lvalue\n");}
            | call                                      { fprintf(yacc_out,"primary -> call\n");}
            | objectdef                                 { fprintf(yacc_out,"primary -> objectdef\n");}
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS{ fprintf(yacc_out,"primary -> (funcdef)\n");}
            | const                                     { fprintf(yacc_out,"primary -> const\n");}
            ;


lvalue:     ID                                          { Symbol *s = symbolTable.lvalue_default($1,symbolTable.currentScope,yylineno);
                                                          fprintf(yacc_out,"lvalue -> id\n");
                                                          $$ = symToExpr(s);
                                                        }                                                                   
            | LOCAL ID                                  { Symbol *s = symbolTable.local_lvalue($2,symbolTable.currentScope,yylineno);
                                                          fprintf(yacc_out,"lvalue -> local id\n");
                                                          $$ = symToExpr(s);
                                                        }
            | DOUBLE_COLON ID                           { Symbol *s = symbolTable.local_lvalue($2,0,yylineno);
                                                          fprintf(yacc_out,"lvalue -> global id\n");
                                                          $$ = symToExpr(s);
                                                        }
            | member                                    { fprintf(yacc_out,"lvalue -> id\n");}
            ;

member:     lvalue PERIOD ID                            { fprintf(yacc_out,"member -> lvalue.id\n");}
            | lvalue LEFT_BRACKET expression RIGHT_BRACKET    {fprintf(yacc_out,"member -> lvalue[expr]\n"); }
            | call PERIOD ID                            { fprintf(yacc_out,"member -> call.id\n");}
            | call LEFT_BRACKET expression RIGHT_BRACKET      { fprintf(yacc_out,"member -> call[expr]\n");}
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

elist:      %empty                                            {$$ = nullptr; 
                                                                fprintf(yacc_out,"elist -> null;\n");
                                                              }
            |
            elist COMMA expression                            {
            }
            | expression                                      { }
            ;

objectdef:  LEFT_BRACKET elist RIGHT_BRACKET            { }
            | LEFT_BRACKET indexed RIGHT_BRACKET        { }
            | LEFT_BRACKET RIGHT_BRACKET                { }
            ;

indexed:    indexedelem                                 { }
            | indexedelem COMMA indexedelem             { }

indexedelem: LEFT_CBRACKET expression COLON expression RIGHT_CBRACKET    { }

block: LEFT_CBRACKET {
         symbolTable.enterScope();
         fprintf(yacc_out, "Entered block scope %d\n", symbolTable.currentScope);
         
       }
       stmts
       RIGHT_CBRACKET {
         symbolTable.exitScope();
         fprintf(yacc_out, "Exited block scope %d\n", symbolTable.currentScope);
         $$ = $3;
       }
       |
       LEFT_CBRACKET RIGHT_CBRACKET {
         fprintf(yacc_out, "Empty block\n");
       }
       ;

funcdef:    FUNCTION ID LEFT_PARENTHESIS {
             Symbol *s = symbolTable.lookupInScope($2, symbolTable.currentScope);
              if(s!= nullptr){
                fprintf(stderr, "ERROR at line %d, with scope %d: function %s already declared\n", yylineno, symbolTable.currentScope, $2);
              } else {
               vector <Symbol*> temp_sym = symbolTable.lookup($2);
               bool isLib = false;
                for (auto& sym : temp_sym) {
                    if (sym->type == LIB_FUNC) {
                        isLib = true;
                        break;
                    }
                }
                if (isLib) {
                    fprintf(stderr, "ERROR at line %d, with scope %d: function %s already declared as a library function\n", yylineno, symbolTable.currentScope, $2);
                } else {
                   Symbol *s = symbolTable.insert($2, symbolTable.currentScope, yylineno, USER_FUNC);
                   fprintf(yacc_out, "funcdef -> function %s\n", $2);
                }
              }
              
            }
            idlist RIGHT_PARENTHESIS block { 

              ;}
            | FUNCTION LEFT_PARENTHESIS {
              static int anonCount = 0;
              string name = "_f" + to_string(anonCount);
              fprintf(yacc_out, "funcdef -> function %s\n", name.c_str());
              Symbol *s = symbolTable.insert(name.c_str(), symbolTable.currentScope, yylineno, USER_FUNC);
              anonCount++;
              }
            RIGHT_PARENTHESIS block         { }
            ;

const:      INT                                         { fprintf(yacc_out,"const -> number\n");
                                                          $$ = newIntExpr($1);
                                                        }
            | REAL                                      { fprintf(yacc_out,"const -> number\n");
                                                          $$ = newDoubleExpr($1);
                                                        }
            | STRING                                    { fprintf(yacc_out,"const -> string\n");
                                                          $$ = newStringExpr($1);
                                                        }
            | NIL                                       { fprintf(yacc_out,"const -> nil\n");}
            | TRUE                                      { fprintf(yacc_out,"const -> true\n");
                                                          $$ = newBoolExpr(true);
                                                        }
            | FALSE                                     { fprintf(yacc_out,"const -> false\n");
                                                          $$ = newBoolExpr(false);
                                                        }
            ;

idlist: /* empty */                                { fprintf(yacc_out, "idlist -> empty\n"); }
       | ID                                        { 
        Symbol *s = symbolTable.lookupInScope($1, symbolTable.currentScope);
        if(s!= nullptr){
          fprintf(stderr, "ERROR at line %d : formal redeclaration '%s'\n" , yylineno, $1);
          }else{
          auto temp_sym = symbolTable.lookup($1);
          bool isLib = false;
          for (auto& sym : temp_sym) {
              if (sym->type == LIB_FUNC) {
                  isLib = true;
                  break;
              }
          }
          if (isLib) {
              fprintf(stderr, "ERROR at line %d : formal argument shadows library function '%s'\n", yylineno, $1);
              } else {
                Symbol *param = symbolTable.insert($1, symbolTable.currentScope, yylineno, FUNCTION_PARAM);
                fprintf(yacc_out, "idlist -> %s\n", $1);
              }
          }
       }
       | idlist COMMA ID                           { 
        Symbol *s = symbolTable.lookupInScope($3, symbolTable.currentScope);
        if(s!= nullptr){
          fprintf(stderr, "ERROR at line %d : formal redeclaration '%s'\n" , yylineno, $3);
          }else{
          auto temp_sym = symbolTable.lookup($3);
          bool isLib = false;
          for (auto& sym : temp_sym) {
              if (sym->type == LIB_FUNC) {
                  isLib = true;
                  break;
              }
          }
          if (isLib) {
              fprintf(stderr, "ERROR at line %d : formal argument shadows library function '%s'\n", yylineno, $3);
              } else {
                Symbol *param = symbolTable.insert($3, symbolTable.currentScope, yylineno, FUNCTION_PARAM);
                fprintf(yacc_out, "idlist -> %s\n", $3);
              }
          }
       }
       ;    

ifstmt: IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS stmt %prec LOWER_THAN_ELSE { }
       | IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS stmt ELSE stmt { }
       ;

whilestmt:  WHILE LEFT_PARENTHESIS expression RIGHT_PARENTHESIS stmt      { }

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expression SEMICOLON elist RIGHT_PARENTHESIS stmt    { }

returnstmt: RETURN expression SEMICOLON                        { }  
            | RETURN SEMICOLON                                 { }
            ;

%%


