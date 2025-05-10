/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "syntax.y"

    #include <cstdio>
    #include <cstdlib>
    #include "lexLib.hpp" 
    #include "symtable.h"
    #include <string>
    #include "yaccHeader.hpp"
    #include "quad.h"
    int yylex();
    FILE* yacc_out;
    extern int yylineno;
    extern char* yytext;
    int scope = 0;
    int max_scope = 0;
    extern SymbolTable symbolTable;  
    

#line 89 "syntax.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_REAL = 6,                       /* REAL  */
  YYSYMBOL_LEFT_PARENTHESIS = 7,           /* "("  */
  YYSYMBOL_RIGHT_PARENTHESIS = 8,          /* ")"  */
  YYSYMBOL_LEFT_BRACKET = 9,               /* "["  */
  YYSYMBOL_RIGHT_BRACKET = 10,             /* "]"  */
  YYSYMBOL_LEFT_CBRACKET = 11,             /* "{"  */
  YYSYMBOL_RIGHT_CBRACKET = 12,            /* "}"  */
  YYSYMBOL_SEMICOLON = 13,                 /* ";"  */
  YYSYMBOL_COMMA = 14,                     /* ","  */
  YYSYMBOL_COLON = 15,                     /* ":"  */
  YYSYMBOL_DOUBLE_COLON = 16,              /* "::"  */
  YYSYMBOL_PERIOD = 17,                    /* "."  */
  YYSYMBOL_DOUBLE_PERIOD = 18,             /* ".."  */
  YYSYMBOL_PLUS = 19,                      /* "+"  */
  YYSYMBOL_MINUS = 20,                     /* "-"  */
  YYSYMBOL_MULTIPLY = 21,                  /* "*"  */
  YYSYMBOL_DIVIDE = 22,                    /* "/"  */
  YYSYMBOL_PLUS_PLUS = 23,                 /* "++"  */
  YYSYMBOL_MINUS_MINUS = 24,               /* "--"  */
  YYSYMBOL_MOD = 25,                       /* "%"  */
  YYSYMBOL_EQUALS = 26,                    /* "="  */
  YYSYMBOL_DOUBLE_EQUALS = 27,             /* "=="  */
  YYSYMBOL_NOT_EQUALS = 28,                /* "!="  */
  YYSYMBOL_LESS = 29,                      /* "<"  */
  YYSYMBOL_GREATER = 30,                   /* ">"  */
  YYSYMBOL_LESS_EQUALS = 31,               /* "<="  */
  YYSYMBOL_GREATER_EQUALS = 32,            /* ">="  */
  YYSYMBOL_AND = 33,                       /* "and"  */
  YYSYMBOL_NOT = 34,                       /* "not"  */
  YYSYMBOL_OR = 35,                        /* "or"  */
  YYSYMBOL_IF = 36,                        /* "if"  */
  YYSYMBOL_ELSE = 37,                      /* "else"  */
  YYSYMBOL_WHILE = 38,                     /* "while"  */
  YYSYMBOL_TRUE = 39,                      /* "true"  */
  YYSYMBOL_FALSE = 40,                     /* "false"  */
  YYSYMBOL_NIL = 41,                       /* "nil"  */
  YYSYMBOL_RETURN = 42,                    /* "return"  */
  YYSYMBOL_FUNCTION = 43,                  /* "function"  */
  YYSYMBOL_BREAK = 44,                     /* "break"  */
  YYSYMBOL_CONTINUE = 45,                  /* "continue"  */
  YYSYMBOL_LOCAL = 46,                     /* "local"  */
  YYSYMBOL_FOR = 47,                       /* "for"  */
  YYSYMBOL_NEGATIVE_VAL = 48,              /* NEGATIVE_VAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 49,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_stmts = 52,                     /* stmts  */
  YYSYMBOL_stmt = 53,                      /* stmt  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_term = 55,                      /* term  */
  YYSYMBOL_assignexpr = 56,                /* assignexpr  */
  YYSYMBOL_primary = 57,                   /* primary  */
  YYSYMBOL_lvalue = 58,                    /* lvalue  */
  YYSYMBOL_member = 59,                    /* member  */
  YYSYMBOL_call = 60,                      /* call  */
  YYSYMBOL_callsuffix = 61,                /* callsuffix  */
  YYSYMBOL_normcall = 62,                  /* normcall  */
  YYSYMBOL_methodcall = 63,                /* methodcall  */
  YYSYMBOL_elist = 64,                     /* elist  */
  YYSYMBOL_objectdef = 65,                 /* objectdef  */
  YYSYMBOL_indexed = 66,                   /* indexed  */
  YYSYMBOL_indexedelem = 67,               /* indexedelem  */
  YYSYMBOL_block = 68,                     /* block  */
  YYSYMBOL_69_1 = 69,                      /* $@1  */
  YYSYMBOL_funcdef = 70,                   /* funcdef  */
  YYSYMBOL_const = 71,                     /* const  */
  YYSYMBOL_idlist = 72,                    /* idlist  */
  YYSYMBOL_ifstmt = 73,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 74,                 /* whilestmt  */
  YYSYMBOL_forstmt = 75,                   /* forstmt  */
  YYSYMBOL_returnstmt = 76                 /* returnstmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   611

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   135,   135,   136,   139,   140,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   156,   157,   158,   159,
     160,   161,   162,   164,   165,   166,   167,   168,   169,   171,
     172,   175,   176,   177,   178,   183,   188,   193,   198,   201,
     203,   204,   205,   206,   207,   211,   213,   215,   217,   220,
     221,   222,   223,   226,   227,   228,   231,   232,   235,   237,
     239,   240,   243,   244,   245,   248,   249,   251,   253,   253,
     264,   269,   270,   273,   274,   275,   276,   277,   278,   281,
     282,   285,   286,   289,   291,   293,   294
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "STRING", "INT",
  "REAL", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\";\"",
  "\",\"", "\":\"", "\"::\"", "\".\"", "\"..\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"++\"", "\"--\"", "\"%\"", "\"=\"", "\"==\"", "\"!=\"",
  "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"and\"", "\"not\"", "\"or\"",
  "\"if\"", "\"else\"", "\"while\"", "\"true\"", "\"false\"", "\"nil\"",
  "\"return\"", "\"function\"", "\"break\"", "\"continue\"", "\"local\"",
  "\"for\"", "NEGATIVE_VAL", "LOWER_THAN_ELSE", "$accept", "program",
  "stmts", "stmt", "expression", "term", "assignexpr", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "objectdef", "indexed", "indexedelem", "block", "$@1", "funcdef",
  "const", "idlist", "ifstmt", "whilestmt", "forstmt", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     190,  -109,  -109,  -109,  -109,   235,    19,     6,  -109,    42,
     323,     4,     4,   323,    44,    47,  -109,  -109,  -109,   279,
      10,    48,    54,    87,    86,    88,   190,  -109,   455,  -109,
    -109,  -109,   119,  -109,    40,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,    81,    99,  -109,   323,   533,    30,   107,
     106,  -109,   190,  -109,  -109,    78,    77,    40,    77,  -109,
     323,   323,  -109,   476,   115,   116,  -109,  -109,  -109,   323,
    -109,  -109,  -109,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   120,   122,
    -109,  -109,   323,  -109,  -109,  -109,   323,   323,   124,  -109,
     125,   516,  -109,   323,  -109,   118,   145,   126,   346,   364,
    -109,   130,   127,    20,    41,    41,  -109,  -109,  -109,   565,
     565,   241,   241,   241,   241,   579,   550,    -2,   388,  -109,
     128,   533,     1,   412,  -109,   323,   323,   533,  -109,  -109,
     125,   190,   190,  -109,     2,  -109,   323,  -109,  -109,   323,
    -109,  -109,    13,   434,   103,  -109,   127,   144,   497,    23,
    -109,  -109,   190,  -109,  -109,   323,  -109,  -109,    24,   190,
    -109
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    45,    75,    73,    74,     0,     0,    68,    15,     0,
       0,     0,     0,     0,     0,     0,    77,    78,    76,     0,
       0,     0,     0,     0,     0,     0,     2,     4,     0,    17,
      16,    38,    40,    48,    41,    42,    13,    14,    44,     7,
       8,     9,    10,     0,     0,    64,     0,    60,     0,     0,
      65,    70,     0,    47,    32,     0,    34,     0,    36,    33,
       0,     0,    86,     0,     0,     0,    11,    12,    46,     0,
       1,     5,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    37,     0,    54,    56,    57,     0,     0,     0,    31,
      43,     0,    62,     0,    63,     0,     0,     0,     0,     0,
      85,     0,     0,     0,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,     0,    49,
       0,    39,     0,     0,    51,     0,     0,    61,    66,    69,
       0,     0,     0,    79,     0,    72,     0,    58,    50,     0,
      53,    52,     0,     0,    81,    83,     0,     0,     0,     0,
      55,    67,     0,    71,    80,     0,    59,    82,     0,     0,
      84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -109,  -109,   101,   -23,    -5,  -109,  -109,  -109,    85,  -109,
      93,  -109,  -109,  -109,   -50,  -109,  -109,    50,  -108,  -109,
      -3,  -109,  -109,  -109,  -109,  -109,  -109
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    93,    94,    95,    48,    35,    49,    50,    36,    52,
      37,    38,   144,    39,    40,    41,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    47,    44,    71,   145,    54,   147,     1,    59,   150,
     156,    55,   103,    64,    63,   103,   157,    65,    51,   113,
       9,   160,     1,     2,     3,     4,     5,   103,     6,    45,
      46,   166,   169,   146,   103,     9,   127,   103,   103,    10,
     102,   101,    11,    12,   103,    53,   132,    96,   163,    97,
      23,    60,   107,    13,    61,   108,   109,    98,    16,    17,
      18,    66,    75,    76,    47,    23,    77,    67,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,    47,   128,    71,    86,   152,    87,   131,    70,    99,
      68,    47,   133,    69,    88,    89,    56,    58,   137,   159,
      73,    74,    75,    76,    57,    57,    77,   100,    78,    79,
      80,    81,    82,    83,    84,   168,    85,   104,   154,   155,
     105,    20,   111,   129,   112,   130,    86,   134,    87,    46,
      47,   153,   135,   143,   140,   149,    88,    89,     7,   167,
     162,   158,    90,    91,    47,    92,   170,   164,     1,     2,
       3,     4,     5,   106,     6,   138,     7,   139,     8,     0,
      47,     9,     0,     0,     0,    10,     0,     0,    11,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,    14,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     1,     2,     3,     4,     5,     0,     6,
       0,     7,     0,     8,     0,     0,     9,     0,     0,     0,
      10,     0,     0,    11,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,    14,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     1,     2,
       3,     4,     5,     0,     6,     0,     0,     0,     0,     0,
       0,     9,     0,     0,     0,    10,     0,     0,    11,    12,
      73,    74,    75,    76,     0,     0,    77,     0,     0,    13,
      -1,    -1,    -1,    -1,    16,    17,    18,     0,    20,     0,
       0,    23,     1,     2,     3,     4,     5,     0,     6,     0,
       0,     0,    62,     0,     0,     9,     0,     0,     0,    10,
       0,     0,    11,    12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     0,     0,     0,    16,    17,
      18,     0,     0,     0,     0,    23,     1,     2,     3,     4,
       5,     0,     6,     0,     0,     0,     0,     0,     0,     9,
       0,     0,     0,    10,     0,     0,    11,    12,     0,     0,
       0,     0,     0,     0,   141,     0,     0,    13,     0,     0,
       0,     0,    16,    17,    18,    73,    74,    75,    76,    23,
       0,    77,   142,    78,    79,    80,    81,    82,    83,    84,
       0,    85,     0,    73,    74,    75,    76,     0,     0,    77,
       0,    78,    79,    80,    81,    82,    83,    84,   148,    85,
       0,     0,     0,     0,     0,     0,     0,    73,    74,    75,
      76,     0,     0,    77,     0,    78,    79,    80,    81,    82,
      83,    84,   151,    85,     0,     0,     0,     0,     0,     0,
       0,    73,    74,    75,    76,     0,     0,    77,     0,    78,
      79,    80,    81,    82,    83,    84,   161,    85,     0,     0,
       0,     0,     0,    73,    74,    75,    76,     0,     0,    77,
       0,    78,    79,    80,    81,    82,    83,    84,    72,    85,
       0,     0,     0,     0,    73,    74,    75,    76,     0,     0,
      77,     0,    78,    79,    80,    81,    82,    83,    84,   110,
      85,     0,     0,     0,     0,    73,    74,    75,    76,     0,
       0,    77,     0,    78,    79,    80,    81,    82,    83,    84,
     165,    85,     0,     0,     0,     0,    73,    74,    75,    76,
       0,     0,    77,     0,    78,    79,    80,    81,    82,    83,
      84,   136,    85,     0,     0,    73,    74,    75,    76,     0,
       0,    77,     0,    78,    79,    80,    81,    82,    83,    84,
       0,    85,    73,    74,    75,    76,     0,     0,    77,     0,
      78,    79,    80,    81,    82,    83,    84,     0,    85,    73,
      74,    75,    76,     0,     0,    77,     0,    78,    79,    80,
      81,    82,    83,    84,    73,    74,    75,    76,     0,     0,
      77,     0,    -1,    -1,    80,    81,    82,    83,    73,    74,
      75,    76,     0,     0,    77,     0,    78,    79,    80,    81,
      82,    83
};

static const yytype_int16 yycheck[] =
{
       5,     6,     5,    26,   112,    10,     8,     3,    13,     8,
       8,     7,    14,     3,    19,    14,    14,     7,    12,    69,
      16,     8,     3,     4,     5,     6,     7,    14,     9,    10,
      11,     8,     8,    13,    14,    16,    86,    14,    14,    20,
      10,    46,    23,    24,    14,     3,    96,     7,   156,     9,
      46,     7,    55,    34,     7,    60,    61,    17,    39,    40,
      41,    13,    21,    22,    69,    46,    25,    13,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,   106,     7,   135,     9,    92,     0,     8,
       3,    96,    97,     7,    17,    18,    11,    12,   103,   149,
      19,    20,    21,    22,    11,    12,    25,     8,    27,    28,
      29,    30,    31,    32,    33,   165,    35,    10,   141,   142,
      14,    43,     7,     3,     8,     3,     7,     3,     9,    11,
     135,   136,     7,     3,     8,     7,    17,    18,    11,   162,
      37,   146,    23,    24,   149,    26,   169,     3,     3,     4,
       5,     6,     7,    52,     9,   105,    11,    12,    13,    -1,
     165,    16,    -1,    -1,    -1,    20,    -1,    -1,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      -1,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     3,     4,     5,     6,     7,    -1,     9,
      -1,    11,    -1,    13,    -1,    -1,    16,    -1,    -1,    -1,
      20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     3,     4,
       5,     6,     7,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    20,    -1,    -1,    23,    24,
      19,    20,    21,    22,    -1,    -1,    25,    -1,    -1,    34,
      29,    30,    31,    32,    39,    40,    41,    -1,    43,    -1,
      -1,    46,     3,     4,     5,     6,     7,    -1,     9,    -1,
      -1,    -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,     3,     4,     5,     6,
       7,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    -1,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    39,    40,    41,    19,    20,    21,    22,    46,
      -1,    25,     8,    27,    28,    29,    30,    31,    32,    33,
      -1,    35,    -1,    19,    20,    21,    22,    -1,    -1,    25,
      -1,    27,    28,    29,    30,    31,    32,    33,    10,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    -1,    -1,    25,    -1,    27,    28,    29,    30,    31,
      32,    33,    10,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    -1,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    33,    12,    35,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    -1,    -1,    25,
      -1,    27,    28,    29,    30,    31,    32,    33,    13,    35,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    -1,    -1,
      25,    -1,    27,    28,    29,    30,    31,    32,    33,    13,
      35,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    -1,
      -1,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      13,    35,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      -1,    -1,    25,    -1,    27,    28,    29,    30,    31,    32,
      33,    15,    35,    -1,    -1,    19,    20,    21,    22,    -1,
      -1,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      -1,    35,    19,    20,    21,    22,    -1,    -1,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    -1,    35,    19,
      20,    21,    22,    -1,    -1,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    19,    20,    21,    22,    -1,    -1,
      25,    -1,    27,    28,    29,    30,    31,    32,    19,    20,
      21,    22,    -1,    -1,    25,    -1,    27,    28,    29,    30,
      31,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    11,    13,    16,
      20,    23,    24,    34,    36,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    65,    68,    70,    71,    73,
      74,    75,    76,    54,    70,    10,    11,    54,    64,    66,
      67,    12,    69,     3,    54,     7,    58,    60,    58,    54,
       7,     7,    13,    54,     3,     7,    13,    13,     3,     7,
       0,    53,    13,    19,    20,    21,    22,    25,    27,    28,
      29,    30,    31,    32,    33,    35,     7,     9,    17,    18,
      23,    24,    26,    61,    62,    63,     7,     9,    17,     8,
       8,    54,    10,    14,    10,    14,    52,    70,    54,    54,
      13,     7,     8,    64,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    64,    54,     3,
       3,    54,    64,    54,     3,     7,    15,    54,    67,    12,
       8,     8,     8,     3,    72,    68,    13,     8,    10,     7,
       8,    10,    64,    54,    53,    53,     8,    14,    54,    64,
       8,    12,    37,    68,     3,    13,     8,    53,    64,     8,
      53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    63,
      64,    64,    65,    65,    65,    66,    66,    67,    69,    68,
      68,    70,    70,    71,    71,    71,    71,    71,    71,    72,
      72,    73,    73,    74,    75,    76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       1,     3,     3,     3,     2,     1,     3,     5,     0,     4,
       2,     6,     4,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     7,     5,     9,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */


