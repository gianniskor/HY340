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
%type <exprV> member //working on it
%type <exprV> call
%type <exprV> callsuffix
%type <exprV> normcall
%type <exprV> methodcall
%type <exprV> elist
%type <exprV> indexed
%type <exprV> indexedelem
%type <statementT> block 
%type <statementT> stmts
%type <symbol_P> funcdef //working on it
%type <exprV> const //done 
%type <symbol_P> idlist
%type <intConst> ifprefix 
%type <intConst> elseprefix
%type <statementT> ifstmt
%type <symbol_P> whilestmt
%type <symbol_P> forstmt
%type <symbol_P> returnstmt
%type <exprV> objectdef //done

/*
  BUSULAS: 
  arithmitika done;
  object def done;
  object assign, access,incr;
  a {<,>,<=,>=,==,!=} b;

  KANW: 
  NOT OR

  TODO:
  oliki (!)
  if else
  while
  for

  PROBLEMS
  t2 = [1,2,print];
    "Error: Cannot use function print as an lvalue at line 1"
    "Error in SymToExpr function, symbol -> null"
*/

%%

program:    stmts                                       { fprintf(yacc_out,"liststmt -> stmt\n"); fclose(yacc_out);}
            |%empty                                     { fprintf(yacc_out,"empty program\n"); fclose(yacc_out);}
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

              expr* tmpExpr = newTempExpr("call");
              emit(call, nullptr, nullptr, $1);

              expr* result = newTempExpr("call");
              emit(getretval, nullptr, nullptr, result);
              $$ = result;

 }
            | lvalue callsuffix                             {
              emit (call, nullptr, nullptr, $1);
              expr* result = newTempExpr("lvalue call");
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

                  Symbol *s = (Symbol*)$2;
                  emit(call, nullptr, nullptr, symToExpr(s));
                  expr* result = newTempExpr("call funcdef");
                  emit(getretval, nullptr, nullptr, result);
                  $$ = result;
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
                                                          expr* tmpExpr = newTempExpr("l_ELIST_r");
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
                                                          expr* tmpExpr = newTempExpr("objectdef l_IDX_r");
                                                          tmpExpr->type = newtable_e;
                                                          emit(tablecreate, nullptr, nullptr, tmpExpr);
                                                          expr* current = $2;
                                                          while(current) {
                                                              emit(tablesetelem, current->index, current,tmpExpr);
                                                              current = current->next;
                                                          }
                                                          $$ = tmpExpr;
                                                        }
            // | LEFT_BRACKET RIGHT_BRACKET                {
            //                                               expr* tmpExpr = newTempExpr("objectdef lr");
            //                                               if (!tmpExpr) {
            //                                                   cerr << "Failed to create temp expression for empty table" << endl;
            //                                                   exit(-1);
            //                                               }
            //                                               tmpExpr->type = newtable_e;
            //                                               tmpExpr->next = nullptr;
            //                                               tmpExpr->prev = nullptr;
            //                                               tmpExpr->index = nullptr;
            //                                               emit(tablecreate, nullptr, nullptr, tmpExpr);
            //                                               $$ = tmpExpr;
            //                                             }
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
              
            }
            idlist RIGHT_PARENTHESIS block { 
              Symbol *s = symbolTable.lookup($2)[0];
              if (s && s->type == USER_FUNC) {
                  unsigned int localCount = symbolTable.getTotalLoc();
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
            RIGHT_PARENTHESIS block         { 
              int currentFuncIndex = anonCount - 1;
              string name = "_f" + to_string(currentFuncIndex);
              Symbol *s = symbolTable.lookup(name.c_str())[0];
              if (s && s->type == USER_FUNC) {
                  unsigned int localCount = symbolTable.getTotalLoc();
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
      int quad_counter = nextquad();
    //expr* JumpPlus2 = newIntExpr(quad_counter+2);
    expr* JumpTrue = newBoolExpr(true);
    emit(if_eq,$3,JumpTrue,nullptr,quad_counter+3);
    $$ = nextquad();
    //0 is gonnafixed
    emit(jump,nullptr,nullptr,0);
                                                          //  $$ = ifPrefix($3,*help);
                                                          }

elseprefix: ELSE {}

ifstmt: ifprefix stmt elseprefix stmt {
          // fprintf(yacc_out,"ifstmt -> if (expr) stmt\n"); 
          // $$ = newIfStmt($3, $5, nullptr); 
          // backpatch($3->trueList, nextquad());
          // $$->nextlist = $3->falseList;
                    
        }
       | ifprefix stmt %prec LOWER_THAN_ELSE{ 
          $$ = $2;
          int quad_counter = nextquad();
          fixLabel($1,quad_counter);
          // fprintf(yacc_out,"ifstmt -> if (expr) else stmt\n");
          // $$ = newIfStmt($3, $5, $7);   //de briskei to newifstmt eno to exo orisei pantou me to idio onoma ...
          // unsigned thenQuad = nextquad();
          // emit(jump, nullptr, nullptr, nullptr);
          // unsigned elseQuad = nextquad();
          // backpatch($3->trueList, thenQuad);
          // backpatch($3->falseList, elseQuad);
        }
       ;

whilestmt:  WHILE LEFT_PARENTHESIS expression RIGHT_PARENTHESIS stmt      { }

forstmt:    FOR LEFT_PARENTHESIS elist SEMICOLON expression SEMICOLON elist RIGHT_PARENTHESIS stmt    { }

returnstmt: RETURN expression SEMICOLON                        { }  
            | RETURN SEMICOLON                                 { }
            ;

%%


