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
    // #include "quad.h"
    // #include "expression"
    int yylex();
    FILE* yacc_out;
    extern int yylineno;
    extern char* yytext;
    int scope = 0;
    int max_scope = 0;
    extern SymbolTable symbolTable; 
    static int anonCount = 0;
    int localOffset = 0;
    int tmpCount = 0;
    int loopCounter = 0;
    // vector<int> continueList;
    // vector<int> breakList;

#line 95 "syntax.cpp"

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
  YYSYMBOL_TRUE = 7,                       /* TRUE  */
  YYSYMBOL_FALSE = 8,                      /* FALSE  */
  YYSYMBOL_LEFT_PARENTHESIS = 9,           /* "("  */
  YYSYMBOL_RIGHT_PARENTHESIS = 10,         /* ")"  */
  YYSYMBOL_LEFT_BRACKET = 11,              /* "["  */
  YYSYMBOL_RIGHT_BRACKET = 12,             /* "]"  */
  YYSYMBOL_LEFT_CBRACKET = 13,             /* "{"  */
  YYSYMBOL_RIGHT_CBRACKET = 14,            /* "}"  */
  YYSYMBOL_SEMICOLON = 15,                 /* ";"  */
  YYSYMBOL_COMMA = 16,                     /* ","  */
  YYSYMBOL_COLON = 17,                     /* ":"  */
  YYSYMBOL_DOUBLE_COLON = 18,              /* "::"  */
  YYSYMBOL_PERIOD = 19,                    /* "."  */
  YYSYMBOL_DOUBLE_PERIOD = 20,             /* ".."  */
  YYSYMBOL_PLUS = 21,                      /* "+"  */
  YYSYMBOL_MINUS = 22,                     /* "-"  */
  YYSYMBOL_MULTIPLY = 23,                  /* "*"  */
  YYSYMBOL_DIVIDE = 24,                    /* "/"  */
  YYSYMBOL_PLUS_PLUS = 25,                 /* "++"  */
  YYSYMBOL_MINUS_MINUS = 26,               /* "--"  */
  YYSYMBOL_MOD = 27,                       /* "%"  */
  YYSYMBOL_EQUALS = 28,                    /* "="  */
  YYSYMBOL_DOUBLE_EQUALS = 29,             /* "=="  */
  YYSYMBOL_NOT_EQUALS = 30,                /* "!="  */
  YYSYMBOL_LESS = 31,                      /* "<"  */
  YYSYMBOL_GREATER = 32,                   /* ">"  */
  YYSYMBOL_LESS_EQUALS = 33,               /* "<="  */
  YYSYMBOL_GREATER_EQUALS = 34,            /* ">="  */
  YYSYMBOL_AND = 35,                       /* "and"  */
  YYSYMBOL_NOT = 36,                       /* "not"  */
  YYSYMBOL_OR = 37,                        /* "or"  */
  YYSYMBOL_IF = 38,                        /* "if"  */
  YYSYMBOL_ELSE = 39,                      /* "else"  */
  YYSYMBOL_WHILE = 40,                     /* "while"  */
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
  YYSYMBOL_71_2 = 71,                      /* $@2  */
  YYSYMBOL_72_3 = 72,                      /* $@3  */
  YYSYMBOL_73_4 = 73,                      /* $@4  */
  YYSYMBOL_74_5 = 74,                      /* $@5  */
  YYSYMBOL_const = 75,                     /* const  */
  YYSYMBOL_idlist = 76,                    /* idlist  */
  YYSYMBOL_ifprefix = 77,                  /* ifprefix  */
  YYSYMBOL_elseprefix = 78,                /* elseprefix  */
  YYSYMBOL_ifstmt = 79,                    /* ifstmt  */
  YYSYMBOL_whileflag = 80,                 /* whileflag  */
  YYSYMBOL_startwhile = 81,                /* startwhile  */
  YYSYMBOL_loop = 82,                      /* loop  */
  YYSYMBOL_83_6 = 83,                      /* $@6  */
  YYSYMBOL_84_7 = 84,                      /* $@7  */
  YYSYMBOL_whilestmt = 85,                 /* whilestmt  */
  YYSYMBOL_N = 86,                         /* N  */
  YYSYMBOL_M = 87,                         /* M  */
  YYSYMBOL_forprefix = 88,                 /* forprefix  */
  YYSYMBOL_forstmt = 89,                   /* forstmt  */
  YYSYMBOL_returnstmt = 90                 /* returnstmt  */
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
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   686

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

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
       0,   178,   178,   182,   185,   188,   197,   202,   206,   210,
     213,   217,   222,   227,   231,   235,   240,   247,   248,   249,
     252,   255,   258,   261,   265,   268,   271,   274,   277,   280,
     284,   287,   292,   295,   298,   302,   307,   311,   315,   319,
     323,   327,   328,   329,   330,   331,   335,   341,   347,   353,
     356,   359,   362,   363,   366,   388,   411,   432,   435,   439,
     441,   454,   458,   465,   471,   487,   500,   501,   512,   519,
     519,   531,   536,   562,   536,   578,   591,   578,   611,   614,
     617,   620,   621,   624,   629,   630,   652,   677,   681,   685,
     691,   698,   701,   704,   704,   704,   707,   711,   715,   717,
     721,   725,   726
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
  "REAL", "TRUE", "FALSE", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"",
  "\"}\"", "\";\"", "\",\"", "\":\"", "\"::\"", "\".\"", "\"..\"", "\"+\"",
  "\"-\"", "\"*\"", "\"/\"", "\"++\"", "\"--\"", "\"%\"", "\"=\"",
  "\"==\"", "\"!=\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"and\"",
  "\"not\"", "\"or\"", "\"if\"", "\"else\"", "\"while\"", "\"nil\"",
  "\"return\"", "\"function\"", "\"break\"", "\"continue\"", "\"local\"",
  "\"for\"", "NEGATIVE_VAL", "LOWER_THAN_ELSE", "$accept", "program",
  "stmts", "stmt", "expression", "term", "assignexpr", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "objectdef", "indexed", "indexedelem", "block", "$@1", "funcdef", "$@2",
  "$@3", "$@4", "$@5", "const", "idlist", "ifprefix", "elseprefix",
  "ifstmt", "whileflag", "startwhile", "loop", "$@6", "$@7", "whilestmt",
  "N", "M", "forprefix", "forstmt", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-159)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     298,  -159,  -159,  -159,  -159,  -159,  -159,   100,   343,     4,
    -159,    18,   413,    10,    10,   413,    20,  -159,  -159,   387,
       6,    12,    72,    96,    91,   102,   298,  -159,   543,  -159,
    -159,  -159,   104,  -159,    24,  -159,  -159,  -159,  -159,   298,
    -159,   101,  -159,  -159,  -159,  -159,    15,   106,   413,   621,
      -2,   107,    98,  -159,   298,  -159,  -159,    78,    11,    24,
      11,  -159,   413,  -159,   564,   103,  -159,  -159,  -159,  -159,
     413,  -159,  -159,  -159,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   124,
     125,  -159,  -159,   413,  -159,  -159,  -159,   413,   413,   130,
     105,   413,  -159,   413,  -159,   128,   604,  -159,   413,  -159,
     122,   163,   132,   434,  -159,  -159,   137,    69,    38,    38,
    -159,  -159,  -159,   638,   638,   349,   349,   349,   349,   652,
     126,     1,   476,  -159,   136,   621,    16,   500,  -159,  -159,
     298,   452,  -159,   298,    41,   413,   413,   621,  -159,  -159,
     128,  -159,   137,  -159,    43,  -159,  -159,  -159,   413,  -159,
    -159,  -159,  -159,  -159,  -159,    48,   522,    50,   139,   151,
     413,    73,  -159,  -159,  -159,  -159,   149,  -159,  -159,   585,
    -159,  -159,  -159,   298,  -159,  -159,   298,   208,   253,  -159,
    -159
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    46,    80,    78,    79,    82,    83,     0,    61,    69,
      15,     0,     0,     0,     0,     0,     0,    92,    81,     0,
       0,     0,     0,     0,     0,     0,     2,     4,     0,    18,
      17,    39,    41,    49,    42,    43,    13,    14,    45,    16,
       7,     0,     8,    97,     9,    10,     0,     0,     0,    63,
       0,     0,    66,    71,    16,    48,    33,     0,    35,     0,
      37,    34,     0,   102,     0,     0,    75,    11,    12,    47,
      61,     1,     5,     6,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,    36,    38,     0,    55,    57,    58,    61,     0,     0,
      90,     0,    93,    61,    32,    44,     0,    64,     0,    65,
       0,     0,     0,     0,   101,    72,    84,     0,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     0,     0,    50,     0,    40,     0,     0,    52,    88,
      16,     0,    96,    16,     0,    61,     0,    62,    67,    70,
       0,    87,    84,    85,     0,    98,    59,    51,    61,    54,
      53,    89,    91,    94,    97,     0,     0,     0,     0,     0,
       0,     0,    95,    93,    56,    68,     0,    76,    86,     0,
      60,    97,    73,    16,    99,   100,    16,     0,     0,    77,
      74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,   -52,   -23,    -7,  -159,  -159,  -159,    79,  -159,
      84,  -159,  -159,  -159,   -63,  -159,  -159,    63,  -159,  -159,
      -3,  -159,  -159,  -159,  -159,  -159,    23,  -159,  -159,  -159,
    -159,  -159,     7,  -159,  -159,  -159,  -158,  -159,  -159,  -159,
    -159
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    94,    95,    96,    50,    35,    51,    52,    36,    54,
      37,   152,   186,   116,   183,    38,   154,    39,   140,    40,
     102,    41,   142,   143,   172,    42,   103,   170,    43,    44,
      45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    49,   111,    72,    47,    56,   173,   117,    61,    65,
     107,   156,    64,     1,   108,    66,   100,   108,    53,    57,
      87,    55,    88,   185,   131,   104,   159,    67,    11,    62,
      89,    90,   108,    97,   136,    98,    74,    75,    76,    77,
     144,   106,    78,    99,    79,    80,    81,    82,    83,    84,
      85,   164,    86,   168,   112,   113,    23,   108,   174,   169,
     176,    76,    77,    49,   108,    78,   169,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
      49,   132,   165,   180,   155,   108,   135,    68,    72,   108,
      49,   137,    58,    60,   141,   171,    49,    59,    59,    69,
      70,   147,    71,     1,     2,     3,     4,     5,     6,     7,
     101,     8,   115,    87,   110,    88,   105,   161,    11,   109,
     163,    20,    12,    89,    90,    13,    14,   133,   134,    91,
      92,   187,    93,   138,   188,    48,    15,   145,    49,   166,
     153,    18,   150,    20,   139,   158,    23,    74,    75,    76,
      77,    49,   177,    78,   178,    79,    80,    81,    82,    83,
      84,    85,   182,   179,    72,    72,     1,     2,     3,     4,
       5,     6,     7,   148,     8,   167,     9,   149,    10,     0,
     181,    11,     0,     0,     0,    12,     0,     0,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
       0,    16,     0,    17,    18,    19,    20,    21,    22,    23,
      24,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       0,     9,   189,    10,     0,     0,    11,     0,     0,     0,
      12,     0,     0,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,    16,     0,    17,    18,
      19,    20,    21,    22,    23,    24,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     0,     9,   190,    10,     0,
       0,    11,     0,     0,     0,    12,     0,     0,    13,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
       0,    16,     0,    17,    18,    19,    20,    21,    22,    23,
      24,     1,     2,     3,     4,     5,     6,     7,     0,     8,
       0,     9,     0,    10,     0,     0,    11,     0,     0,     0,
      12,     0,     0,    13,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,    16,     0,    17,    18,
      19,    20,    21,    22,    23,    24,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     0,    48,     0,     0,     0,
       0,    11,     0,     0,     0,    12,     0,     0,    13,    14,
      74,    75,    76,    77,     0,     0,    78,     0,     0,    15,
      -1,    -1,    -1,    -1,    18,     0,     0,     0,     0,    23,
       1,     2,     3,     4,     5,     6,     7,     0,     8,     0,
       0,     0,    63,     0,     0,    11,     0,     0,     0,    12,
       0,     0,    13,    14,     0,     0,     1,     2,     3,     4,
       5,     6,     7,    15,     8,     0,     0,     0,    18,     0,
       0,    11,     0,    23,     0,    12,     0,     0,    13,    14,
       0,     0,     0,     0,   151,     0,     0,     0,     0,    15,
       0,     0,     0,     0,    18,    74,    75,    76,    77,    23,
       0,    78,   162,    79,    80,    81,    82,    83,    84,    85,
       0,    86,     0,    74,    75,    76,    77,     0,     0,    78,
       0,    79,    80,    81,    82,    83,    84,    85,   157,    86,
       0,     0,     0,     0,     0,     0,     0,    74,    75,    76,
      77,     0,     0,    78,     0,    79,    80,    81,    82,    83,
      84,    85,   160,    86,     0,     0,     0,     0,     0,     0,
       0,    74,    75,    76,    77,     0,     0,    78,     0,    79,
      80,    81,    82,    83,    84,    85,   175,    86,     0,     0,
       0,     0,     0,    74,    75,    76,    77,     0,     0,    78,
       0,    79,    80,    81,    82,    83,    84,    85,    73,    86,
       0,     0,     0,     0,    74,    75,    76,    77,     0,     0,
      78,     0,    79,    80,    81,    82,    83,    84,    85,   114,
      86,     0,     0,     0,     0,    74,    75,    76,    77,     0,
       0,    78,     0,    79,    80,    81,    82,    83,    84,    85,
     184,    86,     0,     0,     0,     0,    74,    75,    76,    77,
       0,     0,    78,     0,    79,    80,    81,    82,    83,    84,
      85,   146,    86,     0,     0,    74,    75,    76,    77,     0,
       0,    78,     0,    79,    80,    81,    82,    83,    84,    85,
       0,    86,    74,    75,    76,    77,     0,     0,    78,     0,
      79,    80,    81,    82,    83,    84,    85,     0,    86,    74,
      75,    76,    77,     0,     0,    78,     0,    -1,    -1,    81,
      82,    83,    84,    74,    75,    76,    77,     0,     0,    78,
       0,    79,    80,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
       7,     8,    54,    26,     7,    12,   164,    70,    15,     3,
      12,    10,    19,     3,    16,     9,    39,    16,    14,     9,
       9,     3,    11,   181,    87,    10,    10,    15,    18,     9,
      19,    20,    16,     9,    97,    11,    21,    22,    23,    24,
     103,    48,    27,    19,    29,    30,    31,    32,    33,    34,
      35,    10,    37,    10,    57,    62,    46,    16,    10,    16,
      10,    23,    24,    70,    16,    27,    16,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   145,    10,    15,    16,    93,    15,   111,    16,
      97,    98,    13,    14,   101,   158,   103,    13,    14,     3,
       9,   108,     0,     3,     4,     5,     6,     7,     8,     9,
       9,    11,     9,     9,    16,    11,    10,   140,    18,    12,
     143,    43,    22,    19,    20,    25,    26,     3,     3,    25,
      26,   183,    28,     3,   186,    13,    36,     9,   145,   146,
       3,    41,    10,    43,    39,     9,    46,    21,    22,    23,
      24,   158,    13,    27,     3,    29,    30,    31,    32,    33,
      34,    35,    13,   170,   187,   188,     3,     4,     5,     6,
       7,     8,     9,   110,    11,   152,    13,    14,    15,    -1,
     173,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    46,
      47,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      -1,    13,    14,    15,    -1,    -1,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    -1,    13,    14,    15,    -1,
      -1,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    46,
      47,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      -1,    13,    -1,    15,    -1,    -1,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    -1,    13,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      21,    22,    23,    24,    -1,    -1,    27,    -1,    -1,    36,
      31,    32,    33,    34,    41,    -1,    -1,    -1,    -1,    46,
       3,     4,     5,     6,     7,     8,     9,    -1,    11,    -1,
      -1,    -1,    15,    -1,    -1,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    36,    11,    -1,    -1,    -1,    41,    -1,
      -1,    18,    -1,    46,    -1,    22,    -1,    -1,    25,    26,
      -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    41,    21,    22,    23,    24,    46,
      -1,    27,    10,    29,    30,    31,    32,    33,    34,    35,
      -1,    37,    -1,    21,    22,    23,    24,    -1,    -1,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    12,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    -1,    -1,    27,    -1,    29,    30,    31,    32,    33,
      34,    35,    12,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    23,    24,    -1,    -1,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    14,    37,    -1,    -1,
      -1,    -1,    -1,    21,    22,    23,    24,    -1,    -1,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    15,    37,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    -1,    -1,
      27,    -1,    29,    30,    31,    32,    33,    34,    35,    15,
      37,    -1,    -1,    -1,    -1,    21,    22,    23,    24,    -1,
      -1,    27,    -1,    29,    30,    31,    32,    33,    34,    35,
      15,    37,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    27,    -1,    29,    30,    31,    32,    33,    34,
      35,    17,    37,    -1,    -1,    21,    22,    23,    24,    -1,
      -1,    27,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    37,    21,    22,    23,    24,    -1,    -1,    27,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    21,
      22,    23,    24,    -1,    -1,    27,    -1,    29,    30,    31,
      32,    33,    34,    21,    22,    23,    24,    -1,    -1,    27,
      -1,    29,    30,    31,    32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    13,
      15,    18,    22,    25,    26,    36,    38,    40,    41,    42,
      43,    44,    45,    46,    47,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    65,    68,    70,    75,    77,
      79,    81,    85,    88,    89,    90,    54,    70,    13,    54,
      64,    66,    67,    14,    69,     3,    54,     9,    58,    60,
      58,    54,     9,    15,    54,     3,     9,    15,    15,     3,
       9,     0,    53,    15,    21,    22,    23,    24,    27,    29,
      30,    31,    32,    33,    34,    35,    37,     9,    11,    19,
      20,    25,    26,    28,    61,    62,    63,     9,    11,    19,
      53,     9,    80,    86,    10,    10,    54,    12,    16,    12,
      16,    52,    70,    54,    15,     9,    73,    64,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    64,    54,     3,     3,    54,    64,    54,     3,    39,
      78,    54,    82,    83,    64,     9,    17,    54,    67,    14,
      10,    10,    71,     3,    76,    15,    10,    12,     9,    10,
      12,    53,    10,    53,    10,    64,    54,    76,    10,    16,
      87,    64,    84,    86,    10,    14,    10,    13,     3,    54,
      10,    82,    13,    74,    15,    86,    72,    52,    52,    14,
      14
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    64,    64,    64,    65,    65,    66,    66,    67,    69,
      68,    68,    71,    72,    70,    73,    74,    70,    75,    75,
      75,    75,    75,    75,    76,    76,    76,    77,    78,    79,
      79,    80,    81,    83,    84,    82,    85,    86,    87,    88,
      89,    90,    90
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     0,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     1,
       3,     1,     1,     1,     3,     1,     1,     2,     2,     1,
       3,     4,     3,     4,     4,     2,     6,     1,     1,     3,
       5,     0,     3,     1,     3,     3,     1,     3,     5,     0,
       4,     2,     0,     0,    10,     0,     0,     9,     1,     1,
       1,     1,     1,     1,     0,     1,     3,     4,     1,     4,
       2,     3,     1,     0,     0,     3,     3,     0,     0,     7,
       7,     3,     2
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
#line 50 "syntax.y"
{   
    yacc_out = fopen("yacc_output.txt", "w");
}