/* User initialization code.  */
#line 40 "syntax.y"
{   
    yacc_out = fopen("yacc_output.txt", "w");
}

#line 1160 "syntax.cpp"

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmts  */
#line 135 "syntax.y"
                                                        { fprintf(yacc_out,"liststmt -> stmt\n"); fclose(yacc_out);}
#line 1363 "syntax.cpp"
    break;

  case 3: /* program: %empty  */
#line 136 "syntax.y"
                                                      { fprintf(yacc_out,"empty program\n"); fclose(yacc_out);}
#line 1369 "syntax.cpp"
    break;

  case 4: /* stmts: stmt  */
#line 139 "syntax.y"
                                                        { fprintf(yacc_out,"liststmt -> liststmt stmt\n");}
#line 1375 "syntax.cpp"
    break;

  case 5: /* stmts: stmts stmt  */
#line 140 "syntax.y"
                                                        { fprintf(yacc_out,"liststmt -> stmt\n");}
#line 1381 "syntax.cpp"
    break;

  case 6: /* stmt: expression ";"  */
#line 143 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> expr;\n");}
#line 1387 "syntax.cpp"
    break;

  case 7: /* stmt: ifstmt  */
#line 144 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> ifstmt;\n");}
#line 1393 "syntax.cpp"
    break;

  case 8: /* stmt: whilestmt  */
