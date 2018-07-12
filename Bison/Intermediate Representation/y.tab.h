/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DO = 258,
    SWITCH = 259,
    CASE = 260,
    DEFAULT = 261,
    CONTINUE = 262,
    BREAK = 263,
    DECOP = 264,
    INCOP = 265,
    BITOP = 266,
    NOT = 267,
    LTHIRD = 268,
    RTHIRD = 269,
    COMMA = 270,
    STRING = 271,
    PRINTLN = 272,
    NEWLINE = 273,
    RETURN = 274,
    ID = 275,
    INT = 276,
    FLOAT = 277,
    DOUBLE = 278,
    VOID = 279,
    CONST_CHAR = 280,
    CONST_FLOAT = 281,
    CONST_INT = 282,
    ADDOP = 283,
    MULOP = 284,
    RELOP = 285,
    LOGICOP = 286,
    ASSIGNOP = 287,
    SEMICOLON = 288,
    LCURL = 289,
    RCURL = 290,
    LPAREN = 291,
    RPAREN = 292,
    IF = 293,
    FOR = 294,
    WHILE = 295,
    LOWER_THEN_ELSE = 296,
    ELSE = 297
  };
#endif
/* Tokens.  */
#define DO 258
#define SWITCH 259
#define CASE 260
#define DEFAULT 261
#define CONTINUE 262
#define BREAK 263
#define DECOP 264
#define INCOP 265
#define BITOP 266
#define NOT 267
#define LTHIRD 268
#define RTHIRD 269
#define COMMA 270
#define STRING 271
#define PRINTLN 272
#define NEWLINE 273
#define RETURN 274
#define ID 275
#define INT 276
#define FLOAT 277
#define DOUBLE 278
#define VOID 279
#define CONST_CHAR 280
#define CONST_FLOAT 281
#define CONST_INT 282
#define ADDOP 283
#define MULOP 284
#define RELOP 285
#define LOGICOP 286
#define ASSIGNOP 287
#define SEMICOLON 288
#define LCURL 289
#define RCURL 290
#define LPAREN 291
#define RPAREN 292
#define IF 293
#define FOR 294
#define WHILE 295
#define LOWER_THEN_ELSE 296
#define ELSE 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 163 "lex.y" /* yacc.c:1909  */

	SymbolInfo *symbol;
	char *str;
	int ival;
	float *dval;

#line 145 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
