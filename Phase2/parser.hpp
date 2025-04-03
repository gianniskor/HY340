/* A Bison parser, made by GNU Bison 3.8.  */

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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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
    LEFT_PARENTHESIS = 262,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 263,       /* RIGHT_PARENTHESIS  */
    LEFT_BRACKET = 264,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 265,           /* RIGHT_BRACKET  */
    LEFT_CBRACKET = 266,           /* LEFT_CBRACKET  */
    RIGHT_CBRACKET = 267,          /* RIGHT_CBRACKET  */
    SEMICOLON = 268,               /* SEMICOLON  */
    COMMA = 269,                   /* COMMA  */
    COLON = 270,                   /* COLON  */
    DOUBLE_COLON = 271,            /* DOUBLE_COLON  */
    PERIOD = 272,                  /* PERIOD  */
    DOUBLE_PERIOD = 273,           /* DOUBLE_PERIOD  */
    PLUS = 274,                    /* PLUS  */
    MINUS = 275,                   /* MINUS  */
    MULTIPLY = 276,                /* MULTIPLY  */
    DIVIDE = 277,                  /* DIVIDE  */
    PLUS_PLUS = 278,               /* PLUS_PLUS  */
    MINUS_MINUS = 279,             /* MINUS_MINUS  */
    MOD = 280,                     /* MOD  */
    EQUALS = 281,                  /* EQUALS  */
    DOUBLE_EQUALS = 282,           /* DOUBLE_EQUALS  */
    NOT_EQUALS = 283,              /* NOT_EQUALS  */
    LESS = 284,                    /* LESS  */
    GREATER = 285,                 /* GREATER  */
    LESS_EQUALS = 286,             /* LESS_EQUALS  */
    GREATER_EQUALS = 287,          /* GREATER_EQUALS  */
    AND = 288,                     /* AND  */
    NOT = 289,                     /* NOT  */
    OR = 290,                      /* OR  */
    IF = 291,                      /* IF  */
    ELSE = 292,                    /* ELSE  */
    WHILE = 293,                   /* WHILE  */
    TRUE = 294,                    /* TRUE  */
    FALSE = 295,                   /* FALSE  */
    NIL = 296,                     /* NIL  */
    RETURN = 297,                  /* RETURN  */
    FUNCTION = 298,                /* FUNCTION  */
    BREAK = 299,                   /* BREAK  */
    CONTINUE = 300,                /* CONTINUE  */
    LOCAL = 301,                   /* LOCAL  */
    FOR = 302                      /* FOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define STRING 259
#define INT 260
#define REAL 261
#define LEFT_PARENTHESIS 262
#define RIGHT_PARENTHESIS 263
#define LEFT_BRACKET 264
#define RIGHT_BRACKET 265
#define LEFT_CBRACKET 266
#define RIGHT_CBRACKET 267
#define SEMICOLON 268
#define COMMA 269
#define COLON 270
#define DOUBLE_COLON 271
#define PERIOD 272
#define DOUBLE_PERIOD 273
#define PLUS 274
#define MINUS 275
#define MULTIPLY 276
#define DIVIDE 277
#define PLUS_PLUS 278
#define MINUS_MINUS 279
#define MOD 280
#define EQUALS 281
#define DOUBLE_EQUALS 282
#define NOT_EQUALS 283
#define LESS 284
#define GREATER 285
#define LESS_EQUALS 286
#define GREATER_EQUALS 287
#define AND 288
#define NOT 289
#define OR 290
#define IF 291
#define ELSE 292
#define WHILE 293
#define TRUE 294
#define FALSE 295
#define NIL 296
#define RETURN 297
#define FUNCTION 298
#define BREAK 299
#define CONTINUE 300
#define LOCAL 301
#define FOR 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    std::string* stringConst;
    int intConst;
    double realConst;
    struct expr* exprV;
    struct Symbol* symbol_P ;

#line 169 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

#if !defined yyerror && !defined YYERROR_IS_DECLARED
void yyerror (const char *msg);
#endif
#if !defined yylex && !defined YYLEX_IS_DECLARED
int yylex (void);
#endif

int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