#line 1212 "syntax.cpp"

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
#line 178 "syntax.y"
                                                        { 
                                                          (yyval.statement) = (yyvsp[0].statement);
                                                          fprintf(yacc_out,"liststmt -> stmt\n"); fclose(yacc_out);
                                                        }
#line 1418 "syntax.cpp"
    break;

  case 3: /* program: %empty  */
#line 182 "syntax.y"
                                                        { fprintf(yacc_out,"empty program\n"); fclose(yacc_out);}
#line 1424 "syntax.cpp"
    break;

  case 4: /* stmts: stmt  */
#line 185 "syntax.y"
                                                        { fprintf(yacc_out,"liststmt -> liststmt stmt\n");
                                                          (yyval.statement) = (yyvsp[0].statement);
                                                        }
#line 1432 "syntax.cpp"
    break;

  case 5: /* stmts: stmts stmt  */
#line 188 "syntax.y"
                                                        { 
                                                          (yyval.statement) = initLists();
                                                          (yyval.statement)->continueLabel = mergeList((yyvsp[-1].statement)->continueLabel,(yyvsp[0].statement)->continueLabel);
                                                          (yyval.statement)-> returnLabel = mergeList((yyvsp[-1].statement)->returnLabel,(yyvsp[0].statement)->returnLabel);
                                                          (yyval.statement)->breakLabel = mergeList((yyvsp[-1].statement)->breakLabel,(yyvsp[0].statement)->breakLabel);
                                                          fprintf(yacc_out,"liststmt -> stmt\n");
                                                        }
