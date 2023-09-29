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
#line 1 "parse.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Defining yylex
int yylex();

// Defining error functions
int yyerror(char *s);
void parerror();

// Extern all required variables to use in lex
extern int yylineno;
extern FILE* PARFILE;
extern FILE* TOKFILE;
extern FILE* yyin;
extern char *yytext;
extern void writenl();

// Defining the enum for the parser
enum stat{funcdef, classdef, decstat, exprstat, callstat, callstatobj, loopstat, condstat, retstat};

// Defining the function to write to the parser file
void writedef(enum stat);

// Defining the struct for the log checking whether the current statement is in function/class and whether it has a return statement
struct log{
    bool isfunc;
    bool isclass;
    bool ret;
};

struct log logval = {false, false, false};


#line 109 "parse.tab.c"

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
    NUM = 259,                     /* NUM  */
    STRINGVAL = 260,               /* STRINGVAL  */
    CHARVAL = 261,                 /* CHARVAL  */
    BOOLVAL = 262,                 /* BOOLVAL  */
    INT = 263,                     /* INT  */
    VOID = 264,                    /* VOID  */
    BOOL = 265,                    /* BOOL  */
    STRING = 266,                  /* STRING  */
    CHAR = 267,                    /* CHAR  */
    FLOAT = 268,                   /* FLOAT  */
    SCOPE = 269,                   /* SCOPE  */
    CLASS = 270,                   /* CLASS  */
    DECLARE = 271,                 /* DECLARE  */
    EXPR = 272,                    /* EXPR  */
    CALL = 273,                    /* CALL  */
    RETURN = 274,                  /* RETURN  */
    THIS = 275,                    /* THIS  */
    LBRACK = 276,                  /* LBRACK  */
    RBRACK = 277,                  /* RBRACK  */
    LBRACE = 278,                  /* LBRACE  */
    RBRACE = 279,                  /* RBRACE  */
    LPAREN = 280,                  /* LPAREN  */
    RPAREN = 281,                  /* RPAREN  */
    SEMICOLON = 282,               /* SEMICOLON  */
    COMMA = 283,                   /* COMMA  */
    COLON = 284,                   /* COLON  */
    WHILE = 285,                   /* WHILE  */
    FOR = 286,                     /* FOR  */
    DO = 287,                      /* DO  */
    INCASE = 288,                  /* INCASE  */
    OTHERWISE = 289,               /* OTHERWISE  */
    LOOP = 290,                    /* LOOP  */
    UNAOP = 291,                   /* UNAOP  */
    EQUAL = 292,                   /* EQUAL  */
    ARROW = 293,                   /* ARROW  */
    BINOP = 294,                   /* BINOP  */
    LOGICOP = 295,                 /* LOGICOP  */
    PREDOP = 296,                  /* PREDOP  */
    NEG = 297                      /* NEG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_STRINGVAL = 5,                  /* STRINGVAL  */
  YYSYMBOL_CHARVAL = 6,                    /* CHARVAL  */
  YYSYMBOL_BOOLVAL = 7,                    /* BOOLVAL  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_BOOL = 10,                      /* BOOL  */
  YYSYMBOL_STRING = 11,                    /* STRING  */
  YYSYMBOL_CHAR = 12,                      /* CHAR  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_SCOPE = 14,                     /* SCOPE  */
  YYSYMBOL_CLASS = 15,                     /* CLASS  */
  YYSYMBOL_DECLARE = 16,                   /* DECLARE  */
  YYSYMBOL_EXPR = 17,                      /* EXPR  */
  YYSYMBOL_CALL = 18,                      /* CALL  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_THIS = 20,                      /* THIS  */
  YYSYMBOL_LBRACK = 21,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 22,                    /* RBRACK  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 25,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 26,                    /* RPAREN  */
  YYSYMBOL_SEMICOLON = 27,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_COLON = 29,                     /* COLON  */
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_FOR = 31,                       /* FOR  */
  YYSYMBOL_DO = 32,                        /* DO  */
  YYSYMBOL_INCASE = 33,                    /* INCASE  */
  YYSYMBOL_OTHERWISE = 34,                 /* OTHERWISE  */
  YYSYMBOL_LOOP = 35,                      /* LOOP  */
  YYSYMBOL_UNAOP = 36,                     /* UNAOP  */
  YYSYMBOL_EQUAL = 37,                     /* EQUAL  */
  YYSYMBOL_ARROW = 38,                     /* ARROW  */
  YYSYMBOL_BINOP = 39,                     /* BINOP  */
  YYSYMBOL_LOGICOP = 40,                   /* LOGICOP  */
  YYSYMBOL_PREDOP = 41,                    /* PREDOP  */
  YYSYMBOL_NEG = 42,                       /* NEG  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_input = 44,                     /* input  */
  YYSYMBOL_part = 45,                      /* part  */
  YYSYMBOL_function = 46,                  /* function  */
  YYSYMBOL_func = 47,                      /* func  */
  YYSYMBOL_class = 48,                     /* class  */
  YYSYMBOL_args = 49,                      /* args  */
  YYSYMBOL_helparg = 50,                   /* helparg  */
  YYSYMBOL_argnumber = 51,                 /* argnumber  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_classbody = 53,                 /* classbody  */
  YYSYMBOL_body = 54,                      /* body  */
  YYSYMBOL_unexp = 55,                     /* unexp  */
  YYSYMBOL_cal = 56,                       /* cal  */
  YYSYMBOL_methodarg = 57,                 /* methodarg  */
  YYSYMBOL_calobj = 58,                    /* calobj  */
  YYSYMBOL_calmet = 59,                    /* calmet  */
  YYSYMBOL_calhelper = 60,                 /* calhelper  */
  YYSYMBOL_helpcal = 61,                   /* helpcal  */
  YYSYMBOL_dec = 62,                       /* dec  */
  YYSYMBOL_helpdec = 63,                   /* helpdec  */
  YYSYMBOL_express = 64,                   /* express  */
  YYSYMBOL_exp = 65,                       /* exp  */
  YYSYMBOL_expression = 66,                /* expression  */
  YYSYMBOL_predicate = 67,                 /* predicate  */
  YYSYMBOL_unaexpression = 68,             /* unaexpression  */
  YYSYMBOL_binexpression = 69,             /* binexpression  */
  YYSYMBOL_ret = 70,                       /* ret  */
  YYSYMBOL_loop = 71,                      /* loop  */
  YYSYMBOL_loopdec = 72,                   /* loopdec  */
  YYSYMBOL_ifdec = 73,                     /* ifdec  */
  YYSYMBOL_other = 74,                     /* other  */
  YYSYMBOL_otherwise = 75                  /* otherwise  */
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   225

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  194

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    58,    58,    59,    62,    63,    66,    69,    72,    73,
      76,    77,    80,    81,    85,    88,    88,    88,    88,    88,
      88,    90,    91,    92,    93,    94,    97,    98,    99,   100,
     101,   102,   103,   106,   109,   110,   114,   115,   117,   118,
     119,   120,   123,   124,   127,   128,   131,   132,   135,   136,
     139,   140,   143,   145,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   161,   162,   165,   166,   169,
     174,   175,   178,   179,   182,   183,   184,   187,   190,   191,
     194
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUM",
  "STRINGVAL", "CHARVAL", "BOOLVAL", "INT", "VOID", "BOOL", "STRING",
  "CHAR", "FLOAT", "SCOPE", "CLASS", "DECLARE", "EXPR", "CALL", "RETURN",
  "THIS", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "SEMICOLON", "COMMA", "COLON", "WHILE", "FOR", "DO", "INCASE",
  "OTHERWISE", "LOOP", "UNAOP", "EQUAL", "ARROW", "BINOP", "LOGICOP",
  "PREDOP", "NEG", "$accept", "input", "part", "function", "func", "class",
  "args", "helparg", "argnumber", "type", "classbody", "body", "unexp",
  "cal", "methodarg", "calobj", "calmet", "calhelper", "helpcal", "dec",
  "helpdec", "express", "exp", "expression", "predicate", "unaexpression",
  "binexpression", "ret", "loop", "loopdec", "ifdec", "other", "otherwise", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-104)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      97,   156,    18,    27,    97,  -104,     6,    29,  -104,  -104,
    -104,  -104,  -104,  -104,    47,    36,  -104,  -104,   115,    -1,
      26,    58,  -104,   150,    67,    16,    19,    59,   116,    69,
      48,   115,   115,   115,   115,    81,    91,   115,   115,    73,
     117,    -1,    96,    -1,    -1,    -1,   131,  -104,   147,   151,
     171,   172,   139,    -7,   140,   153,   154,  -104,  -104,  -104,
    -104,  -104,   155,    16,    62,   158,   159,  -104,    99,  -104,
    -104,  -104,    62,   160,   161,     9,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,   164,   165,  -104,  -104,  -104,
    -104,  -104,  -104,   156,  -104,   149,   149,    62,   163,   176,
     166,   187,  -104,  -104,  -104,  -104,  -104,    33,    62,    62,
    -104,    62,    62,    37,    62,   175,   167,   168,   115,   115,
     192,   193,   170,   173,   130,  -104,    39,   152,    54,  -104,
      -8,    84,   157,  -104,  -104,   130,   177,   174,  -104,  -104,
     178,   180,   179,   149,  -104,  -104,   182,   181,  -104,  -104,
     183,   184,   188,    62,  -104,  -104,    62,  -104,   185,   156,
     186,  -104,  -104,   152,   152,   189,  -104,   152,    88,   190,
    -104,  -104,   191,   196,  -104,   183,   183,  -104,   183,  -104,
       4,   115,   179,   194,  -104,   195,  -104,   197,   198,  -104,
    -104,  -104,  -104,  -104
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     0,     2,     4,     0,     0,    15,    16,
      17,    18,    19,    20,     0,     9,     1,     3,    26,    21,
       0,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    26,    26,    26,     0,     0,    26,    26,     0,
       0,    21,     0,    21,    21,    21,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      62,    63,     0,     0,     0,     0,     0,    64,     0,    57,
      54,    55,     0,     0,     0,     0,     6,    31,    32,    27,
      28,    52,    33,    30,    29,     0,     0,    25,     5,    24,
      22,    23,    11,     0,    14,    50,    50,     0,     0,     0,
       0,     0,    34,    35,    71,    44,    45,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,    26,    26,
       0,     0,     0,     0,    53,    43,     0,     0,     0,    58,
       0,     0,    56,    65,    77,     0,    57,     0,    67,    68,
       0,     0,    12,    50,    49,    48,     0,     0,    36,    37,
      46,     0,     0,     0,    66,    74,     0,    72,    78,     0,
       0,    51,    39,     0,     0,     0,    41,     0,     0,    57,
      80,    73,     0,     0,    10,    46,    46,    42,    46,    69,
       0,    26,    12,     0,    47,     0,    76,     0,     0,    13,
      38,    40,    75,    79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -104,   201,  -104,   102,  -104,  -104,  -104,    34,   -19,   -17,
     100,   -29,    -2,  -104,   -64,   146,   162,  -104,   -40,    72,
     -89,    78,   103,   -16,  -103,   -26,  -104,  -104,  -104,  -104,
    -104,  -104,  -104
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    41,     6,     7,    47,   160,    22,    14,
      42,    30,    31,    32,   150,    55,    56,    67,   165,    33,
     122,    34,    35,   135,    69,    36,    71,    37,    38,    39,
      40,   171,   172
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      70,    48,    77,    78,    79,    80,    51,   123,    83,    84,
      68,   136,   116,     1,    21,    23,    24,    43,    98,    53,
     153,    15,    57,    58,    59,    60,    61,    16,    62,    18,
     186,    99,   111,   112,   100,    29,    54,    63,    70,    43,
      29,    43,    43,    43,    64,    29,    70,    21,   107,   117,
      20,    46,    19,   169,   161,    29,   113,    21,    65,   129,
      21,    66,    49,   134,   146,    57,    58,    59,    60,    61,
      52,    70,    76,   111,   112,    21,   120,   111,   112,   151,
      63,   124,    70,    70,    72,    70,    70,    64,    70,   140,
     141,    44,   130,   131,    75,   132,   133,    45,    29,   175,
     176,    65,     5,   178,    66,    85,     5,   147,    81,   152,
     154,     1,     2,    44,   179,    44,    44,    44,    82,    45,
      88,    45,    45,    45,   111,   112,   110,    70,   111,   112,
      70,    23,    24,    25,    26,   183,   184,   168,   185,   111,
     112,    87,   173,    89,    90,    91,    73,    74,    27,    86,
      28,    29,   188,    50,   187,   148,   149,    92,     8,     9,
      10,    11,    12,    13,     8,     9,    10,    11,    12,    13,
     111,   112,    93,    94,    95,    96,    97,   121,   101,   126,
     102,   103,   104,   108,   109,   114,   115,   118,   119,   125,
     128,   127,    24,   138,   139,   142,   143,   144,   112,   182,
     145,   156,   157,   155,   158,    17,   163,   159,   162,   105,
     166,   164,   174,   167,   181,   177,   189,   180,   137,   170,
     190,   191,   193,   192,     0,   106
};

