%%

%{
    #include "lexLib.h"
%}

%option noyywrap
%option yylineno

ID      [a-zA-Z][a-zA-Z0-9]*
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
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "ASSIGN");
            }
"+"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "PLUS");
            }
"-"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "MINUS");
            }
"*"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "MULTIPLY");
            }
"/"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "DIVISION");
            }
"%"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "MODULO");
            }
"=="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "EQUAL");
            }
"!="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "NONEQUAL");
            }
"++"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "PLUS_PLUS");
            }
"--"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "OPERATOR", "MINUS_MINUS");
            }
">"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "GREATER_THAN");
            }
"<"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "LESSER_THAN");
            }
">="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "GREATER_EQUAL_THAN");
            }
"<="        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "LESSER_EQUAL_THAN");
            }
"{"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "LEFT_BRACE");
            }
"}"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "RIGHT_BRACE");
            }
"["         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "LEFT_BRACKET");
            }
"]"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "RIGHT_BRACKET");
            }
"("         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "LEFT_PARENTHESIS");
            }
")"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "RIGHT_PARENTHESIS");
            }
";"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "SEMICOLON");
            }
","         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "COMMA");
            }
":"         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "END_PARENTHESES");
            }
"::"        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "DOUBLE_END_PARENTHESES");
            }
"."         {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "POINT");
            }
".."        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "PUNCTUATION", "DOUBLE_POINT");
            }

{ID}        {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "IDENTIFIER", "ID");
            }
{INT}       {
                count++;
                token_cont_t tt = "<-integer";
                add_token(yylval, yylineno, count, yytext, "IDENTIFIER", "INT");
            }
{REAL}      {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "IDENTIFIER", "REAL");
            }
{STRING}    {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "IDENTIFIER", "STRING");
            }
{WSPACE}    {
                count++;
                token_cont_t tt = "<-enumerated";
                add_token(yylval, yylineno, count, yytext, "IDENTIFIER", "WSPACE");
            }