#line 1444 "syntax.cpp"
    break;

  case 6: /* stmt: expression ";"  */
#line 197 "syntax.y"
                                                        { 
                                                          (yyval.statement) = initLists();
                                                          tmpCount = 0;
                                                          fprintf(yacc_out,"stmt -> expr;\n");
                                                        }
#line 1454 "syntax.cpp"
    break;

  case 7: /* stmt: ifstmt  */
#line 202 "syntax.y"
                                                        { (yyval.statement) = (yyvsp[0].statement);
                                                          fprintf(yacc_out,"stmt -> ifstmt;\n");
                                                          tmpCount = 0;
                                                        }
#line 1463 "syntax.cpp"
    break;

  case 8: /* stmt: whilestmt  */
#line 206 "syntax.y"
                                                        { 
                                                          (yyval.statement) = initLists();
                                                          fprintf(yacc_out,"stmt -> whilestmt;\n");
                                                        }
#line 1472 "syntax.cpp"
    break;

  case 9: /* stmt: forstmt  */
#line 210 "syntax.y"
                                                        { 
                                                          (yyval.statement) = initLists();
                                                          fprintf(yacc_out,"stmt -> forstmt;\n");}
#line 1480 "syntax.cpp"
    break;

  case 10: /* stmt: returnstmt  */
