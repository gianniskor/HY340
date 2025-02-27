%{
    #include "lexLib.h"
    #define YY_DECL int alpha_yylex(void* yylval)
    int count = 0;
    void add_token(alpha_token_t *yylval, int line, int count, token_cont_t tt);
%}

%option noyywrap
%option yylineno
%option header-file = "al.h"

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
                token_cont_t tt = {yytext,"IF","KEYWORD"};
                add_token(yylval,yylineno, count, tt);
            }

"else"      {
                count++;
                token_cont_t tt = {yytext,"ELSE","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"while"     {
                count++;
                token_cont_t tt = {yytext,"WHILE","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"for"       {
                count++;
                token_cont_t tt = {yytext,"for","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"function"  {
                count++;
                token_cont_t tt = {yytext,"FUNCTION","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"return"    {
                count++;
                token_cont_t tt = {yytext,"RETURN","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"break"     {
                count++;
                token_cont_t tt = {yytext,"BREAK","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"continue"  {
                count++;
                token_cont_t tt = {yytext,"CONTINUE","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"and"       {
                count++;
                token_cont_t tt = {yytext,"AND","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"not"       {
                count++;
                token_cont_t tt = {yytext,"NOT","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"or"        {
                count++;
                token_cont_t tt = {yytext,"OR","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"local"     {
                count++;
                token_cont_t tt = {yytext,"LOCAL","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"true"      {
                count++;
                token_cont_t tt = {yytext,"TRUE","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"false"     {
                count++;
                token_cont_t tt = {yytext,"FALSE","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"nil"       {
                count++;
                token_cont_t tt = {yytext,"NIL","KEYWORD"};
                add_token(yylval, yylineno, count, tt);
            }
"="         {
                count++;
                token_cont_t tt = {yytext,"ASSIGN","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"+"         {
                count++;
                token_cont_t tt = {yytext,"PLUS","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"-"         {
                count++;
                token_cont_t tt = {yytext,"MINUS","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"*"         {
                count++;
                token_cont_t tt = {yytext,"MULTIPLY","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"/"         {
                count++;
                token_cont_t tt = {yytext,"DIVISION","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"%"         {
                count++;
                token_cont_t tt = {yytext,"MODULO","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"=="        {
                count++;
                token_cont_t tt = {yytext,"EQUAL","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"!="        {
                count++;
                token_cont_t tt = {yytext,"NONEQUAL","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"++"        {
                count++;
                token_cont_t tt = {yytext,"PLUS_PLUS","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"--"        {
                count++;
                token_cont_t tt = {yytext,"MINUS_MINUS","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
">"         {
                count++;
                token_cont_t tt = {yytext,"GREATER_THAN","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"<"         {
                count++;
                token_cont_t tt = {yytext,"LESS_THAN","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
">="        {
                count++;
                token_cont_t tt = {yytext,"GREATER_EQUAL_THAN","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"<="        {
                count++;
                token_cont_t tt = {yytext,"LESS_EQUAL_THAN","OPERATOR"};
                add_token(yylval, yylineno, count, tt);
            }
"{"         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","LEFT_BRACE"};
                add_token(yylval, yylineno, count, tt);
            }
"}"         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","RIGHT_BRACE"};
                add_token(yylval, yylineno, count, tt);
            }
"["         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","LEFT_BRACKET"};
                add_token(yylval, yylineno, count, tt);
            }
"]"         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","RIGHT_BRACKET"};
                add_token(yylval, yylineno, count, tt);
            }
"("         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","LEFT_PARENTHESIS"};
                add_token(yylval, yylineno, count, tt);
            }
")"         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","RIGHT_PARENTHESIS"};
                add_token(yylval, yylineno, count, tt);
            }
";"         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","SEMICOLON"};
                add_token(yylval, yylineno, count, tt);
            }
","         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","COMMA"};
                add_token(yylval, yylineno, count, tt);
            }
":"         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","COLON"};
                add_token(yylval, yylineno, count, tt);
            }
"::"        {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","DOUBLE_COLON"};
                add_token(yylval, yylineno, count, tt);
            }
"."         {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","PERIOD"};
                add_token(yylval, yylineno, count, tt);
            }
".."        {
                count++;
                token_cont_t tt = {yytext,"PUNCTUATION","DOUBLE_PERIOD"};
                add_token(yylval, yylineno, count, tt);
            }

{ID}        {
                count++;
                token_cont_t tt = {yytext,"IDENTIFIER","ID"};
                add_token(yylval, yylineno, count, tt);
            }
{INT}       {
                count++;
                token_cont_t tt = {yytext,"IDENTIFIER","INT"};
                add_token(yylval, yylineno, count, tt);
            }
{REAL}      {
                count++;
                token_cont_t tt = {yytext,"IDENTIFIER","REAL"};
                add_token(yylval, yylineno, count, tt);
            }
{STRING}    {
                count++;
                token_cont_t tt = {yytext,"IDENTIFIER","STRING"};
                add_token(yylval, yylineno, count, tt);
            }
{WSPACE}    {
            }
<<EOF>>     {return 2;}

%%

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("error opeing file\n");
    }
    alpha_token_t* token = NULL;
    if(!(yyin=fopen(argv[1],"r"))){
        printf("error sto diavasma\n");
    }
    while(1){
        token = (alpha_token_t*)malloc(sizeof(alpha_token_t));
        if(alpha_yylex(token)==2) break;
    }
    return 0;
}