#line 145 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> whilestmt;\n");}
#line 1399 "syntax.cpp"
    break;

  case 9: /* stmt: forstmt  */
#line 146 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> forstmt;\n");}
#line 1405 "syntax.cpp"
    break;

  case 10: /* stmt: returnstmt  */
#line 147 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> returnstmt;\n");}
#line 1411 "syntax.cpp"
    break;

  case 11: /* stmt: "break" ";"  */
#line 148 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> breakstmt;\n");}
#line 1417 "syntax.cpp"
    break;

  case 12: /* stmt: "continue" ";"  */
#line 149 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> continuestmt;\n");}
#line 1423 "syntax.cpp"
    break;

  case 13: /* stmt: block  */
#line 150 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> blockstmt;\n");}
#line 1429 "syntax.cpp"
    break;

  case 14: /* stmt: funcdef  */
#line 151 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> functstmt;\n");}
#line 1435 "syntax.cpp"
    break;

  case 15: /* stmt: ";"  */
#line 152 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> semicolon;\n");}
#line 1441 "syntax.cpp"
    break;

  case 16: /* expression: assignexpr  */
#line 156 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> assignexpr\n");}
#line 1447 "syntax.cpp"
    break;

  case 17: /* expression: term  */
#line 157 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> term\n");}
#line 1453 "syntax.cpp"
    break;

  case 18: /* expression: expression "+" expression  */