#line 213 "syntax.y"
                                                        { 
                                                          (yyval.statement) = setStmtList(2);
                                                          fprintf(yacc_out,"stmt -> returnstmt;\n");
                                                        }
#line 1489 "syntax.cpp"
    break;

  case 11: /* stmt: "break" ";"  */
#line 217 "syntax.y"
                                                        { 
                                                          (yyval.statement) = setStmtList(0);
                                                          tmpCount = 0;
                                                          fprintf(yacc_out,"stmt -> breakstmt;\n");
                                                        }
#line 1499 "syntax.cpp"
    break;

  case 12: /* stmt: "continue" ";"  */
#line 222 "syntax.y"
                                                        { 
                                                          fprintf(yacc_out,"stmt -> continuestmt;\n");
                                                          tmpCount = 0;
                                                          (yyval.statement) = setStmtList(1);
                                                        }
#line 1509 "syntax.cpp"
    break;

  case 13: /* stmt: block  */
#line 227 "syntax.y"
                                                        { fprintf(yacc_out,"stmt -> blockstmt;\n");
                                                          tmpCount = 0;
                                                          (yyval.statement) = (yyvsp[0].statement);
                                                        }
#line 1518 "syntax.cpp"
    break;

  case 14: /* stmt: funcdef  */
#line 231 "syntax.y"
                                                        { 
                                                          fprintf(yacc_out,"stmt -> functstmt;\n");
                                                          (yyval.statement) = initLists();
                                                        }
#line 1527 "syntax.cpp"
    break;

  case 15: /* stmt: ";"  */
#line 235 "syntax.y"
                                                        { 
                                                          fprintf(yacc_out,"stmt -> semicolon;\n");
                                                          (yyval.statement) = initLists();
                                                          tmpCount = 0;
                                                        }
#line 1537 "syntax.cpp"
    break;

  case 16: /* stmt: %empty  */
#line 240 "syntax.y"
                                                        { 
                                                          fprintf(yacc_out,"stmt -> empty;\n");
                                                          (yyval.statement) = initLists(); //evala ayto
                                                        }
#line 1546 "syntax.cpp"
    break;

  case 17: /* expression: assignexpr  */
#line 247 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> assignexpr\n");}
#line 1552 "syntax.cpp"
    break;

  case 18: /* expression: term  */
#line 248 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> term\n");}
#line 1558 "syntax.cpp"
    break;

  case 19: /* expression: expression "+" expression  */
#line 249 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> +\n");
                                                           (yyval.exprV) = evaluateNumber((yyvsp[-2].exprV), (yyvsp[0].exprV), add);
                                                        }
#line 1566 "syntax.cpp"
    break;

  case 20: /* expression: expression "-" expression  */
#line 252 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> -\n");
                                                           (yyval.exprV) = evaluateNumber((yyvsp[-2].exprV), (yyvsp[0].exprV), sub);
                                                        }
#line 1574 "syntax.cpp"
    break;

  case 21: /* expression: expression "*" expression  */
#line 255 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> *\n");
                                                           (yyval.exprV) = evaluateNumber((yyvsp[-2].exprV), (yyvsp[0].exprV), mul);
                                                        }
#line 1582 "syntax.cpp"
    break;

  case 22: /* expression: expression "/" expression  */
#line 258 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> /\n");
                                                           (yyval.exprV) = evaluateNumber((yyvsp[-2].exprV), (yyvsp[0].exprV), div_op);
                                                        }
#line 1590 "syntax.cpp"
    break;

  case 23: /* expression: expression "%" expression  */
#line 261 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> %%\n");
                                                           (yyval.exprV) = evaluateNumber((yyvsp[-2].exprV), (yyvsp[0].exprV), mod);
                                                        }
#line 1598 "syntax.cpp"
    break;

  case 24: /* expression: expression "==" expression  */
#line 265 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> ==\n");
                                                         (yyval.exprV) = evaluateBoolean((yyvsp[-2].exprV),(yyvsp[0].exprV),if_eq);
                                                        }
#line 1606 "syntax.cpp"
    break;

  case 25: /* expression: expression "!=" expression  */
#line 268 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> !=\n");
                                                          (yyval.exprV) = evaluateBoolean((yyvsp[-2].exprV),(yyvsp[0].exprV),if_noteq);
                                                        }
#line 1614 "syntax.cpp"
    break;

  case 26: /* expression: expression "<" expression  */
#line 271 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> <\n");
                                                          (yyval.exprV) = evaluateBoolean((yyvsp[-2].exprV),(yyvsp[0].exprV),if_less);
                                                        }
#line 1622 "syntax.cpp"
    break;

  case 27: /* expression: expression ">" expression  */
