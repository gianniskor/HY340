/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SYNTAX_HPP_INCLUDED
# define YY_YY_SYNTAX_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "syntax.y"

    #include "headerLib.h"

#line 53 "syntax.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    STRING = 259,                  /* STRING  */
    INT = 260,                     /* INT  */
    REAL = 261,                    /* REAL  */
    TRUE = 262,                    /* TRUE  */
    FALSE = 263,                   /* FALSE  */
    LEFT_PARENTHESIS = 264,        /* "("  */
    RIGHT_PARENTHESIS = 265,       /* ")"  */
    LEFT_BRACKET = 266,            /* "["  */
    RIGHT_BRACKET = 267,           /* "]"  */
    LEFT_CBRACKET = 268,           /* "{"  */
    RIGHT_CBRACKET = 269,          /* "}"  */
    SEMICOLON = 270,               /* ";"  */
    COMMA = 271,                   /* ","  */
    COLON = 272,                   /* ":"  */
    DOUBLE_COLON = 273,            /* "::"  */
    PERIOD = 274,                  /* "."  */
    DOUBLE_PERIOD = 275,           /* ".."  */
    PLUS = 276,                    /* "+"  */
    MINUS = 277,                   /* "-"  */
    MULTIPLY = 278,                /* "*"  */
    DIVIDE = 279,                  /* "/"  */
    PLUS_PLUS = 280,               /* "++"  */
    MINUS_MINUS = 281,             /* "--"  */
    MOD = 282,                     /* "%"  */
    EQUALS = 283,                  /* "="  */
    DOUBLE_EQUALS = 284,           /* "=="  */
    NOT_EQUALS = 285,              /* "!="  */
    LESS = 286,                    /* "<"  */
    GREATER = 287,                 /* ">"  */
    LESS_EQUALS = 288,             /* "<="  */
    GREATER_EQUALS = 289,          /* ">="  */
    AND = 290,                     /* "and"  */
    NOT = 291,                     /* "not"  */
    OR = 292,                      /* "or"  */
    IF = 293,                      /* "if"  */
    ELSE = 294,                    /* "else"  */
    WHILE = 295,                   /* "while"  */
    NIL = 296,                     /* "nil"  */
    RETURN = 297,                  /* "return"  */
    FUNCTION = 298,                /* "function"  */
    BREAK = 299,                   /* "break"  */
    CONTINUE = 300,                /* "continue"  */
    LOCAL = 301,                   /* "local"  */
    FOR = 302,                     /* "for"  */
    NEGATIVE_VAL = 303,            /* NEGATIVE_VAL  */
    LOWER_THAN_ELSE = 304          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "syntax.y"

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

#line 135 "syntax.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYNTAX_HPP_INCLUDED  */