static const yytype_int16 yycheck[] =
{
      26,    20,    31,    32,    33,    34,    23,    96,    37,    38,
      26,   114,     3,    14,    21,    16,    17,    19,    25,     3,
      28,     3,     3,     4,     5,     6,     7,     0,     9,    23,
      26,    38,    40,    41,    53,    36,    20,    18,    64,    41,
      36,    43,    44,    45,    25,    36,    72,    21,    64,    75,
       3,    25,    23,   156,   143,    36,    72,    21,    39,    26,
      21,    42,     4,    26,    25,     3,     4,     5,     6,     7,
       3,    97,    24,    40,    41,    21,    93,    40,    41,    25,
      18,    97,   108,   109,    25,   111,   112,    25,   114,   118,
     119,    19,   108,   109,    25,   111,   112,    19,    36,   163,
     164,    39,     0,   167,    42,    32,     4,   126,    27,   128,
      26,    14,    15,    41,    26,    43,    44,    45,    27,    41,
      24,    43,    44,    45,    40,    41,    27,   153,    40,    41,
     156,    16,    17,    18,    19,   175,   176,   153,   178,    40,
      41,    41,   159,    43,    44,    45,    30,    31,    33,    32,
      35,    36,   181,     3,   180,     3,     4,    26,     8,     9,
      10,    11,    12,    13,     8,     9,    10,    11,    12,    13,
      40,    41,    25,    22,     3,     3,    37,    28,    38,     3,
      27,    27,    27,    25,    25,    25,    25,    23,    23,    26,
       3,    25,    17,    26,    26,     3,     3,    27,    41,     3,
      27,    27,    24,    26,    24,     4,    25,    28,    26,    63,
      26,    28,    26,    25,    23,    26,   182,    27,   115,    34,
      26,    26,    24,    26,    -1,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    15,    44,    45,    46,    47,    48,     8,     9,
      10,    11,    12,    13,    52,     3,     0,    44,    23,    23,
       3,    21,    51,    16,    17,    18,    19,    33,    35,    36,
      54,    55,    56,    62,    64,    65,    68,    70,    71,    72,
      73,    46,    53,    55,    62,    64,    25,    49,    51,     4,
       3,    52,     3,     3,    20,    58,    59,     3,     4,     5,
       6,     7,     9,    18,    25,    39,    42,    60,    66,    67,
      68,    69,    25,    30,    31,    25,    24,    54,    54,    54,
      54,    27,    27,    54,    54,    32,    32,    53,    24,    53,
      53,    53,    26,    25,    22,     3,     3,    37,    25,    38,
      51,    38,    27,    27,    27,    58,    59,    66,    25,    25,
      27,    40,    41,    66,    25,    25,     3,    68,    23,    23,
      52,    28,    63,    63,    66,    26,     3,    25,     3,    26,
      66,    66,    66,    66,    26,    66,    67,    65,    26,    26,
      54,    54,     3,     3,    27,    27,    25,    51,     3,     4,
      57,    25,    51,    28,    26,    26,    27,    24,    24,    28,
      50,    63,    26,    25,    28,    61,    26,    25,    66,    67,
      34,    74,    75,    52,    26,    57,    57,    26,    57,    26,
      27,    23,     3,    61,    61,    61,    26,    68,    54,    50,
      26,    26,    26,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    46,    47,    48,    48,
      49,    49,    50,    50,    51,    52,    52,    52,    52,    52,
      52,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    55,    56,    56,    57,    57,    58,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    67,    68,    68,    69,
      70,    70,    71,    71,    72,    72,    72,    73,    74,    74,
      75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     4,     4,     4,     3,     2,
       6,     2,     0,     4,     3,     1,     1,     1,     1,     1,
       1,     0,     2,     2,     2,     2,     0,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     1,     1,     8,     5,
       8,     5,     6,     3,     2,     2,     0,     3,     5,     5,
       0,     3,     2,     4,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     4,     4,     4,     6,
       3,     3,     5,     6,     5,     9,     8,     4,     0,     4,
       1
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
  case 5: /* part: class LBRACE classbody RBRACE  */
#line 63 "parse.y"
                                    {logval.isclass = false; logval.ret = false;}
#line 1377 "parse.tab.c"
    break;

  case 6: /* function: func LBRACE body RBRACE  */
#line 66 "parse.y"
                                  {logval.isfunc = false; if(logval.ret == false){parerror();} logval.ret = false;}
#line 1383 "parse.tab.c"
    break;

  case 7: /* func: SCOPE type ID args  */
#line 69 "parse.y"
                         {writedef(funcdef); logval.isfunc = true;}
#line 1389 "parse.tab.c"
    break;

  case 8: /* class: CLASS ID argnumber  */
#line 72 "parse.y"
                          {writedef(classdef); logval.isclass = true;}
#line 1395 "parse.tab.c"
    break;

  case 9: /* class: CLASS ID  */
#line 73 "parse.y"
               {writedef(classdef); logval.isclass = true;}
#line 1401 "parse.tab.c"
    break;

  case 33: /* unexp: unaexpression SEMICOLON  */
#line 106 "parse.y"
                               {writedef(exprstat);}
#line 1407 "parse.tab.c"
    break;

  case 34: /* cal: CALL calobj SEMICOLON  */
#line 109 "parse.y"
                           {writedef(callstatobj);}
#line 1413 "parse.tab.c"
    break;

  case 35: /* cal: CALL calmet SEMICOLON  */
#line 110 "parse.y"
                            {writedef(callstat);}
#line 1419 "parse.tab.c"
    break;

  case 48: /* dec: DECLARE type ID helpdec SEMICOLON  */
#line 135 "parse.y"
                                       {writedef(decstat);}
#line 1425 "parse.tab.c"
    break;

  case 49: /* dec: DECLARE ID ID helpdec SEMICOLON  */
#line 136 "parse.y"
                                      {writedef(decstat);}
#line 1431 "parse.tab.c"
    break;

  case 52: /* express: exp SEMICOLON  */
#line 143 "parse.y"
                       {writedef(exprstat);}
#line 1437 "parse.tab.c"
    break;

  case 70: /* ret: RETURN expression SEMICOLON  */
#line 174 "parse.y"
                                 {writedef(retstat); logval.ret = true;}
#line 1443 "parse.tab.c"
    break;

  case 71: /* ret: RETURN VOID SEMICOLON  */
#line 175 "parse.y"
                            {writedef(retstat); logval.ret = true;}
#line 1449 "parse.tab.c"
    break;

  case 74: /* loopdec: LOOP WHILE LPAREN predicate RPAREN  */
#line 182 "parse.y"
                                            {writedef(loopstat);}
#line 1455 "parse.tab.c"
    break;

  case 75: /* loopdec: LOOP FOR LPAREN exp SEMICOLON predicate SEMICOLON unaexpression RPAREN  */
#line 183 "parse.y"
                                                                             {writedef(loopstat);}
#line 1461 "parse.tab.c"
    break;

  case 76: /* loopdec: LOOP FOR LPAREN exp SEMICOLON predicate SEMICOLON RPAREN  */
#line 184 "parse.y"
                                                               {writedef(loopstat);}
#line 1467 "parse.tab.c"
    break;

  case 77: /* ifdec: INCASE LPAREN expression RPAREN  */
#line 187 "parse.y"
                                       {writedef(condstat);}
#line 1473 "parse.tab.c"
    break;

  case 80: /* otherwise: OTHERWISE  */
#line 194 "parse.y"
                     {writedef(condstat);}
#line 1479 "parse.tab.c"
    break;


#line 1483 "parse.tab.c"

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

#line 197 "parse.y"


// Function to print error
int yyerror(char *s)
{
  extern int yylineno;	// defined and maintained in lex.c
  printf("ERROR: %s at symbol \"%s\" on line %d\n", s, yytext, yylineno);
  fprintf(PARFILE, "\nInvalid statement");
  fprintf(TOKFILE, "Invalid statement");
  exit(1);
}

// Function to print error
void parerror(){
        char *toprint = "Error at line number: ";
        fprintf(TOKFILE, "%s%d\n", toprint, yylineno);
        fprintf(PARFILE, "\nInvalid statement");
        printf("%s%d\n", toprint, yylineno);
        exit(1);
}

// Function to write newline to the parser file
void writenl(){
    fprintf(PARFILE, "\n");
}

// Function to write the definition of the statement
void writedef(enum stat x){
    fprintf(PARFILE, " : ");
    if(x == funcdef){
        fprintf(PARFILE, "function definition");
    }
    else if(x == classdef){
        fprintf(PARFILE, "class definition");
    }
    else if(x == decstat){
        fprintf(PARFILE, "declaration statement");
    }
    else if(x == exprstat){
        fprintf(PARFILE, "expression statement");
    }
    else if(x == callstat){
        fprintf(PARFILE, "call statement");
    }
    else if(x == callstatobj){
        fprintf(PARFILE, "call statement with object");
    }
    else if(x == loopstat){
        fprintf(PARFILE, "loop statement");
    }
    else if(x == condstat){
        fprintf(PARFILE, "conditional statement");
    }
    else if(x == retstat){
        fprintf(PARFILE, "return statement");
    }
}

// Main function
int main(int argc, char **argv){

    ++argv;
    --argc;


    // Defining strings for the file names
    char *TOKN = "./TP2/seq_tokens_";
    char *PARN = "./TP2/parser_";
    
    char * TOK_NAME, *PAR_NAME;

    int n = strlen(argv[0]) - 5;

    // Take the number as a substring
    char* substr = (char *)malloc(n);
    strncpy(substr, argv[0], n-1);
    substr[n-1] = '\0';

    TOK_NAME = (char *)malloc(n+30);
    PAR_NAME = (char *)malloc(n+30);

    // Set the file names
    strncpy(TOK_NAME, TOKN, 17);
    strncpy(PAR_NAME, PARN, 13);
    strncpy(TOK_NAME+17, substr, n-1);
    strncpy(PAR_NAME+13, substr, n-1);
    strncpy(TOK_NAME+17+n-1, ".txt", 4);
    strncpy(PAR_NAME+13+n-1, ".parsed", 7);

    // Remove files if present beforehand
    remove(TOK_NAME);
    remove(PAR_NAME);

    // Open the req files
    yyin = fopen( argv[0], "r" );
    TOKFILE = fopen(TOK_NAME, "w");
    PARFILE = fopen(PAR_NAME, "w");

    // Print Name and Roll Number 
    fprintf(TOKFILE, "%s\n%s\n\n","Name: Vishal Vijay Devadiga", "ID: CS21BTECH11061");

    // Call the parser
    yyparse();

    // Close the output files
    fclose(TOKFILE);
    fclose(PARFILE);
}