#line 274 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> >\n");
                                                          (yyval.exprV) = evaluateBoolean((yyvsp[-2].exprV),(yyvsp[0].exprV),if_greater);
                                                        }
#line 1630 "syntax.cpp"
    break;

  case 28: /* expression: expression "<=" expression  */
#line 277 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> <=\n");
                                                          (yyval.exprV) = evaluateBoolean((yyvsp[-2].exprV),(yyvsp[0].exprV),if_lesseq);
                                                        }
#line 1638 "syntax.cpp"
    break;

  case 29: /* expression: expression ">=" expression  */
#line 280 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> >=\n");
                                                          (yyval.exprV) = evaluateBoolean((yyvsp[-2].exprV),(yyvsp[0].exprV),if_greatereq);
                                                        }
#line 1646 "syntax.cpp"
    break;

  case 30: /* expression: expression "and" expression  */
#line 284 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> AND\n");
                                                          evaluateAND_OR((yyvsp[-2].exprV),(yyvsp[0].exprV),and_op);
                                                        }
#line 1654 "syntax.cpp"
    break;

  case 31: /* expression: expression "or" expression  */
#line 287 "syntax.y"
                                                        { fprintf(yacc_out,"expr -> OR\n");
                                                          evaluateAND_OR((yyvsp[-2].exprV),(yyvsp[0].exprV),or_op);  
                                                        }
#line 1662 "syntax.cpp"
    break;

  case 32: /* term: "(" expression ")"  */
#line 292 "syntax.y"
                                                              { fprintf(yacc_out,"expr -> (term)\n");
                                                                (yyval.exprV) = (yyvsp[-1].exprV);
                                                              }
#line 1670 "syntax.cpp"
    break;

  case 33: /* term: "-" expression  */
#line 295 "syntax.y"
                                                              { fprintf(yacc_out,"expr -> -term\n");
                                                                (yyval.exprV) = evaluateUminus((yyvsp[0].exprV));
                                                              }
#line 1678 "syntax.cpp"
    break;

  case 34: /* term: "not" expression  */
#line 298 "syntax.y"
                                                              {
                                                               fprintf(yacc_out,"expr -> !term\n");
                                                               (yyval.exprV) = evaluateNOT((yyvsp[0].exprV));
                                                              }
#line 1687 "syntax.cpp"
    break;

  case 35: /* term: "++" lvalue  */
#line 302 "syntax.y"
                                                              {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                (yyval.exprV) = evaluatePP(oneoneoneone, (yyvsp[0].exprV), false, add); //antrea ,dua lipa kosovo 1 , 2 i 3 augoustoy 
                                                                // ELA NA KLEISOYME TWRA EISITIRIA
                                                              }
#line 1697 "syntax.cpp"
    break;

  case 36: /* term: lvalue "++"  */
#line 307 "syntax.y"
                                                              {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                (yyval.exprV) = evaluatePP((yyvsp[-1].exprV), oneoneoneone, true, add);
                                                              }
#line 1706 "syntax.cpp"
    break;

  case 37: /* term: "--" lvalue  */
#line 311 "syntax.y"
                                                              {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                (yyval.exprV) = evaluatePP(oneoneoneone, (yyvsp[0].exprV), false, sub);
                                                              }
#line 1715 "syntax.cpp"
    break;

  case 38: /* term: lvalue "--"  */
#line 315 "syntax.y"
                                                              {
                                                                expr* oneoneoneone = newIntExpr(1);
                                                                (yyval.exprV) = evaluatePP((yyvsp[-1].exprV), oneoneoneone, true, sub);
                                                              }
#line 1724 "syntax.cpp"
    break;

  case 39: /* term: primary  */
#line 319 "syntax.y"
                                                              { (yyval.exprV) = (yyvsp[0].exprV);
                                                                fprintf(yacc_out,"expr -> primary\n");}
#line 1731 "syntax.cpp"
    break;

  case 40: /* assignexpr: lvalue "=" expression  */
#line 323 "syntax.y"
                                                              { 
                                                                (yyval.exprV) = evaluateAssignExp((yyvsp[-2].exprV), (yyvsp[0].exprV));
                                                              }
#line 1739 "syntax.cpp"
    break;

  case 41: /* primary: lvalue  */
#line 327 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> lvalue\n");}
#line 1745 "syntax.cpp"
    break;

  case 42: /* primary: call  */
#line 328 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> call\n");}
#line 1751 "syntax.cpp"
    break;

  case 43: /* primary: objectdef  */
#line 329 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> objectdef\n");}
#line 1757 "syntax.cpp"
    break;

  case 44: /* primary: "(" funcdef ")"  */
#line 330 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> (funcdef)\n");}
#line 1763 "syntax.cpp"
    break;

  case 45: /* primary: const  */
#line 331 "syntax.y"
                                                        { fprintf(yacc_out,"primary -> const\n");}
#line 1769 "syntax.cpp"
    break;

  case 46: /* lvalue: ID  */
#line 335 "syntax.y"
                                                        { 
                                                          // Symbol *s = symbolTable.lvalue_default($1,symbolTable.currentScope,yylineno);
                                                          // fprintf(yacc_out,"lvalue -> id\n");
                                                          // $$ = symToExpr(s);
                                                          (yyval.exprV) = lvaluesIncert((yyvsp[0].stringConst),3);
                                                        }
#line 1780 "syntax.cpp"
    break;

  case 47: /* lvalue: "local" ID  */
#line 341 "syntax.y"
                                                        { 
                                                          // Symbol *s = symbolTable.local_lvalue($2,symbolTable.currentScope,yylineno);
                                                          // fprintf(yacc_out,"lvalue -> local id\n");
                                                          // $$ = symToExpr(s);
                                                          (yyval.exprV) = lvaluesIncert((yyvsp[0].stringConst),2);
                                                        }
#line 1791 "syntax.cpp"
    break;

  case 48: /* lvalue: "::" ID  */
#line 347 "syntax.y"
                                                        { 
                                                          // Symbol *s = symbolTable.local_lvalue($2,0,yylineno);
                                                          // fprintf(yacc_out,"lvalue -> global id\n");
                                                          // $$ = symToExpr(s);
                                                          (yyval.exprV) = lvaluesIncert((yyvsp[0].stringConst),1);
                                                        }
#line 1802 "syntax.cpp"
    break;

  case 49: /* lvalue: member  */
#line 353 "syntax.y"
                                                        { fprintf(yacc_out,"lvalue -> id\n");}
#line 1808 "syntax.cpp"
    break;

  case 50: /* member: lvalue "." ID  */
#line 356 "syntax.y"
                                                        { fprintf(yacc_out,"member -> lvalue.id\n");
                                                          (yyval.exprV) = tablePeriodId((yyvsp[-2].exprV), (yyvsp[0].stringConst));
                                                        }
#line 1816 "syntax.cpp"
    break;

  case 51: /* member: lvalue "[" expression "]"  */
