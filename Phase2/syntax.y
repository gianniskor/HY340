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
    int yylex();
    extern int yylineno;
    extern char* yytext;
    int scope = 0;
    int max_scope = 0;
    extern SymbolTable symbolTable; 
    static int anonCount = 0;
    int localOffset = 0;
    int globalOffset = 0;
    int tmpCount = 0;
    int loopCounter = 0;
    int funcCounter = 0;
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
    //unsigned int flowLabel_V;
    //type_t * statementT;
    expr* expression;
    stmt_t* statement;
    forConst_t* forCnst;
}
%initial-action
{   
  
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
%type <statement> block 
%type <statement> stmts
%type <symbol_P> funcdef
%type <exprV> const
%type <symbol_P> idlist
%type <intConst> ifprefix 
%type <intConst> elseprefix
%type <statement> ifstmt
%type <statement> whilestmt
%type <statement> returnstmt
%type <exprV> objectdef
%type <intConst> whileflag
%type <intConst> startwhile
%type <statement> forstmt
%type <intConst> N 
%type <intConst> M 
%type <statement> program
%type <statement> loop
%type <forCnst> forprefix
%type <symbol_P> funcprefix;

/*
  BUSULAS: 
  arithmitika done;
  object def done;
  function def done;
  object assign, access,incr;
  a {<,>,<=,>=,==,!=} b;
  NOT, OR, AND;
  IF, IF-ELSE, IF-ELSE_IF-ELSE;
  while, cont, break for
  KANW:

  TODO:

  PROBLEMS
  
*/

%%

program:    stmts                                       { 
                                                          $$ = $1;
                                                        }
            |%empty                                     { }
            ;

stmts:      stmt                                        {
                                                          $$ = $1;
                                                        }
            | stmts stmt                                { 
                                                          $$ = initLists();
                                                          $$->continueLabel = mergeList($1->continueLabel,$2->continueLabel);
                                                          $$-> returnLabel = mergeList($1->returnLabel,$2->returnLabel);
                                                          $$->breakLabel = mergeList($1->breakLabel,$2->breakLabel);
                                                        }
            ;

stmt:       expression SEMICOLON                        { 
                                                          $$ = initLists();
                                                          tmpCount = 0;
                                                        }
            | ifstmt                                    { $$ = $1;
                                                          tmpCount = 0;
                                                        }
            | whilestmt                                 { 
                                                          $$ = initLists();
                                                        }
            | forstmt                                   { 
                                                          $$ = initLists();
                                                        }
            | returnstmt                                { 
                                                          $$ = setStmtList(2);
                                                        }
            | BREAK SEMICOLON                           { 
                                                          $$ = setStmtList(0);
                                                          tmpCount = 0;
                                                        }
            | CONTINUE SEMICOLON                        { 
                                                          tmpCount = 0;
                                                          $$ = setStmtList(1);
                                                        }
            | block                                     {
                                                          tmpCount = 0;
                                                          $$ = $1;
                                                        } 
            | funcdef                                   { 

                                                          $$ = initLists();
                                                        }
            | SEMICOLON                                 { 
                                                          $$ = initLists();
                                                          tmpCount = 0;
                                                        }
            | %empty                                    { 
                                                          $$ = initLists(); //evala ayto
                                                        }
            ;


expression: assignexpr                                  {}
          | term                                        { }
          | expression PLUS expression                  {
                                                           $$ = evaluateNumber($1, $3, add);
                                                        }
          | expression MINUS expression                 {
                                                           $$ = evaluateNumber($1, $3, sub);
                                                        }   
          | expression MULTIPLY expression              {
                                                           $$ = evaluateNumber($1, $3, mul);
                                                        }       
          | expression DIVIDE expression                {
                                                           $$ = evaluateNumber($1, $3, div_op);
                                                        }         
          | expression MOD expression                   {
                                                           $$ = evaluateNumber($1, $3, mod);
                                                        }

          | expression DOUBLE_EQUALS expression         {
                                                         $$ = evaluateBoolean($1,$3,if_eq);
                                                        } 
          | expression NOT_EQUALS expression            {
                                                          $$ = evaluateBoolean($1,$3,if_noteq);
                                                        }
          | expression LESS expression                  {
                                                          $$ = evaluateBoolean($1,$3,if_less);
                                                        }
          | expression GREATER expression               {
                                                          $$ = evaluateBoolean($1,$3,if_greater);
                                                        }
          | expression LESS_EQUALS expression           {
                                                          $$ = evaluateBoolean($1,$3,if_lesseq);
                                                        }
          | expression GREATER_EQUALS expression        {
                                                          $$ = evaluateBoolean($1,$3,if_greatereq);
                                                        }

          | expression AND expression                   { 
                                                          evaluateAND_OR($1,$3,and_op);
                                                        }
          | expression OR expression                    {
                                                          evaluateAND_OR($1,$3,or_op);  
                                                        } 
          ;

term:       LEFT_PARENTHESIS expression RIGHT_PARENTHESIS     { 
                                                                $$ = $2;
                                                              }
            | MINUS expression %prec NEGATIVE_VAL             { 
                                                                $$ = evaluateUminus($2);
                                                              }
            | NOT expression                                  {
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
            | primary                                         { 
                                                                $$ = $1;
                                                              }
            ;

assignexpr: lvalue EQUALS expression                          { 
                                                                $$ = evaluateAssignExp($1, $3);
                                                              }

primary:    lvalue                                      {}
            | call                                      {}
            | objectdef                                 {}
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS{ 
                                                          $$ = newNilExpr();
                                                          $$->type = programfunc_e;
                                                          $$->sym = $2;
                                                        }
            | const                                     {}
            ;


lvalue:     ID                                          { 
                                                          $$ = lvaluesIncert($1,3);
                                                        }                                                                   
            | LOCAL ID                                  { 
                                                          // Symbol *s = symbolTable.local_lvalue($2,symbolTable.currentScope,yylineno);
                                                          // $$ = symToExpr(s);
                                                          $$ = lvaluesIncert($2,2);
                                                        }
            | DOUBLE_COLON ID                           { 
                                                          // Symbol *s = symbolTable.local_lvalue($2,0,yylineno);
                                                          // $$ = symToExpr(s);
                                                          $$ = lvaluesIncert($2,1);
                                                        }
            | member                                    {}
            ;

member:     lvalue PERIOD ID                            {
                                                          $$ = tablePeriodId($1, $3);
                                                        }
            | lvalue LEFT_BRACKET expression RIGHT_BRACKET    {
                                                                $$ = tableBrackets($1,$3);
                                                              }
            | call PERIOD ID                            {}
            | call LEFT_BRACKET expression RIGHT_BRACKET      {
                                                              }
            ;

call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                                                              expr* current = $3;
                                                              int  paramCount = 0;

                                                              while (current) {
                                                                  paramCount++;
                                                                  if (!current->next) break;
                                                                      current = current->next;
                                                                  }

                                                              while (current && paramCount > 0) {
                                                                  emit (param, current, nullptr, nullptr);
                                                                  current = current->prev;
                                                                  paramCount--;
                                                              }
                                                              emit(call, nullptr, nullptr, $1);

                                                              expr* result = newTempExpr();
                                                              emit(getretval, nullptr, nullptr, result);
                                                              $$ = result;
                                                              

                                                              // expr* current = $3;
                                                              // int paramCount = 0;

                                                              // // Count parameters
                                                              // while (current) {
                                                              //     paramCount++;
                                                              //     current = current->next;
                                                              // }

                                                              // // Reset to beginning and emit param instructions
                                                              // current = $3;
                                                              // while (current) {
                                                              //     emit(param, current, nullptr, nullptr);
                                                              //     current = current->next;
                                                              // }
                                                              
                                                              // // Emit the call instruction
                                                              // emit(call, nullptr, nullptr, $1);

                                                              // // Get return value
                                                              // expr* result = newTempExpr();
                                                              // emit(getretval, nullptr, nullptr, result);
                                                              // $$ = result;
                                                            }
            | lvalue callsuffix                             {
                                                              expr* current = $2;
                                                              int  paramCount = 0;

                                                              while (current) {
                                                                  paramCount++;
                                                                  if (!current->next) break;
                                                                      current = current->next;
                                                                  }

                                                              while (current && paramCount > 0) {
                                                                  emit (param, current, nullptr, nullptr);
                                                                  current = current->prev;
                                                                  paramCount--;
                                                              }
                                                              expr* e_tmp = newNilExpr();

                                                              emit(call, nullptr, nullptr, $1);

                                                              expr* result = newTempExpr();
                                                              emit(getretval, nullptr, nullptr, result);
                                                              $$ = result;


                                                              // expr* current = $2;
                                                              // // Emit param instructions for each argument
                                                              // while (current) {
                                                              //     emit(param, current, nullptr, nullptr);
                                                              //     current = current->next;
                                                              // }
                                                              
                                                              // // Emit the call instruction
                                                              // emit(call, nullptr, nullptr, $1);

                                                              // // Get return value
                                                              // expr* result = newTempExpr();
                                                              // emit(getretval, nullptr, nullptr, result);
                                                              // $$ = result;
                                                            }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {
                                                                                                    expr* current = $5;
                                                                                                    int  paramCount = 0;
                                                                                                    while (current) {
                                                                                                        paramCount++;
                                                                                                        if (!current->next)break;
                                                                                                            current = current->next;
                                                                                                    }
                                                                                                        while (current && paramCount > 0) {
                                                                                                            emit(param, current, nullptr, nullptr);
                                                                                                            current = current->prev;
                                                                                                            paramCount--;
                                                                                                        }
                                                                                                        expr* result = newTempExpr();
                                                                                                        expr* funcExpr = symToExpr($2);
                                                                                                        
                                                                                                        emit(call, nullptr, nullptr, funcExpr);
                                                                                                        emit(getretval, nullptr, nullptr, result);
                                                                                                        $$ = result;
                                                                                                  }
            ;

callsuffix: normcall                                    {
                                                          $$ = $1;
                                                        }  
            | methodcall                                {
                                                          $$ = $1;
                                                        }
            ;
normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    {
                                                          $$ =$2;
                                                        }

methodcall: DOUBLE_PERIOD ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {
                                                          expr* current = $4;
                                                          int  paramCount = 0;

                                                          while (current) {
                                                              paramCount++;
                                                              if (!current->next) break;
                                                                  current = current->next;
                                                              }
                                                              

                                                          while (current && paramCount > 0) {
                                                              emit (param, current, nullptr, nullptr);
                                                              current = current->prev;
                                                              paramCount--;
                                                          }
                                                          expr* method = newStringExpr($2);
                                                          //emit(call, nullptr, nullptr, method);
                                                          expr* result = newTempExpr();
                                                          //emit(getretval, nullptr, nullptr, result);
                                                          $$ = result;
                                                        }
                                                        ;             

elist:      %empty                                            { $$ = nullptr; 
                                                              }
            |
            elist COMMA expression                            {
                                                                while($1->next){
                                                                  $1 = $1-> next;
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
            | indexed COMMA indexedelem             { 
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

block:  LEFT_CBRACKET {
                        symbolTable.enterScope();
                      }
        stmts
        RIGHT_CBRACKET {
                          symbolTable.exitScope();
                          $$ = $3;
                        }
       |
       LEFT_CBRACKET RIGHT_CBRACKET {
                                    }  
       ;
funcprefix: FUNCTION ID LEFT_PARENTHESIS              {
                                                        localOffset = -1;
                                                        Symbol *s = symbolTable.lookupInScope($2, symbolTable.currentScope);
                                                        if(s != nullptr) {
                                                            fprintf(stderr, "ERROR at line %d, with scope %d: function %s already declared\n", 
                                                                    yylineno, symbolTable.currentScope, $2);
                                                        } else {
                                                            // Check for library function conflicts
                                                            vector <Symbol*> temp_sym = symbolTable.lookup($2);
                                                            bool isLib = false;
                                                            for (auto& sym : temp_sym) {
                                                                if (sym->type == LIB_FUNC) {
                                                                    isLib = true;
                                                                    break;
                                                                }
                                                            }
                                                            
                                                            if (isLib) {
                                                                fprintf(stderr, "ERROR at line %d, with scope %d: function %s already declared as a library function\n", 
                                                                        yylineno, symbolTable.currentScope, $2);
                                                            } else {
                                                                // s = symbolTable.insert($2, symbolTable.currentScope, yylineno, USER_FUNC);
                                                                // s->setIaddress(nextquad());
                                                                // emit(funcstart, nullptr, nullptr, symToExpr(s));
                                                            int jump_quad = nextquad();
                                                            emit(jump, nullptr, nullptr, nullptr, 0);
                                                            s = symbolTable.insert($2, symbolTable.currentScope, yylineno, USER_FUNC);
                                                            s->setIaddress(nextquad());
                                                            emit(funcstart, nullptr, nullptr, symToExpr(s));
                                                            s->funcJumpQuad = jump_quad;
                                                            }
                                                        }
                                                        $$ = s;
                                                        }
              

funcdef:      funcprefix idlist RIGHT_PARENTHESIS              {
                                                                incFunc();
                                                                //symbolTable.enterScope();
                                                                loopStack.push_back(loopCounter);
                                                                loopCounter = 0;
              } block                                          { 
                                                                  Symbol *s = $1;
                                                                  if (s && s->type == USER_FUNC) {
                                                                      // unsigned int localCount = symbolTable.getTotalLoc(symbolTable.currentScope);
                                                                      // s->setTotalLoc(localCount);
                                                                      expr* retval = newTempExpr();
                                                                      expr* funcname = symToExpr(s);
                                                                      //emit(assign, retval, funcname, nullptr);
                                                                      
                                                                      emit(funcend, nullptr, nullptr, symToExpr(s));
                                                                      quads[s->funcJumpQuad]->label = nextquad() + 1;
                                                                      // emit(funcend, nullptr, nullptr, symToExpr(s));
                                                                      // emit(funcend, nullptr, nullptr, symToExpr(s));
                                                                  }
                                                                  //symbolTable.exitScope();
                                                                  //TWRA AUTO GIATI EINAI 5?
                                                                  fixList($5->returnLabel,nextquad()-1);
                                                                  decFunc();
                                                                  int i = loopStack.back();
                                                                  loopStack.pop_back();
                                                                  $$ = s;
                                                                }
            | FUNCTION LEFT_PARENTHESIS                         {
                                                                  localOffset = -1;
                                                                  string name = "_f" + to_string(anonCount);
                                                                  int jump_quad = nextquad();
                                                                  emit(jump, nullptr, nullptr, nullptr, 0);
                                                                  Symbol *s = symbolTable.insert(name.c_str(), symbolTable.currentScope, yylineno, USER_FUNC);
                                                                  s->setIaddress(nextquad());
                                                                  emit(funcstart, nullptr, nullptr, symToExpr(s));
                                                                  s->funcJumpQuad = jump_quad;
                                                                  // int functionScope = symbolTable.currentScope;
                                                                  // s->setFuncScope(functionScope);

                                                                  anonCount++;
                                                                }
              idlist RIGHT_PARENTHESIS                          {
                                                                  loopStack.push_back(loopCounter);
                                                                  loopCounter = 0;
                                                                  //symbolTable.enterScope();
                                                                  incFunc();
                                                                }
              block                                          {
                                                              int currentFuncIndex = anonCount - 1;
                                                              string name = "_f" + to_string(currentFuncIndex);
                                                              Symbol *s = symbolTable.lookup(name.c_str())[0];
                                                              if (s && s->type == USER_FUNC) {
                                                                  //  int funcScope = s->getFuncScope() ;
                                                                  //  unsigned int localCount = symbolTable.getTotalLoc(funcScope);
                                                                  //  s->setTotalLoc(localCount);
                                                                  emit(funcend, nullptr, nullptr, symToExpr(s));
                                                                  quads[s->funcJumpQuad]->label = nextquad() +1;
                                                              }
                                                              //symbolTable.exitScope();
                                                              decFunc();
                                                              //fixList($2->returnList,nextquad());
                                                              //TWRA AUTO GIATI EINAI 7?
                                                              fixList($7->returnLabel,nextquad()-1);
                                                              int i = loopStack.back();
                                                              loopStack.pop_back();
                                                              $$ = s;
                                                            }
                                                            
            ;

const:      INT                                         {
                                                          $$ = newIntExpr($1);
                                                        }
            | REAL                                      {
                                                          $$ = newDoubleExpr($1);
                                                        }
            | STRING                                    {
                                                          $$ = newStringExpr($1);
                                                        }
            | NIL                                       { 
                                                        }
            | TRUE                                      {
                                                          $$ = newBoolExpr(true);
                                                        }
            | FALSE                                     {
                                                          $$ = newBoolExpr(false);
                                                        }
            ;

idlist: %empty                                     { }
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
                                                          param->setOffset(++localOffset);
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
                                                          param->setOffset(++localOffset);
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

N: %empty                                                { 
                                                          $$ = nextquad();
                                                          emit(jump, nullptr, nullptr, nullptr, nextquad());
                                                         }

M: %empty                                                {
                                                          $$ = nextquad();
                                                         }

forprefix: FOR LEFT_PARENTHESIS elist SEMICOLON M expression SEMICOLON {
                                                                          $$ = evaluateForPrefix($6,$5);
                                                                        }

forstmt: forprefix N elist RIGHT_PARENTHESIS N loop N                  {
                                                                          $$ = evaluateFor($1,$2 ,$6,$5,$7);
                                                                       }

returnstmt: RETURN expression SEMICOLON                        { 
                                                                  $$ = initLists();
                                                                  emit(return_op,$2,nullptr,nullptr);
                                                                }  
            | RETURN SEMICOLON                                 { 
                                                                  $$ = initLists();
                                                                  emit(return_op,nullptr,nullptr,nullptr);
                                                               }
            ;

%%