#line 158 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> +\n");}
#line 1459 "syntax.cpp"
    break;

  case 19: /* expression: expression "-" expression  */
#line 159 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> -\n");}
#line 1465 "syntax.cpp"
    break;

  case 20: /* expression: expression "*" expression  */
#line 160 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> *\n");}
#line 1471 "syntax.cpp"
    break;

  case 21: /* expression: expression "/" expression  */
#line 161 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> /\n");}
#line 1477 "syntax.cpp"
    break;

  case 22: /* expression: expression "%" expression  */
#line 162 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> %\n");}
#line 1483 "syntax.cpp"
    break;

  case 23: /* expression: expression "==" expression  */
#line 164 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> ==\n");}
#line 1489 "syntax.cpp"
    break;

  case 24: /* expression: expression "!=" expression  */
#line 165 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> !=\n");}
#line 1495 "syntax.cpp"
    break;

  case 25: /* expression: expression "<" expression  */
#line 166 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> <\n");}
#line 1501 "syntax.cpp"
    break;

  case 26: /* expression: expression ">" expression  */
#line 167 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> >\n");}
#line 1507 "syntax.cpp"
    break;

  case 27: /* expression: expression "<=" expression  */
#line 168 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> <=\n");}
#line 1513 "syntax.cpp"
    break;

  case 28: /* expression: expression ">=" expression  */