#line 359 "syntax.y"
                                                              {fprintf(yacc_out,"member -> lvalue[expr]\n"); 
                                                                (yyval.exprV) = tableBrackets((yyvsp[-3].exprV),(yyvsp[-1].exprV));
                                                              }
#line 1824 "syntax.cpp"
    break;

  case 52: /* member: call "." ID  */
#line 362 "syntax.y"
                                                        { fprintf(yacc_out,"member -> call.id\n");}
#line 1830 "syntax.cpp"
    break;

  case 53: /* member: call "[" expression "]"  */
#line 363 "syntax.y"
                                                              { fprintf(yacc_out,"member -> call[expr]\n");}
#line 1836 "syntax.cpp"
    break;

  case 54: /* call: call "(" elist ")"  */
#line 366 "syntax.y"
                                                            {
              expr* current = (yyvsp[-1].exprV);
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
              emit(call, nullptr, nullptr, (yyvsp[-3].exprV));

              expr* result = newTempExpr();
              emit(getretval, nullptr, nullptr, result);
              (yyval.exprV) = result;

 }
#line 1863 "syntax.cpp"
    break;

  case 55: /* call: lvalue callsuffix  */
#line 388 "syntax.y"
                                                            {
              expr* current = (yyvsp[0].exprV);
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
              expr* e_tmp = newNillExpr();

              emit(call, nullptr, nullptr, (yyvsp[-1].exprV));

              expr* result = newTempExpr();
              emit(getretval, nullptr, nullptr, result);
              (yyval.exprV) = result;
             }
#line 1891 "syntax.cpp"
    break;

  case 56: /* call: "(" funcdef ")" "(" elist ")"  */
#line 411 "syntax.y"
                                                                                                  {
              expr* current = (yyvsp[-1].exprV);
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
                  
                  emit(call, nullptr, nullptr, nullptr,(yyvsp[-4].statement));
                  emit(getretval, nullptr, nullptr, result);
                  (yyval.exprV) = result;
             }
#line 1915 "syntax.cpp"
    break;

  case 57: /* callsuffix: normcall  */
#line 432 "syntax.y"
                                                        {(yyval.exprV) = (yyvsp[0].exprV);
                                                          fprintf(yacc_out,"callsuffix -> normcall\n");
                                                        }
#line 1923 "syntax.cpp"
    break;

  case 58: /* callsuffix: methodcall  */
#line 435 "syntax.y"
                                                        {(yyval.exprV) = (yyvsp[0].exprV);
                                                          fprintf(yacc_out,"callsuffix -> methodcall\n");
                                                        }
#line 1931 "syntax.cpp"
    break;

  case 59: /* normcall: "(" elist ")"  */
#line 439 "syntax.y"
                                                        {(yyval.exprV) =(yyvsp[-1].exprV);}
#line 1937 "syntax.cpp"
    break;

  case 60: /* methodcall: ".." ID "(" elist ")"  */
#line 441 "syntax.y"
                                                                        {
                                                                           expr* current = (yyvsp[-1].exprV);
                                                                           int  paramCount = 0;
                                                                           expr* last = nullptr;
                                                                           while (current) {
                                                                               paramCount++;
                                                                               if (current->next) {
                                                                                   last = current;
                                                                                   current = current->next;
                                                                               }
                                                                           }
                                                                           (yyval.exprV) = (yyvsp[-1].exprV); }
#line 1954 "syntax.cpp"
    break;

  case 61: /* elist: %empty  */
#line 454 "syntax.y"
                                                              { (yyval.exprV) = nullptr; 
                                                                fprintf(yacc_out,"elist -> null;\n");
                                                              }
#line 1962 "syntax.cpp"
    break;

  case 62: /* elist: elist "," expression  */
#line 458 "syntax.y"
                                                              {
                                                                while((yyvsp[-2].exprV)->next){
                                                                  (yyvsp[-2].exprV) = (yyvsp[-2].exprV)-> next;
                                                                }
                                                                (yyvsp[-2].exprV)->next = (yyvsp[0].exprV);
                                                                (yyvsp[0].exprV)->prev = (yyvsp[-2].exprV);
                                                              }
#line 1974 "syntax.cpp"
    break;

  case 63: /* elist: expression  */
#line 465 "syntax.y"
                                                              { (yyval.exprV) = (yyvsp[0].exprV);
                                                                (yyval.exprV)->next = nullptr;
                                                                (yyval.exprV)->prev = nullptr;
                                                                }
#line 1983 "syntax.cpp"
    break;

  case 64: /* objectdef: "[" elist "]"  */
#line 471 "syntax.y"
                                                        { 
                                                          expr* tmpExpr = newTempExpr();
                                                          tmpExpr->type = newtable_e;
                                                          emit(tablecreate, nullptr, nullptr, tmpExpr);
                                                          if((yyvsp[-1].exprV)){
                                                              expr* current = (yyvsp[-1].exprV);
                                                              int i = 0;
                                                              while (current) {
                                                                  expr* indexExpr = newIntExpr(i++);
                                                                  emit(tablesetelem, indexExpr, current,tmpExpr);
                                                                  current = current->next;
                                                              }
                                                          }
                                                          (yyval.exprV) = tmpExpr;
                                                          fprintf(yacc_out, "objectdef -> [ elist ]\n");
                                                        }
#line 2004 "syntax.cpp"
    break;

  case 65: /* objectdef: "[" indexed "]"  */
#line 487 "syntax.y"
                                                        { 
                                                          expr* tmpExpr = newTempExpr();
                                                          tmpExpr->type = newtable_e;
                                                          emit(tablecreate, nullptr, nullptr, tmpExpr);
                                                          expr* current = (yyvsp[-1].exprV);
                                                          while(current) {
                                                              emit(tablesetelem, current->index, current,tmpExpr);
                                                              current = current->next;
                                                          }
                                                          (yyval.exprV) = tmpExpr;
                                                        }
#line 2020 "syntax.cpp"
    break;

  case 66: /* indexed: indexedelem  */
#line 500 "syntax.y"
                                                        { (yyval.exprV) = (yyvsp[0].exprV);}
#line 2026 "syntax.cpp"
    break;

  case 67: /* indexed: indexedelem "," indexedelem  */
#line 501 "syntax.y"
                                                        { 
                                                        expr* current = (yyvsp[-2].exprV);
                                                        while(current->next) {
                                                            current = current->next;
                                                        }
                                                        current->next = (yyvsp[0].exprV);
                                                        (yyvsp[0].exprV)->prev = current;
                                                        (yyval.exprV) = (yyvsp[-2].exprV);
                                                        }
#line 2040 "syntax.cpp"
    break;

  case 68: /* indexedelem: "{" expression ":" expression "}"  */
