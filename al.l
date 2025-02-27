%%

%{
    #include "lexLib.h"
%}

%option noyywrap
%option yylineno

ID      [a-zA-z][a-zA-Z0-9]*
INT     [0-9]+
REAL    [0-9]+\.+[0-9]+
STRING  \"([^"\\]|\\.|\\\n)*\"
WSPACE  [ \n\t]

%x      COMMENT
%x      LINE_COMMENT

%%

"if"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval,yylineno,count,yytext,"KEYWORD","IF");
            }

"else"      {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "ELSE");
            }
"while"     {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "WHILE");
            }
"for"       {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "FOR");
            }
"function"  {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "FUNCTION");
            }
"return"    {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "RETURN");
            }
"break"     {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "BREAK");
            }
"continue"  {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "CONTINUE");
            }
"and"       {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "AND");
            }
"not"       {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "NOT");
            }
"or"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "OR");
            }
"local"     {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "LOCAL");
            }
"true"      {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "TRUE");
            }
"false"     {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "FALSE");
            }
"nil"       {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "NIL");
            }
"="         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "ASSIGN");
            }
"+"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "PLUS");
            }
"-"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "MINUS");
            }
"*"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "MULTIPLY");
            }
"/"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "DIVISION");
            }
"%"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "MODULO");
            }
"=="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "EQUAL");
            }
"!="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "NONEQUAL");
            }
"++"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "PLUS_PLUS");
            }
"--"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "MINUS_MINUS");
            }
">"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "GREATER_THAN");
            }
"<"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "LESSER_THAN");
            }
">="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "GREATER_EQUAL_THAN");
            }
"<="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "LESSER_EQUAL_THAN");
            }
"{"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "LEFT_BRACE");
            }
"}"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "RIGHT_BRACE");
            }
"["         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "LEFT_BRACKET");
            }
"]"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "RIGHT_BRACKET");
            }
"("         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "LEFT_PARENTHESIS");
            }
")"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "RIGHT_PARENTHESIS");
            }
";"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "SEMICOLON");
            }
","         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "COMMA");
            }
":"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "END_PARENTHESES");
            }
"::"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "DOUBLE_END_PARENTHESES");
            }
"."         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "POINT");
            }
".."        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "DOUBLE_POINT");
            }

{ID}        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "ID");
            }
{INT}       {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "INT");
            }
{REAL}      {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "REAL");
            }
{STRING}    {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "STRING");
            }
{WSPACE}    {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "KEYWORD", "WSPACE");
            }