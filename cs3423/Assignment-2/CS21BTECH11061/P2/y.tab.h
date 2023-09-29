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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define NUM 259
#define STRINGVAL 260
#define CHARVAL 261
#define BOOLVAL 262
#define INT 263
#define VOID 264
#define BOOL 265
#define STRING 266
#define CHAR 267
#define FLOAT 268
#define SCOPE 269
#define CLASS 270
#define DECLARE 271
#define EXPR 272
#define CALL 273
#define RETURN 274
#define THIS 275
#define LBRACK 276
#define RBRACK 277
#define LBRACE 278
#define RBRACE 279
#define LPAREN 280
#define RPAREN 281
#define SEMICOLON 282
#define COMMA 283
#define COLON 284
#define WHILE 285
#define FOR 286
#define DO 287
#define INCASE 288
#define OTHERWISE 289
#define LOOP 290
#define UNAOP 291
#define EQUAL 292
#define ARROW 293
#define BINOP 294
#define LOGICOP 295
#define PREDOP 296
#define NEG 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