#line 512 "syntax.y"
                                                                        { 
                                                                          (yyval.exprV) = (yyvsp[-1].exprV);
                                                                          (yyval.exprV)->index = (yyvsp[-3].exprV);
                                                                          (yyval.exprV)->next = nullptr;
                                                                          (yyval.exprV)->prev = nullptr; 
                                                                        }
#line 2051 "syntax.cpp"
    break;

  case 69: /* $@1: %empty  */
#line 519 "syntax.y"
                     {
         symbolTable.enterScope();
         fprintf(yacc_out, "Entered block scope %d\n", symbolTable.currentScope);
         
       }
#line 2061 "syntax.cpp"
    break;

  case 70: /* block: "{" $@1 stmts "}"  */
#line 525 "syntax.y"
                      {
         symbolTable.exitScope();
         fprintf(yacc_out, "Exited block scope %d\n", symbolTable.currentScope);
         (yyval.statement) = (yyvsp[-1].statement);
       }
#line 2071 "syntax.cpp"
    break;

  case 71: /* block: "{" "}"  */
#line 531 "syntax.y"
                                    {
         fprintf(yacc_out, "Empty block\n");
       }
#line 2079 "syntax.cpp"
    break;

  case 72: /* $@2: %empty  */
#line 536 "syntax.y"
                                         {
              localOffset = -1;
             Symbol *s = symbolTable.lookupInScope((yyvsp[-1].stringConst), symbolTable.currentScope);
              if(s!= nullptr){
                fprintf(stderr, "ERROR at line %d, with scope %d: function %s already declared\n", yylineno, symbolTable.currentScope, (yyvsp[-1].stringConst));
              } else {
               vector <Symbol*> temp_sym = symbolTable.lookup((yyvsp[-1].stringConst));
               bool isLib = false;
                for (auto& sym : temp_sym) {
                    if (sym->type == LIB_FUNC) {
                        isLib = true;
                        break;
                    }
                }
                if (isLib) {
                    fprintf(stderr, "ERROR at line %d, with scope %d: function %s already declared as a library function\n", yylineno, symbolTable.currentScope, (yyvsp[-1].stringConst));
                } else {
                   Symbol *s = symbolTable.insert((yyvsp[-1].stringConst), symbolTable.currentScope, yylineno, USER_FUNC);
                   s->setIaddress(nextquad());
                   emit(funcstart, nullptr, nullptr, symToExpr(s));
                   fprintf(yacc_out, "funcdef -> function %s\n", (yyvsp[-1].stringConst));
                }
              }
               int functionScope = symbolTable.currentScope + 1;
               if (s) s->setFuncScope(functionScope);
            }
#line 2110 "syntax.cpp"
    break;

  case 73: /* $@3: %empty  */
#line 562 "syntax.y"
                                                   {
              symbolTable.enterScope();
              fprintf(yacc_out, "Entered function body scope %d\n", symbolTable.currentScope);
            }
#line 2119 "syntax.cpp"
    break;

  case 74: /* funcdef: "function" ID "(" $@2 idlist ")" "{" $@3 stmts "}"  */
#line 567 "syntax.y"
                           { 
              Symbol *s = symbolTable.lookup((yyvsp[-8].stringConst))[0];
              if (s && s->type == USER_FUNC) {
                int funcScope = s->getFuncScope();
                unsigned int localCount = symbolTable.getTotalLoc(funcScope);
                s->setTotalLoc(localCount);
                emit(funcend, nullptr, nullptr, symToExpr(s));
              }
              symbolTable.exitScope();
              fprintf(yacc_out, "Exited function body scope %d\n", symbolTable.currentScope);
            }
#line 2135 "syntax.cpp"
    break;

  case 75: /* $@4: %empty  */
#line 578 "syntax.y"
                                        {
                localOffset = -1;
                string name = "_f" + to_string(anonCount);
                fprintf(yacc_out, "funcdef -> function %s\n", name.c_str());
                Symbol *s = symbolTable.insert(name.c_str(), symbolTable.currentScope, yylineno, USER_FUNC);
                s->setIaddress(nextquad());
                emit(funcstart, nullptr, nullptr, symToExpr(s));
                
                int functionScope = symbolTable.currentScope + 1;
                s->setFuncScope(functionScope);
                
                anonCount++;
              }
#line 2153 "syntax.cpp"
    break;

  case 76: /* $@5: %empty  */
#line 591 "syntax.y"
                                                     {
                symbolTable.enterScope();
                fprintf(yacc_out, "Entered anonymous function body scope %d\n", symbolTable.currentScope);
              }
#line 2162 "syntax.cpp"
    break;

  case 77: /* funcdef: "function" "(" $@4 idlist ")" "{" $@5 stmts "}"  */
#line 596 "syntax.y"
                           { 
               int currentFuncIndex = anonCount - 1;
               string name = "_f" + to_string(currentFuncIndex);
               Symbol *s = symbolTable.lookup(name.c_str())[0];
               if (s && s->type == USER_FUNC) {
                   int funcScope = s->getFuncScope();
                   unsigned int localCount = symbolTable.getTotalLoc(funcScope);
                   s->setTotalLoc(localCount);
                   emit(funcend, nullptr, nullptr, symToExpr(s));
               }
               symbolTable.exitScope();
               fprintf(yacc_out, "Exited anonymous function body scope %d\n", symbolTable.currentScope);
            }
#line 2180 "syntax.cpp"
    break;

  case 78: /* const: INT  */
#line 611 "syntax.y"
                                                        { fprintf(yacc_out,"const -> number\n");
                                                          (yyval.exprV) = newIntExpr((yyvsp[0].intConst));
                                                        }
#line 2188 "syntax.cpp"
    break;

  case 79: /* const: REAL  */
#line 614 "syntax.y"
                                                        { fprintf(yacc_out,"const -> number\n");
                                                          (yyval.exprV) = newDoubleExpr((yyvsp[0].realConst));
                                                        }
#line 2196 "syntax.cpp"
    break;

  case 80: /* const: STRING  */
#line 617 "syntax.y"
                                                        { fprintf(yacc_out,"const -> string\n");
                                                          (yyval.exprV) = newStringExpr((yyvsp[0].stringConst));
                                                        }
#line 2204 "syntax.cpp"
    break;

  case 81: /* const: "nil"  */
#line 620 "syntax.y"
                                                        { fprintf(yacc_out,"const -> nil\n");}
#line 2210 "syntax.cpp"
    break;

  case 82: /* const: TRUE  */
#line 621 "syntax.y"
                                                        { fprintf(yacc_out,"const -> true\n");
                                                          (yyval.exprV) = newBoolExpr(true);
                                                        }
#line 2218 "syntax.cpp"
    break;

  case 83: /* const: FALSE  */
#line 624 "syntax.y"
                                                        { fprintf(yacc_out,"const -> false\n");
                                                          (yyval.exprV) = newBoolExpr(false);
                                                        }
#line 2226 "syntax.cpp"
    break;

  case 84: /* idlist: %empty  */
