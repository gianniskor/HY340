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
    static int anonCount = 0;
 
    int tmpCount = 0;
    int loopCounter = 0;
    // vector<int> continueList;
    // vector<int> breakList;
%}

%start program

%union {
    char* stringConst;
    int intConst;
    double realConst;
    struct expr* exprV;
    struct ifstmt* Ifstmt;
    class Symbol* symbol_P;
    int boolConst;
    /*Gia thn trith fash prosethikan 
    ta parakatw sto union*/
    unsigned int flowLabel_V;
    //type_t * statementT;
    expr* expression;
    stmt_t* statement;
    forConst_t* forCnst;
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
%type <statement> stmt 
%type <exprV> term //working on it
%type <exprV> assignexpr //done
%type <exprV> primary
%type <exprV> lvalue
%type <exprV> member //working on it
%type <exprV> call
%type <exprV> callsuffix
%type <exprV> normcall
%type <exprV> methodcall
%type <exprV> elist
%type <exprV> indexed
%type <exprV> indexedelem
%type <statement> block 
%type <statement> stmts
%type <statement> funcdef //working on it
%type <exprV> const //done 
%type <symbol_P> idlist
%type <intConst> ifprefix 
%type <intConst> elseprefix
%type <statement> ifstmt
%type <statement> whilestmt
//%type <symbol_P> forstmt
%type <statement> returnstmt
%type <exprV> objectdef //done
%type <intConst> whileflag //woi
%type <intConst> startwhile //woi
//%type <intConst> forprefix //woi
%type <intConst> forstmt //woi
%type <intConst> N //woi
%type <intConst> M //woi
%type <statement> program
%type <statement> loop
%type <forCnst> forprefix;

/*
  BUSULAS: 
  arithmitika done;
  object def done;
  object assign, access,incr;
  a {<,>,<=,>=,==,!=} b;
  NOT, OR, AND;
  IF, IF-ELSE, IF-ELSE_IF-ELSE;
  while, cont, break
  KANW:

  TODO:
  for

  PROBLEMS
  t2 = [1,2,print];
    "Error: Cannot use function print as an lvalue at line 1"
    "Error in SymToExpr function, symbol -> null"
*/

%%

program:    stmts                                       { 
                                                          $$ = $1;
                                                          fprintf(yacc_out,"liststmt -> stmt\n"); fclose(yacc_out);
                                                        }
            |%empty                                     { fprintf(yacc_out,"empty program\n"); fclose(yacc_out);}
            ;

stmts:      stmt                                        { fprintf(yacc_out,"liststmt -> liststmt stmt\n");
                                                          $$ = $1;
                                                        }
            | stmts stmt                                { 
                                                          $$ = initLists();
                                                          $$->continueLabel = mergeList($1->continueLabel,$2->continueLabel);
                                                          $$-> returnLabel = mergeList($1->returnLabel,$2->returnLabel);
                                                          $$->breakLabel = mergeList($1->breakLabel,$2->breakLabel);
                                                          fprintf(yacc_out,"liststmt -> stmt\n");
                                                        }
            ;

stmt:       expression SEMICOLON                        { 
                                                          $$ = initLists();
                                                          tmpCount = 0;
                                                          fprintf(yacc_out,"stmt -> expr;\n");
                                                        }
            | ifstmt                                    { $$ = $1;
                                                          fprintf(yacc_out,"stmt -> ifstmt;\n");
                                                          tmpCount = 0;
                                                        }
            | whilestmt                                 { 
                                                          $$ = initLists();
                                                          fprintf(yacc_out,"stmt -> whilestmt;\n");
                                                        }
            | forstmt                                   { 
                                                          $$ = initLists();
                                                          fprintf(yacc_out,"stmt -> forstmt;\n");}
            | returnstmt                                { 
                                                          $$ = setStmtList(2);
                                                          fprintf(yacc_out,"stmt -> returnstmt;\n");
                                                        }
            | BREAK SEMICOLON                           { 
                                                          $$ = setStmtList(0);
                                                          tmpCount = 0;
                                                          fprintf(yacc_out,"stmt -> breakstmt;\n");
                                                        }
            | CONTINUE SEMICOLON                        { 
                                                          fprintf(yacc_out,"stmt -> continuestmt;\n");
                                                          tmpCount = 0;
                                                          $$ = setStmtList(1);
                                                        }
            | block                                     { fprintf(yacc_out,"stmt -> blockstmt;\n");
                                                          tmpCount = 0;
                                                          $$ = $1;
                                                        } 
            | funcdef                                   { 
                                                          fprintf(yacc_out,"stmt -> functstmt;\n");
                                                          $$ = initLists();
                                                        }
            | SEMICOLON                                 { 
                                                          fprintf(yacc_out,"stmt -> semicolon;\n");
                                                          $$ = initLists();
                                                          tmpCount = 0;
                                                        }
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
          | expression MOD expression                   { fprintf(yacc_out,"expr -> %%\n");
                                                           $$ = evaluateNumber($1, $3, mod);
                                                        }

          | expression DOUBLE_EQUALS expression         { fprintf(yacc_out,"expr -> ==\n");
                                                         $$ = evaluateBoolean($1,$3,if_eq);
                                                        } 
          | expression NOT_EQUALS expression            { fprintf(yacc_out,"expr -> !=\n");
                                                          $$ = evaluateBoolean($1,$3,if_noteq);
                                                        }
          | expression LESS expression                  { fprintf(yacc_out,"expr -> <\n");
                                                          $$ = evaluateBoolean($1,$3,if_less);
                                                        }
          | expression GREATER expression               { fprintf(yacc_out,"expr -> >\n");
                                                          $$ = evaluateBoolean($1,$3,if_greater);
                                                        }
          | expression LESS_EQUALS expression           { fprintf(yacc_out,"expr -> <=\n");
                                                          $$ = evaluateBoolean($1,$3,if_lesseq);
                                                        }
          | expression GREATER_EQUALS expression        { fprintf(yacc_out,"expr -> >=\n");
                                                          $$ = evaluateBoolean($1,$3,if_greatereq);
                                                        }

          | expression AND expression                   { fprintf(yacc_out,"expr -> AND\n");
                                                          evaluateAND_OR($1,$3,and_op);
                                                        }
          | expression OR expression                    { fprintf(yacc_out,"expr -> OR\n");
                                                          evaluateAND_OR($1,$3,or_op);  
                                                        } 
          ;

term:       LEFT_PARENTHESIS expression RIGHT_PARENTHESIS     { fprintf(yacc_out,"expr -> (term)\n");
                                                                $$ = $2;
                                                              }
            | MINUS expression %prec NEGATIVE_VAL             { fprintf(yacc_out,"expr -> -term\n");
                                                                $$ = evaluateUminus($2);
                                                              }
            | NOT expression                                  {
                                                               fprintf(yacc_out,"expr -> !term\n");
                                                               $$ = evaluateNOT($2);
                                                              }
            | PLUS_PLUS lvalue                                {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluatePP(oneoneoneone, $2, false, add); //antrea ,dua lipa kosovo 1 , 2 i 3 augoustoy 
                                                                // ELA NA KLEISOYME TWRA EISITIRIA
                                                              }
             | lvalue PLUS_PLUS                               {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluatePP($1, oneoneoneone, true, add);
                                                              }
             | MINUS_MINUS lvalue                             {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluatePP(oneoneoneone, $2, false, sub);
                                                              }
             | lvalue MINUS_MINUS                             {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                $$ = evaluatePP($1, oneoneoneone, true, sub);
                                                              }
            | primary                                         { $$ = $1;
                                                                fprintf(yacc_out,"expr -> primary\n");}
            ;

assignexpr: lvalue EQUALS expression                          { 
                                                                $$ = evaluateAssignExp($1, $3);
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

member:     lvalue PERIOD ID                            { fprintf(yacc_out,"member -> lvalue.id\n");
                                                          $$ = tablePeriodId($1, $3);
                                                        }
            | lvalue LEFT_BRACKET expression RIGHT_BRACKET    {fprintf(yacc_out,"member -> lvalue[expr]\n"); 
                                                                $$ = tableBrackets($1,$3);
                                                              }
            | call PERIOD ID                            { fprintf(yacc_out,"member -> call.id\n");}
            | call LEFT_BRACKET expression RIGHT_BRACKET      { fprintf(yacc_out,"member -> call[expr]\n");}
            ;

call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
              expr* current = $3;
              int  paramCount = 0;
              expr* last = nullptr;
              while (current) {
                  paramCount++;
                  if (current->next) {
                      last = current;
                      current = current->next;
                  }
              }

              current =last;
              while (current && paramCount > 0) {
                  emit (param, current, nullptr, nullptr);
                  current = current->prev;
                  paramCount--;
              }

              expr* tmpExpr = newTempExpr();
              emit(call, nullptr, nullptr, $1);

              expr* result = newTempExpr();
              emit(getretval, nullptr, nullptr, result);
              $$ = result;

 }
            | lvalue callsuffix                             {
              emit (call, nullptr, nullptr, $1);
              expr* result = newTempExpr();
              emit(getretval, nullptr, nullptr, result);
              $$ = result;
             }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {
              expr* current = $5;
              int  paramCount = 0;
              expr* last = nullptr;
              while (current) {
                  paramCount++;
                  if (current->next) {
                      last = current;
                      current = current->next;
                  }
                  current = last;
                  while (current && paramCount > 0) {
                      emit(param, current, nullptr, nullptr);
                      current = current->prev;
                      paramCount--;
                  }
              }
             }
            ;

callsuffix: normcall                                    {$$ = $1;}  
            | methodcall                                {$$ = $1;}
            ;

normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    {$$ =$2;}

methodcall: DOUBLE_PERIOD ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                                                                           expr* current = $4;
                                                                           int  paramCount = 0;
                                                                           expr* last = nullptr;
                                                                           while (current) {
                                                                               paramCount++;
                                                                               if (current->next) {
                                                                                   last = current;
                                                                                   current = current->next;
                                                                               }
                                                                           }
                                                                           $$ = $4; }