#line 169 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> >=\n");}
#line 1519 "syntax.cpp"
    break;

  case 29: /* expression: expression "and" expression  */
#line 171 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> AND\n");}
#line 1525 "syntax.cpp"
    break;

  case 30: /* expression: expression "or" expression  */
#line 172 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> OR\n");}
#line 1531 "syntax.cpp"
    break;

  case 31: /* term: "(" expression ")"  */
#line 175 "syntax.y"
                                                              { fprintf(yacc_out,"expr -> (term)\n");}
#line 1537 "syntax.cpp"
    break;

  case 32: /* term: "-" expression  */
#line 176 "syntax.y"
                                                              { fprintf(yacc_out,"expr -> -term\n");}
#line 1543 "syntax.cpp"
    break;

  case 33: /* term: "not" expression  */
#line 177 "syntax.y"
                                                              { fprintf(yacc_out,"expr -> !term\n");}
#line 1549 "syntax.cpp"
    break;

  case 34: /* term: "++" lvalue  */
#line 178 "syntax.y"
                                                        {   if ((yyvsp[0].symbol_P) != NULL && (yyvsp[0].symbol_P)->type != USER_FUNC && (yyvsp[0].symbol_P)->type != LIB_FUNC) {
                                                                 fprintf(yacc_out, "term -> PLUS_PLUS lvalue\n");}
                                                             else if ((yyvsp[0].symbol_P)->type == USER_FUNC || (yyvsp[0].symbol_P)->type == LIB_FUNC) {
                                                                 cout << (stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
#line 1559 "syntax.cpp"
    break;

  case 35: /* term: lvalue "++"  */
#line 183 "syntax.y"
                                                         {   if ((yyvsp[-1].symbol_P) != NULL && (yyvsp[-1].symbol_P)->type != USER_FUNC && (yyvsp[-1].symbol_P)->type != LIB_FUNC) {
                                                                 fprintf(yacc_out, "term -> lvalue PLUS_PLUS\n");}
                                                             else if ((yyvsp[-1].symbol_P)->type == USER_FUNC || (yyvsp[-1].symbol_P)->type == LIB_FUNC) {
                                                                 cout << (stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
#line 1569 "syntax.cpp"
    break;

  case 36: /* term: "--" lvalue  */
#line 188 "syntax.y"
                                                         {   if ((yyvsp[0].symbol_P) != NULL && (yyvsp[0].symbol_P)->type != USER_FUNC && (yyvsp[0].symbol_P)->type != LIB_FUNC) {
                                                                 fprintf(yacc_out, "term -> MINUS_MINUS lvalue\n");}
                                                             else if ((yyvsp[0].symbol_P)->type == USER_FUNC || (yyvsp[0].symbol_P)->type == LIB_FUNC) {
                                                                 cout << (stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
#line 1579 "syntax.cpp"
    break;

  case 37: /* term: lvalue "--"  */
#line 193 "syntax.y"
                                                         {   if ((yyvsp[-1].symbol_P) != NULL && (yyvsp[-1].symbol_P)->type != USER_FUNC && (yyvsp[-1].symbol_P)->type != LIB_FUNC) {
                                                                 fprintf(yacc_out, "term -> lvalue MINUS_MINUS\n");}
                                                             else if ((yyvsp[-1].symbol_P)->type == USER_FUNC || (yyvsp[-1].symbol_P)->type == LIB_FUNC) {
                                                                 cout << (stderr, "ERROR at line %d, with scope %d: Can't use a function as lvalue\n", yylineno, scope);
                                                             } }
#line 1589 "syntax.cpp"
    break;

  case 38: /* term: primary  */
#line 198 "syntax.y"
                                                              { fprintf(yacc_out,"expr -> primary\n");}
#line 1595 "syntax.cpp"
    break;

  case 39: /* assignexpr: lvalue "=" expression  */
#line 201 "syntax.y"
                                                              { }
#line 1601 "syntax.cpp"
    break;

  case 40: /* primary: lvalue  */
#line 203 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> lvalue\n");}
#line 1607 "syntax.cpp"
    break;

  case 41: /* primary: call  */
#line 204 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> call\n");}
#line 1613 "syntax.cpp"
    break;

  case 42: /* primary: objectdef  */
#line 205 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> objectdef\n");}
#line 1619 "syntax.cpp"
    break;

  case 43: /* primary: "(" funcdef ")"  */
#line 206 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> (funcdef)\n");}
#line 1625 "syntax.cpp"
    break;

  case 44: /* primary: const  */
#line 207 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> const\n");}
#line 1631 "syntax.cpp"
    break;

  case 45: /* lvalue: ID  */
#line 211 "syntax.y"
                                                        { symbolTable.lvalue_default((yyvsp[0].stringConst),symbolTable.currentScope,yylineno,(yyval.symbol_P)->type);
                                                          fprintf(yacc_out,"lvalue -> id\n");                                        }
#line 1638 "syntax.cpp"
    break;

  case 46: /* lvalue: "local" ID  */
#line 213 "syntax.y"
                                                        { symbolTable.local_lvalue((yyvsp[0].stringConst),symbolTable.currentScope,yylineno,(yyval.symbol_P)->type);
                                                          fprintf(yacc_out,"lvalue -> local id\n");}
#line 1645 "syntax.cpp"
    break;

  case 47: /* lvalue: "::" ID  */
#line 215 "syntax.y"
                                                        { symbolTable.local_lvalue((yyvsp[0].stringConst),0,yylineno,(yyval.symbol_P)->type);
                                                          fprintf(yacc_out,"lvalue -> global id\n");}
#line 1652 "syntax.cpp"
    break;

  case 48: /* lvalue: member  */
#line 217 "syntax.y"
                                                        { fprintf(yacc_out,"lvalue -> id\n");}
#line 1658 "syntax.cpp"
    break;

  case 49: /* member: lvalue "." ID  */
#line 220 "syntax.y"
                                                        { fprintf(yacc_out,"member -> lvalue.id\n");}
#line 1664 "syntax.cpp"
    break;

  case 50: /* member: lvalue "[" expression "]"  */
#line 221 "syntax.y"
                                                              {fprintf(yacc_out,"member -> lvalue[expr]\n"); }
#line 1670 "syntax.cpp"
    break;

  case 51: /* member: call "." ID  */
#line 222 "syntax.y"
                                                        { fprintf(yacc_out,"member -> call.id\n");}
#line 1676 "syntax.cpp"
    break;

  case 52: /* member: call "[" expression "]"  */
#line 223 "syntax.y"
                                                              { fprintf(yacc_out,"member -> call[expr]\n");}
#line 1682 "syntax.cpp"
    break;

  case 53: /* call: call "(" elist ")"  */
#line 226 "syntax.y"
                                                            { }
#line 1688 "syntax.cpp"
    break;

  case 54: /* call: lvalue callsuffix  */
#line 227 "syntax.y"
                                                            { }
#line 1694 "syntax.cpp"
    break;

  case 55: /* call: "(" funcdef ")" "(" elist ")"  */
#line 228 "syntax.y"
                                                                                                  { }
#line 1700 "syntax.cpp"
    break;

  case 56: /* callsuffix: normcall  */
#line 231 "syntax.y"
                                                        { }
#line 1706 "syntax.cpp"
    break;

  case 57: /* callsuffix: methodcall  */
#line 232 "syntax.y"
                                                        { }
#line 1712 "syntax.cpp"
    break;

  case 58: /* normcall: "(" elist ")"  */
#line 235 "syntax.y"
                                                        { }
#line 1718 "syntax.cpp"
    break;

  case 59: /* methodcall: ".." ID "(" elist ")"  */
#line 237 "syntax.y"
                                                                        { }
#line 1724 "syntax.cpp"
    break;

  case 60: /* elist: expression  */
#line 239 "syntax.y"
                                                              { }
#line 1730 "syntax.cpp"
    break;

  case 61: /* elist: elist "," expression  */
#line 240 "syntax.y"
                                                              { }
#line 1736 "syntax.cpp"
    break;

  case 62: /* objectdef: "[" elist "]"  */
#line 243 "syntax.y"
                                                        { }
#line 1742 "syntax.cpp"
    break;

  case 63: /* objectdef: "[" indexed "]"  */
#line 244 "syntax.y"
                                                        { }
#line 1748 "syntax.cpp"
    break;

  case 64: /* objectdef: "[" "]"  */
#line 245 "syntax.y"
                                                        { }
#line 1754 "syntax.cpp"
    break;

  case 65: /* indexed: indexedelem  */
#line 248 "syntax.y"
                                                        { }
#line 1760 "syntax.cpp"
    break;

  case 66: /* indexed: indexedelem "," indexedelem  */
#line 249 "syntax.y"
                                                        { }
#line 1766 "syntax.cpp"
    break;

  case 67: /* indexedelem: "{" expression ":" expression "}"  */
#line 251 "syntax.y"
                                                                         { }
#line 1772 "syntax.cpp"
    break;

  case 68: /* $@1: %empty  */
#line 253 "syntax.y"
                     {
         symbolTable.enterScope();
         fprintf(yacc_out, "Entered block scope %d\n", symbolTable.currentScope);
         
       }
#line 1782 "syntax.cpp"
    break;

  case 69: /* block: "{" $@1 stmts "}"  */
#line 259 "syntax.y"
                      {
         symbolTable.exitScope();
         fprintf(yacc_out, "Exited block scope %d\n", symbolTable.currentScope);
       }
#line 1791 "syntax.cpp"
    break;

  case 70: /* block: "{" "}"  */
#line 264 "syntax.y"
                                    {
         fprintf(yacc_out, "Empty block\n");
       }
#line 1799 "syntax.cpp"
    break;

  case 71: /* funcdef: "function" ID "(" idlist ")" block  */
#line 269 "syntax.y"
                                                                        { fprintf(yacc_out, "function id (idlist) block\n");}
#line 1805 "syntax.cpp"
    break;

  case 72: /* funcdef: "function" "(" ")" block  */
#line 270 "syntax.y"
                                                                        { }
#line 1811 "syntax.cpp"
    break;

  case 73: /* const: INT  */
#line 273 "syntax.y"
                                                        { }
#line 1817 "syntax.cpp"
    break;

  case 74: /* const: REAL  */
#line 274 "syntax.y"
                                                        { }
#line 1823 "syntax.cpp"
    break;

  case 75: /* const: STRING  */
#line 275 "syntax.y"
                                                        { }
#line 1829 "syntax.cpp"
    break;

  case 76: /* const: "nil"  */
#line 276 "syntax.y"
                                                        { }
#line 1835 "syntax.cpp"
    break;

  case 77: /* const: "true"  */
#line 277 "syntax.y"
                                                        { }
#line 1841 "syntax.cpp"
    break;

  case 78: /* const: "false"  */
#line 278 "syntax.y"
                                                        { }
#line 1847 "syntax.cpp"
    break;

  case 79: /* idlist: ID  */
#line 281 "syntax.y"
                                                        { }
#line 1853 "syntax.cpp"
    break;

  case 80: /* idlist: idlist "," ID  */
#line 282 "syntax.y"
                                                        { }
#line 1859 "syntax.cpp"
    break;

  case 81: /* ifstmt: "if" "(" expression ")" stmt  */
#line 285 "syntax.y"
                                                                                    { }
#line 1865 "syntax.cpp"
    break;

  case 82: /* ifstmt: "if" "(" expression ")" stmt "else" stmt  */
#line 286 "syntax.y"
                                                                         { }
#line 1871 "syntax.cpp"
    break;

  case 83: /* whilestmt: "while" "(" expression ")" stmt  */
#line 289 "syntax.y"
                                                                          { }
#line 1877 "syntax.cpp"
    break;

  case 84: /* forstmt: "for" "(" elist ";" expression ";" elist ")" stmt  */
#line 291 "syntax.y"
                                                                                                      { }
#line 1883 "syntax.cpp"
    break;

  case 85: /* returnstmt: "return" expression ";"  */
#line 293 "syntax.y"
                                                               { }
#line 1889 "syntax.cpp"
    break;

  case 86: /* returnstmt: "return" ";"  */
#line 294 "syntax.y"
                                                               { }
#line 1895 "syntax.cpp"
    break;


#line 1899 "syntax.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 297 "syntax.y"



