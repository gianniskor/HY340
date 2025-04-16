/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING = 259,
     INT = 260,
     REAL = 261,
     LEFT_PARENTHESIS = 262,
     RIGHT_PARENTHESIS = 263,
     LEFT_BRACKET = 264,
     RIGHT_BRACKET = 265,
     LEFT_CBRACKET = 266,
     RIGHT_CBRACKET = 267,
     SEMICOLON = 268,
     COMMA = 269,
     COLON = 270,
     DOUBLE_COLON = 271,
     PERIOD = 272,
     DOUBLE_PERIOD = 273,
     PLUS = 274,
     MINUS = 275,
     MULTIPLY = 276,
     DIVIDE = 277,
     PLUS_PLUS = 278,
     MINUS_MINUS = 279,
     MOD = 280,
     EQUALS = 281,
     DOUBLE_EQUALS = 282,
     NOT_EQUALS = 283,
     LESS = 284,
     GREATER = 285,
     LESS_EQUALS = 286,
     GREATER_EQUALS = 287,
     AND = 288,
     NOT = 289,
     OR = 290,
     IF = 291,
     ELSE = 292,
     WHILE = 293,
     TRUE = 294,
     FALSE = 295,
     NIL = 296,
     RETURN = 297,
     FUNCTION = 298,
     BREAK = 299,
     CONTINUE = 300,
     LOCAL = 301,
     FOR = 302,
     NEGATIVE_VAL = 303,
     LOWER_THAN_ELSE = 304
   };
#endif
/* Tokens.  */
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
#define NEGATIVE_VAL 303
#define LOWER_THAN_ELSE 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 18 "syntax.y"
{
    char* stringConst;
    int intConst;
    double realConst;
    struct expr* exprV;
    struct Symbol* symbol_P ;
}
/* Line 1529 of yacc.c.  */
#line 155 "syntax.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