elist:      %empty                                            { $$ = nullptr; 
                                                                fprintf(yacc_out,"elist -> null;\n");
                                                              }
            |
            elist COMMA expression                            {
                                                                while($1->next){
                                                                  $1 = $1-> next;
                                                                }
                                                                if($3->type == boolexpr_e){
                                                                  int lala;
                                                                }
                                                                $1->next = $3;
                                                                $3->prev = $1;
                                                              }
            | expression                                      { $$ = $1;
                                                                $$->next = nullptr;
                                                                $$->prev = nullptr;
                                                                }
            ;

objectdef:  LEFT_BRACKET elist RIGHT_BRACKET            { 
                                                          expr* tmpExpr = newTempExpr();
                                                          tmpExpr->type = newtable_e;
                                                          emit(tablecreate, nullptr, nullptr, tmpExpr);
                                                          if($2){
                                                              expr* current = $2;
                                                              int i = 0;
                                                              while (current) {
                                                                  expr* indexExpr = newIntExpr(i++);
                                                                  emit(tablesetelem, indexExpr, current,tmpExpr);
                                                                  current = current->next;
                                                              }
                                                          }
                                                          $$ = tmpExpr;
                                                          fprintf(yacc_out, "objectdef -> [ elist ]\n");
                                                        }
            | LEFT_BRACKET indexed RIGHT_BRACKET        { 
                                                          expr* tmpExpr = newTempExpr();
                                                          tmpExpr->type = newtable_e;
                                                          emit(tablecreate, nullptr, nullptr, tmpExpr);
                                                          expr* current = $2;
                                                          while(current) {
                                                              emit(tablesetelem, current->index, current,tmpExpr);
                                                              current = current->next;
                                                          }
                                                          $$ = tmpExpr;
                                                        }
            ;

