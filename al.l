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
                add_token(yylval,yylineno,count,yytext,"KEYWORD","IF")
            }

"else"      {}
"while"     {}
"for"       {}
"function"  {}
"return"    {}
"break"     {}
"continue"  {}
"and"       {}
"not"       {}
"or"        {}
"local"     {}
"true"      {}
"false"     {}
"nil"       {}

"="         {}
"+"         {}
"-"         {}
"*"         {}
"/"         {}
"%"         {}
"=="        {}
"!="        {}
"++"        {}
"--"        {}
">"         {}
"<"         {}
">="        {}
"<="        {}

"{"         {}
"}"         {}
"["         {}
"]"         {}
"("         {}
")"         {}
";"         {}
","         {}
":"         {}
"::"        {}
"."         {}
".."        {}

{ID}        {}
{INT}       {}
{REAL}      {}
{STRING}    {}
{WSPACE}    {}