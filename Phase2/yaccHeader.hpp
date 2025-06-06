#ifndef YACC_HEADER_HPP
#define YACC_HEADER_HPP
#include <cstdio>
extern int yylineno;
extern char* yytext;
int yyerror(char* str)
{return 0;}
#endif