indexed:    indexedelem                                 { $$ = $1;}
            | indexedelem COMMA indexedelem             { 
                                                        expr* current = $1;
                                                        while(current->next) {
                                                            current = current->next;
                                                        }
                                                        current->next = $3;
                                                        $3->prev = current;
                                                        $$ = $1;
                                                        }
            ;

indexedelem: LEFT_CBRACKET expression COLON expression RIGHT_CBRACKET   { 
                                                                          $$ = $4;
                                                                          $$->index = $2;
                                                                          $$->next = nullptr;
                                                                          $$->prev = nullptr; 
                                                                        }

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
                   s->setIaddress(nextquad());
                   emit(funcstart, nullptr, nullptr, symToExpr(s));
                   fprintf(yacc_out, "funcdef -> function %s\n", $2);
                }
              }
               int functionScope = symbolTable.currentScope + 1;
               if (s) s->setFuncScope(functionScope);
            }
            idlist RIGHT_PARENTHESIS block { 
              Symbol *s = symbolTable.lookup($2)[0];
              if (s && s->type == USER_FUNC) {
                //kai kala gia ta Local Variables
                  int funcScope = s->getFuncScope();
                  unsigned int localCount = symbolTable.getTotalLoc(funcScope);
                  s->setTotalLoc(localCount);
                  
                  emit(funcend, nullptr, nullptr, symToExpr(s));
              } 
            }
            | FUNCTION LEFT_PARENTHESIS {
              string name = "_f" + to_string(anonCount);
              fprintf(yacc_out, "funcdef -> function %s\n", name.c_str());
              Symbol *s = symbolTable.insert(name.c_str(), symbolTable.currentScope, yylineno, USER_FUNC);
              s->setIaddress(nextquad());
              emit(funcstart, nullptr, nullptr, symToExpr(s));
              anonCount++;
              }
            idlist RIGHT_PARENTHESIS block         { 
              int currentFuncIndex = anonCount - 1;
              string name = "_f" + to_string(currentFuncIndex);
              Symbol *s = symbolTable.lookup(name.c_str())[0];
              if (s && s->type == USER_FUNC) {
                  //kai kala gia ta Local Variables
                  unsigned int localCount = symbolTable.getTotalLoc(s->getFuncScope());
                  s->setTotalLoc(localCount);

                  emit(funcend, nullptr, nullptr, symToExpr(s));
              }
            }
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