#line 629 "syntax.y"
                                              { fprintf(yacc_out, "idlist -> empty\n"); }
#line 2232 "syntax.cpp"
    break;

  case 85: /* idlist: ID  */
#line 630 "syntax.y"
                                                   { 
        Symbol *s = symbolTable.lookupInScope((yyvsp[0].stringConst), symbolTable.currentScope);
        if(s!= nullptr){
          fprintf(stderr, "ERROR at line %d : formal redeclaration '%s'\n" , yylineno, (yyvsp[0].stringConst));
          }else{
          auto temp_sym = symbolTable.lookup((yyvsp[0].stringConst));
          bool isLib = false;
          for (auto& sym : temp_sym) {
              if (sym->type == LIB_FUNC) {
                  isLib = true;
                  break;
              }
          }
          if (isLib) {
              fprintf(stderr, "ERROR at line %d : formal argument shadows library function '%s'\n", yylineno, (yyvsp[0].stringConst));
              } else {
                Symbol *param = symbolTable.insert((yyvsp[0].stringConst), symbolTable.currentScope, yylineno, FUNCTION_PARAM);
                param->setOffset(++localOffset);
                fprintf(yacc_out, "idlist -> %s ( offset 0 )\n", (yyvsp[0].stringConst));
              }
          }
       }
#line 2259 "syntax.cpp"
    break;

  case 86: /* idlist: idlist "," ID  */
#line 652 "syntax.y"
                                                   { 
        Symbol *s = symbolTable.lookupInScope((yyvsp[0].stringConst), symbolTable.currentScope);
        if(s!= nullptr){
          fprintf(stderr, "ERROR at line %d : formal redeclaration '%s'\n" , yylineno, (yyvsp[0].stringConst));
          }else{
          auto temp_sym = symbolTable.lookup((yyvsp[0].stringConst));
          bool isLib = false;
          for (auto& sym : temp_sym) {
              if (sym->type == LIB_FUNC) {
                  isLib = true;
                  break;
              }
          }
          if (isLib) {
              fprintf(stderr, "ERROR at line %d : formal argument shadows library function '%s'\n", yylineno, (yyvsp[0].stringConst));
          } else {
              
              Symbol *param = symbolTable.insert((yyvsp[0].stringConst), symbolTable.currentScope, yylineno, FUNCTION_PARAM);
              param->setOffset(++localOffset);
              fprintf(yacc_out, "idlist -> %s ( offset %d )\n", (yyvsp[0].stringConst), localOffset);
          }
        }
       }
#line 2287 "syntax.cpp"
    break;

  case 87: /* ifprefix: "if" "(" expression ")"  */
#line 677 "syntax.y"
                                                           {
                                                            (yyval.intConst) = ifPrefix((yyvsp[-1].exprV));
                                                           }
#line 2295 "syntax.cpp"
    break;

  case 88: /* elseprefix: "else"  */
#line 681 "syntax.y"
                                                           {
                                                            (yyval.intConst) = elsePrefix();
                                                           }
#line 2303 "syntax.cpp"
    break;

  case 89: /* ifstmt: ifprefix stmt elseprefix stmt  */
#line 685 "syntax.y"
                                      {
          fixLabel((yyvsp[-3].intConst),(yyvsp[-1].intConst)+1);
          int quad_counter = nextquad();
          fixLabel((yyvsp[-1].intConst),quad_counter);
          (yyval.statement) = evaluateIfElse((yyvsp[-3].intConst), (yyvsp[-1].intConst), (yyvsp[-2].statement), (yyvsp[0].statement));
        }
#line 2314 "syntax.cpp"
    break;

  case 90: /* ifstmt: ifprefix stmt  */
#line 691 "syntax.y"
                                            { 
          (yyval.statement) = (yyvsp[0].statement);
          int quad_counter = nextquad();
          fixLabel((yyvsp[-1].intConst),quad_counter);
        }
#line 2324 "syntax.cpp"
    break;

  case 91: /* whileflag: "(" expression ")"  */
#line 698 "syntax.y"
                                                          { 
                                                            (yyval.intConst) = setWhileCont((yyvsp[-1].exprV));
                                                          }
#line 2332 "syntax.cpp"
    break;

  case 92: /* startwhile: "while"  */
#line 701 "syntax.y"
                                                          { 
                                                            jumpStartWhile((yyval.intConst)); 
                                                          }
#line 2340 "syntax.cpp"
    break;

  case 93: /* $@6: %empty  */
#line 704 "syntax.y"
      { incLoop(); }
#line 2346 "syntax.cpp"
    break;

  case 94: /* $@7: %empty  */
#line 704 "syntax.y"
                          { decLoop(); }
#line 2352 "syntax.cpp"
    break;

  case 95: /* loop: $@6 stmt $@7  */
#line 704 "syntax.y"
                                                          {
                                                            (yyval.statement) = (yyvsp[-1].statement);
                                                          }
#line 2360 "syntax.cpp"
    break;

  case 96: /* whilestmt: startwhile whileflag loop  */
#line 707 "syntax.y"
                                                          {      
                                                            (yyval.statement) = evaluateWhile((yyvsp[-1].intConst),(yyvsp[0].statement),(yyvsp[-2].intConst));
                                                          }
#line 2368 "syntax.cpp"
    break;

  case 97: /* N: %empty  */
#line 711 "syntax.y"
         {  (yyval.intConst) = nextquad();
      emit(jump, nullptr, nullptr, nullptr, nextquad());
    }
#line 2376 "syntax.cpp"
    break;

  case 98: /* M: %empty  */
#line 715 "syntax.y"
         {  (yyval.intConst) = nextquad();  }
#line 2382 "syntax.cpp"
    break;

  case 99: /* forprefix: "for" "(" elist ";" M expression ";"  */
#line 717 "syntax.y"
                                                                       {
                                                                          (yyval.forCnst) = evaluateForPrefix((yyvsp[-1].exprV),(yyvsp[-2].intConst));
                                                                        }
#line 2390 "syntax.cpp"
    break;

  case 100: /* forstmt: forprefix N elist ")" N loop N  */
#line 721 "syntax.y"
                                                                       {
                                                                          (yyval.statement) = evaluateFor((yyvsp[-6].forCnst),(yyvsp[-5].intConst) ,(yyvsp[-1].statement),(yyvsp[-2].intConst),(yyvsp[0].intConst));
                                                                       }
#line 2398 "syntax.cpp"
    break;

  case 101: /* returnstmt: "return" expression ";"  */
#line 725 "syntax.y"
                                                               { }
#line 2404 "syntax.cpp"
    break;

  case 102: /* returnstmt: "return" ";"  */
#line 726 "syntax.y"
                                                               { }
#line 2410 "syntax.cpp"
    break;


#line 2414 "syntax.cpp"

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

#line 729 "syntax.y"