idlist: %empty                                { fprintf(yacc_out, "idlist -> empty\n"); }
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

ifprefix: IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS {
                                                            $$ = ifPrefix($3);
                                                           }

elseprefix: ELSE                                           {
                                                            $$ = elsePrefix();
                                                           }

ifstmt: ifprefix stmt elseprefix stmt {
          fixLabel($1,$3+1);
          int quad_counter = nextquad();
          fixLabel($3,quad_counter);
          $$ = evaluateIfElse($1, $3, $2, $4);
        }
       | ifprefix stmt %prec LOWER_THAN_ELSE{ 
          $$ = $2;
          int quad_counter = nextquad();
          fixLabel($1,quad_counter);
        }
       ;

whileflag: LEFT_PARENTHESIS expression RIGHT_PARENTHESIS  { 
                                                            $$ = setWhileCont($2);
                                                          }
startwhile: WHILE                                         { 
                                                            jumpStartWhile($$); 
                                                          }
loop: { incLoop(); } stmt { decLoop(); }                  {
                                                            $$ = $2;
                                                          }
whilestmt:  startwhile whileflag loop                     {      
                                                            $$ = evaluateWhile($2,$3,$1);
                                                          }                 

N: %empty{  $$ = nextquad();
      emit(jump, nullptr, nullptr, nullptr, nextquad());
    }

M: %empty{  $$ = nextquad();  }

forprefix: FOR LEFT_PARENTHESIS elist SEMICOLON M expression SEMICOLON {
                                                                          $$ = evaluateForPrefix($6,$5);
                                                                       }

forstmt: forprefix N elist RIGHT_PARENTHESIS N stmt N                  {
                                                                          
                                                                       }

returnstmt: RETURN expression SEMICOLON                        { }  
            | RETURN SEMICOLON                                 { }
            ;

%%


