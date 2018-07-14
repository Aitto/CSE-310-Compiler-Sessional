/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "lex.y" /* yacc.c:339  */

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "symbolMain.cpp"
#include "vars.h"
#include<vector>
#include<utility>


//#define YYDEBUG 1

using namespace std;

void initParNum();

int yyparse(void);
int yylex(void);
FILE *gCode=NULL;

string typeSp;
string vType;
string rType="none";
string par[10];
string parType[10];
string argType[10];


char * undecvar= "\nError at line: %d. Undeclared variable %s\n";
char * muldec= "\nError at line: %d. Multipe declaration of %s\n";
char * nonIn= "\nError at line: %d. Not-Integer Array Index used\n";
char * nonArr="\nError at line: %d. %s not an Array\n";
char * arrIn="\nError at line: %d. Trying to access array like normal variable!\n";
char * typemm= "\nError at line: %d. Type mismatched\n";
char * undecfunc="\nError at line: %d. Undeclared function %s\n";
char * moderror="\nError at ine: %d. Both operands on modulus should be Integer\n";
char * voidcall="\nError at line: %d. Can't call Void function for assignment or expression\n";

bool c;

int parNum=0;
int argNum=0;
int tperror=0;

SymbolInfo * symbolInfo;

extern char* yytext;
extern int yylineno;
extern FILE *yyin;
extern FILE *logOut,*tokenOut;
extern int terror;

void yyerror(char *s,string t)
{
	fprintf(parseError,s,yylineno,t.c_str());
	//else fprintf(parseError,s,yylineno);

	tperror++;
}

void yyerror(const char *s){
	fprintf(parseError,s,yylineno);
	tperror++;
}

void addToTable(){
	for(int i=0;i<parNum;i++){
		if(par[i]!=" "){
		manage('I',par[i],"ID");
		symbolInfo=getSymbol(par[i]);
		symbolInfo->var_type=parType[i];
		}
	}
}

void addToSymbol(SymbolInfo *s){
	if(s!=0) s->parSet(parType,parNum);
}

bool matchPL(string s1[], string s2[],int num){
	bool ans=true;
	for(int i=0;i<num;i++){
		if(s1[i]!=s2[i]){
			ans=false;
			break;
		}
	}
	return ans;
}

void initVtype(){
	vType="none";
}

void initRtype(){
	rType="none";
}

void initSymbol(){
	symbolInfo=0;
}

void initParNum(){
	parNum=0;
}

/**
	Variables for Intermediate code generation.
	string code contains corresponding code segment
	and string data contains corresponding code for data segment
	addToCode() --> Adds code to the code segment
	addTo
*/
string init=".model small\n.stack 100h\n";
string inStack="\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";
string outStack="\tpop ax\n\tpop bx\n\tpop cx\n\tpop dx\n";
string codeSegment=".code\n";
string dataSegment=".data\n";
vector<string> variables;
vector<pair<string,int>> avariables;
bool global=true;
string fname=" ";
int labelCount=0;
int tempCount=0;

void addCode(string s){
	codeSegment+=s;
}

void addData(string s){
	dataSegment+=s;
}

void addVars(string name,int num,bool array=false){
	if(array){
		if(!global) avariables.push_back(make_pair(fname+ name,num));
		else avariables.push_back(make_pair(name,num));
	}
	else for(int i=0;i<num;i++){
		if(!global) variables.push_back(name + par[i]);
		else variables.push_back(par[i]);
	}
}


char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	variables.push_back(string(t));
	return t;
}



#line 238 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 173 "lex.y" /* yacc.c:355  */

	SymbolInfo *symbol;
	char *str;
	int ival;
	float *dval;

#line 369 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 386 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,   198,   198,   217,   226,   236,   241,   246,   253,   272,
     291,   291,   359,   359,   415,   422,   429,   435,   444,   444,
     451,   451,   459,   459,   472,   477,   482,   489,   505,   520,
     535,   552,   558,   567,   572,   577,   582,   599,   612,   629,
     644,   654,   664,   668,   676,   692,   716,   722,   741,   746,
     766,   771,   804,   809,   833,   838,   871,   884,   897,   904,
     921,   941,   947,   956,   965,   973,   983,   988,   991,   998
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DO", "SWITCH", "CASE", "DEFAULT",
  "CONTINUE", "BREAK", "DECOP", "INCOP", "BITOP", "NOT", "LTHIRD",
  "RTHIRD", "COMMA", "STRING", "PRINTLN", "NEWLINE", "RETURN", "ID", "INT",
  "FLOAT", "DOUBLE", "VOID", "CONST_CHAR", "CONST_FLOAT", "CONST_INT",
  "ADDOP", "MULOP", "RELOP", "LOGICOP", "ASSIGNOP", "SEMICOLON", "LCURL",
  "RCURL", "LPAREN", "RPAREN", "IF", "FOR", "WHILE", "LOWER_THEN_ELSE",
  "ELSE", "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "parameter_list", "compound_statement",
  "$@3", "$@4", "var_declaration", "$@5", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF -72

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-72)))

#define YYTABLE_NINF -21

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      28,   -72,   -72,   -72,    16,    28,   -72,   -72,   -72,   -72,
       4,   -72,   -72,    -5,    27,    34,    32,    39,    29,    52,
      38,     7,    56,    65,   -72,   -72,   -72,    48,    28,    50,
     -72,    57,    59,   -72,    76,   -72,    48,    71,    78,    66,
     -72,   -72,   -72,    -1,    67,    -1,     1,   -72,   -72,    -1,
     -72,    -1,    72,    73,    74,   -72,   -72,    93,    53,   -72,
     -72,     8,    86,   -72,    89,    30,    96,   -72,   -72,   -72,
       3,   -72,   104,    94,    -1,    -1,   -72,    92,    -1,    95,
      -1,   113,   -72,   -72,   -72,   -72,    -1,   -72,    -1,    -1,
      -1,    -1,    97,   -72,   116,   -72,    98,   117,   -72,    99,
      95,   100,   -72,   -72,    96,   105,   -72,   106,   -72,   -72,
      -1,    78,    -1,    78,   -72,   -72,   101,   103,   -72,    78,
      78,   -72,   -72
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    24,    25,    26,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    29,    22,     0,     0,     0,     0,     0,
      12,     0,    17,    27,    23,    30,     9,     0,     0,    10,
      16,     0,    18,    13,    15,     8,     0,     0,     0,     0,
      14,    11,    28,     0,     0,     0,    44,    63,    62,     0,
      42,     0,     0,     0,     0,    35,    33,     0,     0,    31,
      34,    59,     0,    46,    48,    50,    52,    54,    58,    21,
      59,    57,     0,     0,     0,    67,    56,     0,     0,     0,
       0,    29,    19,    32,    65,    64,     0,    43,     0,     0,
       0,     0,     0,    41,     0,    69,     0,    66,    61,     0,
       0,     0,    47,    49,    53,    51,    55,     0,    45,    60,
       0,     0,     0,     0,    40,    68,    37,     0,    39,     0,
       0,    38,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   133,   -72,   -72,   -72,   -72,   -72,     2,
     -72,   -72,    23,   -72,     5,   -72,   -72,   -56,   -59,   -43,
     -44,   -71,    54,    51,    55,   -40,   -72,   -72,   -72
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    36,    27,    21,    55,
      38,    39,    56,    18,    57,    14,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    96,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      70,    73,    83,    71,    95,    10,    70,    77,    15,    76,
      10,    43,    84,    85,    74,   102,    11,    84,    85,    46,
     100,    22,    28,     9,    13,    47,    48,    49,     9,    33,
      94,    16,    70,    34,    99,    51,   101,    75,    41,   115,
      86,   112,    17,    70,    29,    70,    70,    70,    70,     1,
       2,   106,     3,     1,     2,   116,     3,   118,    89,    23,
      90,    19,    24,   121,   122,    43,    25,    70,   117,    20,
      44,    26,    45,    46,     1,     2,    30,     3,    31,    47,
      48,    49,    32,    35,    37,    42,    50,    32,    82,    51,
      43,    52,    53,    54,   -20,    44,    40,    45,    46,     1,
       2,    69,     3,    72,    47,    48,    49,    43,    78,    79,
      80,    50,    32,    81,    51,    46,    52,    53,    54,    87,
      88,    47,    48,    49,    92,    91,    15,    93,    50,    98,
     108,    51,   110,    89,   107,   109,   111,   113,    12,   114,
     120,   105,   103,   119,   104
};

static const yytype_uint8 yycheck[] =
{
      43,    45,    58,    43,    75,     0,    49,    51,    13,    49,
       5,    12,     9,    10,    13,    86,     0,     9,    10,    20,
      79,    16,    15,     0,    20,    26,    27,    28,     5,    27,
      74,    36,    75,    28,    78,    36,    80,    36,    36,   110,
      32,   100,    15,    86,    37,    88,    89,    90,    91,    21,
      22,    91,    24,    21,    22,   111,    24,   113,    28,    20,
      30,    27,    33,   119,   120,    12,    14,   110,   112,    37,
      17,    33,    19,    20,    21,    22,    20,    24,    13,    26,
      27,    28,    34,    33,    27,    14,    33,    34,    35,    36,
      12,    38,    39,    40,    35,    17,    20,    19,    20,    21,
      22,    35,    24,    36,    26,    27,    28,    12,    36,    36,
      36,    33,    34,    20,    36,    20,    38,    39,    40,    33,
      31,    26,    27,    28,    20,    29,    13,    33,    33,    37,
      14,    36,    15,    28,    37,    37,    37,    37,     5,    33,
      37,    90,    88,    42,    89
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    22,    24,    44,    45,    46,    47,    48,    55,
      57,     0,    46,    20,    58,    13,    36,    15,    56,    27,
      37,    51,    57,    20,    33,    14,    33,    50,    15,    37,
      20,    13,    34,    52,    57,    33,    49,    27,    53,    54,
      20,    52,    14,    12,    17,    19,    20,    26,    27,    28,
      33,    36,    38,    39,    40,    52,    55,    57,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    35,
      62,    68,    36,    63,    13,    36,    68,    63,    36,    36,
      36,    20,    35,    60,     9,    10,    32,    33,    31,    28,
      30,    29,    20,    33,    63,    64,    70,    71,    37,    63,
      61,    63,    64,    65,    67,    66,    68,    37,    14,    37,
      15,    37,    61,    37,    33,    64,    60,    63,    60,    42,
      37,    60,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    47,    47,
      49,    48,    50,    48,    51,    51,    51,    51,    53,    52,
      54,    52,    56,    55,    57,    57,    57,    58,    58,    58,
      58,    59,    59,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    67,    67,    68,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     0,     4,     1,     1,     1,     3,     6,     1,
       4,     1,     2,     1,     1,     1,     7,     5,     7,     5,
       5,     3,     1,     2,     1,     4,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     2,     2,     1,     1,
       4,     3,     1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 199 "lex.y" /* yacc.c:1646  */
    {
		//write your code in this block in all the similar blocks below
		manage('P',"...");
		//Initialize assembly
		//if(tperror==0 || tperror!=0){
			fprintf(gCode,(init+"\n.data\n").c_str());
			for(vector<string>::iterator it=variables.begin();it!=variables.end();it++){
				fprintf(gCode,("\t"+*it + " dw ?\n").c_str() );
			}
			for(int i=0;i<avariables.size();i++){
				fprintf(gCode,("\t"+avariables[i].first+ " dw %d dup (?)\n").c_str(),avariables[i].second );
			}
			fprintf(gCode,(printInit+".code\n"+pDec+ (yyvsp[0].symbol)->code+"\nend main").c_str());
			
		//}
	}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 217 "lex.y" /* yacc.c:1646  */
    {
		(yyval.symbol)=(yyvsp[-1].symbol);
		(yyval.symbol)->code=(yyvsp[-1].symbol)->code+(yyvsp[0].symbol)->code;

		fprintf(parseLog, "\nAt line no : %d program : program unit\n\n",yylineno );
		(yyval.symbol)->setName((yyvsp[-1].symbol)->getName()+"\n"+(yyvsp[0].symbol)->getName());
		fprintf(parseLog,"\n%s\n",(yyvsp[-1].symbol)->getName().c_str());
		global=true;
		}
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 226 "lex.y" /* yacc.c:1646  */
    {

		(yyval.symbol)=(yyvsp[0].symbol);

		fprintf(parseLog, "\nAt line no : %d program : unit\n\n",yylineno );
		fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
		global=true;
		}
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 236 "lex.y" /* yacc.c:1646  */
    {
			(yyval.symbol)=(yyvsp[0].symbol);
			fprintf(parseLog, "\nAt line no : %d unit : var_declaration\n\n",yylineno );
			fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
			}
#line 1608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 241 "lex.y" /* yacc.c:1646  */
    {
		 	(yyval.symbol)=(yyvsp[0].symbol);
		 	fprintf(parseLog, "\nAt line no : %d unit : func_declaration\n\n",yylineno );
			 fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
			 }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 246 "lex.y" /* yacc.c:1646  */
    {
		 	(yyval.symbol)=(yyvsp[0].symbol);
		 	fprintf(parseLog, "\nAt line no : %d unit : func_definition\n\n",yylineno );
			 fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
			 }
#line 1628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 253 "lex.y" /* yacc.c:1646  */
    {

				c=manage('I',(yyvsp[-4].symbol)->getName(),"foo"); symbolInfo=getSymbol((yyvsp[-4].symbol)->getName()); if(symbolInfo!=0){
					if(symbolInfo->func_declared || symbolInfo->func_defined){
						yyerror("\nWarning. At line : %d. %s Declared multiple times\n",(yyvsp[-4].symbol)->getName());
					}else{
						symbolInfo->func_declared=true;
						symbolInfo->ret_type=(yyvsp[-5].symbol)->getName();
						symbolInfo->parNum=parNum;
						addToSymbol(symbolInfo);
						
					}

				} initParNum();
				
				fprintf(parseLog, "\nAt line no : %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[-5].symbol)->getName()+" "+(yyvsp[-4].symbol)->getName()+"("+(yyvsp[-2].symbol)->getName()+");" );
				fprintf(parseLog,"%s\n",(yyvsp[-5].symbol)->getName().c_str());
				}
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 272 "lex.y" /* yacc.c:1646  */
    {
				c=manage('I',(yyvsp[-3].symbol)->getName(),"foo"); symbolInfo=getSymbol((yyvsp[-3].symbol)->getName()); if(symbolInfo!=0){
					

					if(symbolInfo->func_declared || symbolInfo->func_defined){
						yyerror("\nWarning. At line : %d. %s Declared multiple times\n",(yyvsp[-3].symbol)->getName());
					}else{
						symbolInfo->func_declared=true;
						symbolInfo->ret_type=(yyvsp[-4].symbol)->getName();
						symbolInfo->parNum=0;
					}

				} initParNum();
				fprintf(parseLog, "\nAt line no : %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[-4].symbol)->getName()+" "+(yyvsp[-3].symbol)->getName() + "();");
				fprintf(parseLog,"%s\n",(yyvsp[-4].symbol)->getName().c_str());
				}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 291 "lex.y" /* yacc.c:1646  */
    {
				
				global=false;
				fname=(yyvsp[-3].symbol)->getName();
				
				c=manage('I',(yyvsp[-3].symbol)->getName(),"foo"); if(!c){

					addVars((yyvsp[-3].symbol)->getName(),parNum);

					symbolInfo=getSymbol((yyvsp[-3].symbol)->getName()); if(symbolInfo!=0){
						if(symbolInfo->func_defined){
							yyerror(muldec,(yyvsp[-3].symbol)->getName());
						}else {
							symbolInfo->func_defined=true;
							if(symbolInfo->func_declared){
								if(parNum!=symbolInfo->parNum){
									yyerror("\nError at line : %d. Parameter Number of %s doesn't match\n",(yyvsp[-3].symbol)->getName());
								}else if(!matchPL(symbolInfo->parTList,parType,parNum)){
									yyerror("Error at line : %d. Parameter types doesn't match!\n");
								}
								
							}else {

								//actually they'll never come in this stage
								
								symbolInfo->ret_type=(yyvsp[-4].symbol)->getName();
								symbolInfo->parNum=parNum;
								addToSymbol(symbolInfo);
								
							}
						}
					}
				}else{
					symbolInfo=getSymbol((yyvsp[-3].symbol)->getName()); if(symbolInfo!=0){
					
					symbolInfo->ret_type=(yyvsp[-4].symbol)->getName();
					symbolInfo->parNum=parNum;
					
					addVars((yyvsp[-3].symbol)->getName(),parNum);

					addToSymbol(symbolInfo);
					symbolInfo->func_defined=true;
					}
				} 
				}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 335 "lex.y" /* yacc.c:1646  */
    {
				
				
				if((yyvsp[-5].symbol)->getName()=="main"){
					(yyval.symbol)->code=(yyvsp[-5].symbol)->getName() + " proc\n";
					(yyval.symbol)->code+="\tmov ax,@data\n\tmov ds,ax\n";
					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
					(yyval.symbol)->code+="\tmov ah,4ch\n\tint 21h\nmain endp\n" ;
				}else{
					(yyval.symbol)->code=(yyvsp[-5].symbol)->getName() + " proc\n" +inStack;
					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
					(yyval.symbol)->code+=outStack + "ret\n" + (yyvsp[-5].symbol)->getName()+ " endp\n" ;
				}

				if((yyvsp[-6].symbol)->getName()!=rType){
						yyerror("\nError at line : %d. Return type doesn't match\n");
						//cout<<$1->getName()<< " "<<rType<<endl;
						rType="none";
				}

				fprintf(parseLog, "\nAt line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[-6].symbol)->getName()+" "+(yyvsp[-5].symbol)->getName()+"("+(yyvsp[-3].symbol)->getName()+")"+(yyvsp[0].symbol)->getName() );
				fprintf(parseLog,"%s\n",(yyvsp[-6].symbol)->getName().c_str());
				}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 359 "lex.y" /* yacc.c:1646  */
    {
				
				global=false;
				fname=(yyvsp[-2].symbol)->getName();

				c=manage('I',(yyvsp[-2].symbol)->getName(),"foo"); if(!c){
					symbolInfo=getSymbol((yyvsp[-2].symbol)->getName()); if(symbolInfo!=0){
						if(symbolInfo->func_defined){
							yyerror(muldec,(yyvsp[-2].symbol)->getName());
						}else {
							symbolInfo->func_defined=true;
							if(symbolInfo->func_declared){
								if(parNum!=symbolInfo->parNum){
									yyerror("\nError at line : %d. Parameter Number of %s doesn't match\n",(yyvsp[-2].symbol)->getName());
									cout<<parNum<< " "<<symbolInfo->parNum<<endl;
								}
								
							}else {
								
								symbolInfo->ret_type=(yyvsp[-3].symbol)->getName();
								symbolInfo->parNum=0;
							}
						}
					}
				}else{
					symbolInfo=getSymbol((yyvsp[-2].symbol)->getName()); if(symbolInfo!=0){
					
					symbolInfo->ret_type=(yyvsp[-3].symbol)->getName();
					symbolInfo->func_defined=true;
					symbolInfo->parNum=0;
					}
				}
				}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 391 "lex.y" /* yacc.c:1646  */
    {
				
				
				if((yyvsp[-4].symbol)->getName()=="main"){
					(yyval.symbol)->code=(yyvsp[-4].symbol)->getName() + " proc\n";
					(yyval.symbol)->code+="\tmov ax,@data\n\tmov ds,ax\n";
					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
					(yyval.symbol)->code+="\tmov ah,4ch\n\tint 21h\nmain endp\n" ;
				}else{
					(yyval.symbol)->code=(yyvsp[-4].symbol)->getName() + " proc\n" +inStack;
					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
					(yyval.symbol)->code+=outStack + "ret\n" + (yyvsp[-4].symbol)->getName()+ " endp\n" ;
				}

				if((yyvsp[-5].symbol)->getName()!=rType){
						yyerror("\nError at line : %d. Return type doesn't match\n");
						rType="none";
				}
				fprintf(parseLog, "\nAt line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[-5].symbol)->getName()+ " "+ (yyvsp[-4].symbol)->getName()+ "( )"+(yyvsp[0].symbol)->getName());
				fprintf(parseLog,"%s\n",(yyvsp[-5].symbol)->getName().c_str());
				}
#line 1818 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 415 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[-3].symbol);
				par[parNum]=(yyvsp[0].symbol)->getName(); parType[parNum]=(yyvsp[-1].symbol)->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : parameter_list COMMA type_specifier ID\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[-3].symbol)->getName()+","+(yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName());
				fprintf(parseLog,"%s\n",(yyvsp[-3].symbol)->getName().c_str()); 
				}
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 422 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[-2].symbol);
				par[parNum]=" "; parType[parNum]=(yyvsp[0].symbol)->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : parameter_list COMMA type_specifier\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+","+(yyvsp[0].symbol)->getName());
				fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str());
				}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 429 "lex.y" /* yacc.c:1646  */
    {
			 	par[parNum]=(yyvsp[0].symbol)->getName(); parType[parNum]=(yyvsp[-1].symbol)->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : type_specifier ID\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[-1].symbol)->getName()+" "+(yyvsp[0].symbol)->getName());
				fprintf(parseLog,"%s\n",(yyvsp[-1].symbol)->getName().c_str());
				}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 435 "lex.y" /* yacc.c:1646  */
    {
				par[parNum]=" "; parType[parNum]=(yyvsp[0].symbol)->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : type_specifier\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[0].symbol)->getName());
				fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
				}
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 444 "lex.y" /* yacc.c:1646  */
    {manage('S',"..."); addToTable(); initParNum(); }
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 444 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[-1].symbol);
					fprintf(parseLog, "\nAt line no : %d compound_statement : LCURL statements RCURL\n\n",yylineno );
					(yyval.symbol)->setName("{\n"+(yyvsp[-1].symbol)->getName()+"}\n");
					fprintf(parseLog,"%s\n",(yyval.symbol)->getName().c_str());
					manage('E',"...");
					}
#line 1882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 451 "lex.y" /* yacc.c:1646  */
    {manage('S',"..."); addToTable(); initParNum(); }
#line 1888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 451 "lex.y" /* yacc.c:1646  */
    { 
			 		fprintf(parseLog, "\nAt line no : %d compound_statement : LCURL RCURL\n\n",yylineno );
					(yyval.symbol)->setName("{\n}\n");
					fprintf(parseLog,"{\n}\n");
					manage('E',"...");
					}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 459 "lex.y" /* yacc.c:1646  */
    {
						addVars(fname,parNum);
					}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 461 "lex.y" /* yacc.c:1646  */
    {
					initParNum();

					if(vType=="void") yyerror("\nError at line  %d. Variable type Cannot be Void\n"),initVtype;

					fprintf(parseLog, "\nAt line no : %d var_declaration : type_specifier declaration_list SEMICOLON\n\n",yylineno );
					(yyval.symbol)->setName((yyvsp[-3].symbol)->getName()+ " "+(yyvsp[-2].symbol)->getName() + ";");
					fprintf(parseLog,"%s\n",(yyvsp[-3].symbol)->getName().c_str());
					}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 472 "lex.y" /* yacc.c:1646  */
    {
					vType="int"; rType="int";
					fprintf(parseLog, "\nAt line no : %d type_specifier : INT\n\n",yylineno );
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 477 "lex.y" /* yacc.c:1646  */
    {
					vType="float"; rType="float";
					fprintf(parseLog, "\nAt line no : %d type_specifier : FLOAT\n\n",yylineno );
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 482 "lex.y" /* yacc.c:1646  */
    {
					vType="void"; rType="void";
					fprintf(parseLog, "\nAt line no : %d type_specifier : VOID\n\n",yylineno );
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
					}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 489 "lex.y" /* yacc.c:1646  */
    {
						c=manage('I',(yyvsp[0].symbol)->getName(),"ID"); if(!c) yyerror(muldec,(yyvsp[0].symbol)->getName()); else{
						symbolInfo=getSymbol((yyvsp[0].symbol)->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->arr=false;
							if(!global) symbolInfo->temp_var=fname+(yyvsp[0].symbol)->getName();
							else symbolInfo->temp_var=(yyvsp[0].symbol)->getName();
							par[parNum]=(yyvsp[0].symbol)->getName();
							parNum++;
						}}
						
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : declaration_list COMMA ID\n\n",yylineno );
						(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+ "," + (yyvsp[0].symbol)->getName());
						fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str()); 
						}
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 505 "lex.y" /* yacc.c:1646  */
    {
			   			c=manage('I',(yyvsp[-3].symbol)->getName() ,"ID"); if(!c) yyerror(muldec, (yyvsp[-3].symbol)->getName()); else {
						symbolInfo=getSymbol((yyvsp[-3].symbol)->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->ret_type="array";
							symbolInfo->arr=true;
							if(!global) symbolInfo->temp_var=fname+(yyvsp[-3].symbol)->getName();
							else symbolInfo->temp_var=(yyvsp[-3].symbol)->getName();
							addVars((yyvsp[-3].symbol)->getName(),(yyvsp[-1].symbol)->ival,true);
						}}
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n",yylineno );
						(yyval.symbol)->setName((yyvsp[-5].symbol)->getName()+"," + (yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]");
						fprintf(parseLog,"%s\n",(yyvsp[-5].symbol)->getName().c_str());
						}
#line 1992 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 520 "lex.y" /* yacc.c:1646  */
    {
			   			c=manage('I',(yyvsp[0].symbol)->getName(),"ID"); if(!c) yyerror(muldec,(yyvsp[0].symbol)->getName()); else {
						symbolInfo=getSymbol((yyvsp[0].symbol)->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->arr=false;
							if(!global) symbolInfo->temp_var=fname+(yyvsp[0].symbol)->getName();
							else symbolInfo->temp_var=(yyvsp[0].symbol)->getName();
							par[parNum]=(yyvsp[0].symbol)->getName();
							parNum++;
						}}
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : ID\n\n",yylineno );
						(yyval.symbol)->setName((yyvsp[0].symbol)->getName());
						fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
						}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 535 "lex.y" /* yacc.c:1646  */
    {
			   			c=manage('I',(yyvsp[-3].symbol)->getName(),"ID"); if(!c) yyerror(muldec,(yyvsp[-3].symbol)->getName()); else {
						symbolInfo=getSymbol((yyvsp[-3].symbol)->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->ret_type="array";
							symbolInfo->arr=false;
							if(!global) symbolInfo->temp_var=fname+(yyvsp[-3].symbol)->getName();
							else symbolInfo->temp_var=(yyvsp[-3].symbol)->getName();
							addVars((yyvsp[-3].symbol)->getName(),(yyvsp[-1].symbol)->ival,true);
						}}
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n",yylineno );
						(yyval.symbol)->setName((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]");
						fprintf(parseLog,"%s\n",(yyvsp[-3].symbol)->getName().c_str());
						}
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 552 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[0].symbol);
					fprintf(parseLog, "\nAt line no : %d statements : statement\n\n",yylineno );
					(yyval.symbol)->setName((yyvsp[0].symbol)->getName());
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
					}
#line 2043 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 558 "lex.y" /* yacc.c:1646  */
    {
		   			(yyval.symbol)=(yyvsp[-1].symbol);
					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
		   			fprintf(parseLog, "\nAt line no : %d statements : statements statement\n\n",yylineno );
					(yyval.symbol)->setName((yyvsp[-1].symbol)->getName()+"\n"+(yyvsp[0].symbol)->getName());
					fprintf(parseLog,"%s\n",(yyvsp[-1].symbol)->getName().c_str());
					}
#line 2055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 567 "lex.y" /* yacc.c:1646  */
    {
						(yyval.symbol)=(yyvsp[0].symbol);
						fprintf(parseLog, "\nAt line no : %d statement : var_declaration\n\n",yylineno );
						fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
						}
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 572 "lex.y" /* yacc.c:1646  */
    {
		  				(yyval.symbol)=(yyvsp[0].symbol);
		  				fprintf(parseLog, "\nAt line no : %d statement : expression_statement\n\n",yylineno );
						fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
						}
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 577 "lex.y" /* yacc.c:1646  */
    {
		  				(yyval.symbol)=(yyvsp[0].symbol);
		  				fprintf(parseLog, "\nAt line no : %d statement : compound_statement\n\n",yylineno );
						fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
						}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 582 "lex.y" /* yacc.c:1646  */
    {
		  				
						(yyval.symbol)=(yyvsp[-4].symbol);
                        string loop=newLabel();
                        string skip=newLabel();
                        (yyval.symbol)->code+=loop+":\n";
                        (yyval.symbol)->code+=(yyvsp[-3].symbol)->code;
                        (yyval.symbol)->code+="\tcmp "+(yyvsp[-3].symbol)->temp_var+",0\n";
                        (yyval.symbol)->code+="\tje "+skip+"\n";
                        (yyval.symbol)->code+=(yyvsp[0].symbol)->code+(yyvsp[-2].symbol)->code;
                        (yyval.symbol)->code+="\tjmp "+loop+"\n";
                        (yyval.symbol)->code+=skip+":\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n",yylineno );
						(yyval.symbol)->setName("for("+(yyvsp[-4].symbol)->getName()+(yyvsp[-3].symbol)->getName()+(yyvsp[-2].symbol)->getName()+")"+(yyvsp[0].symbol)->getName());
						fprintf(parseLog,"%s\n",(yyvsp[-6].symbol)->getName().c_str());
						}
#line 2107 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 599 "lex.y" /* yacc.c:1646  */
    {

						(yyval.symbol)=(yyvsp[-2].symbol);
						(yyval.symbol)->code+="\n\tcmp "+(yyvsp[-2].symbol)->temp_var+",0\n";
						string skip=string(newLabel());
						(yyval.symbol)->code+="\tje "+skip+"\n";
						(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
						(yyval.symbol)->code+=skip+":\n\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE\n\n",yylineno );
						(yyval.symbol)->setName("if("+(yyvsp[-2].symbol)->getName()+")"+(yyvsp[0].symbol)->getName());
						fprintf(parseLog,"%s\n",(yyvsp[-4].symbol)->getName().c_str());
						}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 612 "lex.y" /* yacc.c:1646  */
    {
		  				
						(yyval.symbol)=(yyvsp[-4].symbol);
						(yyval.symbol)->code+="\n\tcmp "+(yyvsp[-4].symbol)->temp_var+",0\n";
						string skip=string(newLabel());
						string else_code=string(newLabel());
						(yyval.symbol)->code+="\tje "+else_code+"\n";
						(yyval.symbol)->code+=(yyvsp[-2].symbol)->code;
						(yyval.symbol)->code+="\tjmp "+skip+"\n";
						(yyval.symbol)->code+=else_code+":\n\n";
						(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
						(yyval.symbol)->code+=skip+":\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n",yylineno );
						(yyval.symbol)->setName("if("+(yyvsp[-4].symbol)->getName()+")"+(yyvsp[-2].symbol)->getName()+" else "+(yyvsp[0].symbol)->getName());
						fprintf(parseLog,"%s\n",(yyvsp[-6].symbol)->getName().c_str());
						}
#line 2147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 629 "lex.y" /* yacc.c:1646  */
    {

						(yyval.symbol)=(yyvsp[-2].symbol);
						string loop=newLabel();
						string skip=newLabel();
						(yyval.symbol)->code="\n"+loop+":\n";
						(yyval.symbol)->code+="\tcmp "+(yyvsp[-2].symbol)->temp_var+",0\n";
						(yyval.symbol)->code+="je "+skip+"\n";
						(yyval.symbol)->code+=(yyvsp[0].symbol)->code+"\n\tjmp "+loop+"\n" ;
						(yyval.symbol)->code+=skip+":\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : WHILE LPAREN expression RPAREN statement\n\n",yylineno );
						(yyval.symbol)->setName("while("+(yyvsp[-2].symbol)->getName()+")"+(yyvsp[0].symbol)->getName());
						fprintf(parseLog,"%s\n",(yyvsp[-4].symbol)->getName().c_str());
						}
#line 2167 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 644 "lex.y" /* yacc.c:1646  */
    {
		  				symbolInfo=getSymbol((yyvsp[-2].symbol)->getName());
						(yyval.symbol)->code="\tmov ax,"+symbolInfo->temp_var+"\n";
						cout<< "I thiknk jhamela is here : "<<(yyvsp[-2].symbol)->temp_var+"\n";
						(yyval.symbol)->code+="\tmov printVar,ax\n";
						(yyval.symbol)->code+="\tcall SHOW\n";
						
		  				fprintf(parseLog, "\nAt line no : %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n",yylineno );
						
						}
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 654 "lex.y" /* yacc.c:1646  */
    {
		  				(yyval.symbol)=(yyvsp[-1].symbol);
		  				rType=(yyvsp[-1].symbol)->var_type;
						
						fprintf(parseLog, "\nAt line no : %d statement : RETURN expression SEMICOLON\n\n",yylineno );
						(yyval.symbol)->setName("return " +(yyvsp[-1].symbol)->getName()+";"); 
						fprintf(parseLog,"return %s ;\n",(yyvsp[-1].symbol)->getName().c_str());
						}
#line 2195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 664 "lex.y" /* yacc.c:1646  */
    {
					fprintf(parseLog, "\nAt line no : %d expression_statement : SEMICOLON\n\n",yylineno );
					(yyval.symbol)->setName(";\n"); fprintf(parseLog,";\n"); 
					}
#line 2204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 668 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[-1].symbol);
					fprintf(parseLog, "\nAt line no : %d expression_statement : expression SEMICOLON\n\n",yylineno ); 
					(yyval.symbol)->setName((yyvsp[-1].symbol)->getName()+";"); 
					fprintf(parseLog,"%s\n",(yyvsp[-1].symbol)->getName().c_str()); 
					}
#line 2215 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 676 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[0].symbol);
				symbolInfo=getSymbol((yyvsp[0].symbol)->getName());
				(yyval.symbol)->temp_var=symbolInfo->temp_var;
                (yyval.symbol)->arr=false;
				
				c=manage('L',(yyvsp[0].symbol)->getName()); if(!c) yyerror(undecvar,(yyvsp[0].symbol)->getName()); 
				
				if(symbolInfo!=0) {
					if(symbolInfo->ret_type=="array") yyerror(arrIn,(yyvsp[0].symbol)->getName());
					(yyval.symbol)->var_type=symbolInfo->var_type;
				}
				fprintf(parseLog, "\nAt line no : %d variable : ID\n\n",yylineno );
				(yyval.symbol)->setName((yyvsp[0].symbol)->getName());
				fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
				}
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 692 "lex.y" /* yacc.c:1646  */
    {
		 		symbolInfo=getSymbol((yyvsp[-3].symbol)->getName());
		 		(yyval.symbol)=(yyvsp[-3].symbol);
				(yyval.symbol)->code+=(yyvsp[-1].symbol)->code;
				(yyval.symbol)->code+="\tmov bx,"+(yyvsp[-1].symbol)->temp_var+"\n";
            	(yyval.symbol)->code+="\tshl bx,1\n";
	            (yyval.symbol)->temp_var=symbolInfo->temp_var+"[bx]";
		 		(yyval.symbol)->arr=true;
				c=manage('L',(yyvsp[-3].symbol)->getName()); if(!c) yyerror(undecvar,(yyvsp[-3].symbol)->getName()); 

		 		if((yyvsp[-1].symbol)->var_type=="void") yyerror(voidcall);
		 		else if((yyvsp[-1].symbol)->var_type!="int") yyerror(nonIn);
				
				if(symbolInfo!=0) {
					if(symbolInfo->ret_type!="array") yyerror(nonArr,(yyvsp[-3].symbol)->getName());
					(yyval.symbol)->var_type=symbolInfo->var_type;
				}
				c=manage('L',(yyvsp[-3].symbol)->getName()); if(!c) yyerror(undecvar,(yyvsp[-3].symbol)->getName());
				fprintf(parseLog, "\nAt line no : %d variable : ID LTHIRD expression RTHIRD\n\n",yylineno ); 
				(yyval.symbol)->setName((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]"); 
				fprintf(parseLog,"%s\n",(yyvsp[-3].symbol)->getName().c_str()); 
				}
#line 2263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 716 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[0].symbol);

					fprintf(parseLog, "\nAt line no : %d expression : logic_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 2274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 722 "lex.y" /* yacc.c:1646  */
    {
		   			(yyval.symbol)=(yyvsp[-2].symbol);

					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
                    (yyval.symbol)->code+="\tmov ax,"+(yyvsp[0].symbol)->temp_var+"\n";
                    (yyval.symbol)->code+="\tmov "+(yyvsp[-2].symbol)->temp_var+",ax\n";
                    (yyval.symbol)->temp_var=newTemp();
                    (yyval.symbol)->code+="\tmov "+(yyval.symbol)->temp_var+",ax\n";

					if((yyvsp[0].symbol)->var_type=="void") yyerror(voidcall);
					else if((yyvsp[-2].symbol)->var_type!=(yyvsp[0].symbol)->var_type) yyerror(typemm);
					//cout<<$1->getName()<<" "<< $1->var_type<< " "<<$3->var_type<<endl;
					
		   			fprintf(parseLog, "\nAt line no : %d expression : variable ASSIGNOP logic_expression\n\n",yylineno ); 
					(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+"="+(yyvsp[0].symbol)->getName()); 
					fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str()); 
					}
#line 2296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 741 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[0].symbol);
					fprintf(parseLog, "\nAt line no : %d logic_expression : rel_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 746 "lex.y" /* yacc.c:1646  */
    {
			 		(yyval.symbol)=(yyvsp[-2].symbol);
					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
					char *temp=newTemp();
					(yyval.symbol)->code+="\tmov ax,"+(yyvsp[-2].symbol)->temp_var+"\n";
					(yyval.symbol)->temp_var=string(temp);
					if((yyvsp[-1].symbol)->getName()=="&&"){
						(yyval.symbol)->code+="\tand ax,"+(yyvsp[0].symbol)->temp_var+"\n";
					}else{
						(yyval.symbol)->code+="\tor ax,"+(yyvsp[0].symbol)->temp_var+"\n";
					}
					(yyval.symbol)->code+="\tmov "+(yyval.symbol)->code+",ax\n";

			 		(yyval.symbol)->var_type="int";  
			 		fprintf(parseLog, "\nAt line no : %d logic_expression : rel_expression LOGICOP rel_expression\n\n",yylineno ); 
					(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName()); 
					fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str()); 
					}
#line 2329 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 766 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[0].symbol); 
					fprintf(parseLog, "\nAt line no : %d rel_expression : simple_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 771 "lex.y" /* yacc.c:1646  */
    { /* Relational Opertator type is Integer */
					(yyval.symbol)=(yyvsp[-2].symbol);
					char *temp=newTemp();
					(yyval.symbol)->temp_var=string(temp);
					(yyval.symbol)->code+="\tmov ax,"+(yyvsp[-2].symbol)->temp_var+"\n";
					(yyval.symbol)->code+="\tcmp ax,"+(yyvsp[0].symbol)->temp_var+"\n";
					string do_work=string(newLabel());
					string escape_work=string(newLabel());

					if((yyvsp[-1].symbol)->getName()=="<")
                    	(yyval.symbol)->code+="\tjge "+do_work+"\n";
                    else if((yyvsp[-1].symbol)->getName()=="<=")
                        (yyval.symbol)->code+="\tjg "+do_work+"\n";
                    else if((yyvsp[-1].symbol)->getName()==">")
                        (yyval.symbol)->code+="\tjle "+do_work+"\n";
                    else if((yyvsp[-1].symbol)->getName()==">=")
                        (yyval.symbol)->code+="\tjl "+do_work+"\n";
                    else
                        (yyval.symbol)->code+="\tjne "+do_work+"\n";
					
					(yyval.symbol)->code+="\tmov "+(yyval.symbol)->temp_var+",1\n";
                    (yyval.symbol)->code+="\tjmp "+escape_work+"\n";
                    (yyval.symbol)->code+=do_work+":\n";
					(yyval.symbol)->code+="\tmov "+(yyval.symbol)->temp_var+",0\n";
                    (yyval.symbol)->code+=escape_work+":\n";

					(yyval.symbol)->var_type="int"; 
					fprintf(parseLog, "\nAt line no : %d rel_expression : simple_expression RELOP simple_expression\n\n",yylineno ); 
					(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName()); 
					fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str()); 
					}
#line 2375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 804 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[0].symbol);
					fprintf(parseLog, "\nAt line no : %d simple_expression : term\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 2385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 809 "lex.y" /* yacc.c:1646  */
    {
			  		(yyval.symbol)=(yyvsp[-2].symbol);
					(yyval.symbol)->code+=(yyvsp[0].symbol)->code;
					(yyval.symbol)->code+="\tmov ax,"+(yyvsp[-2].symbol)->temp_var+"\n";
					(yyval.symbol)->code+="\tmov bx,"+(yyvsp[0].symbol)->temp_var+"\n";
					char* temp=newTemp();
					(yyval.symbol)->temp_var=string(temp);

					if((yyvsp[-1].symbol)->getName()=="+"){
						(yyval.symbol)->code+="\tadd ax,bx\n";
						
					}else{
						(yyval.symbol)->code+="\\tsub ax,bx\n";
					}
					(yyval.symbol)->code+="\tmov "+(yyval.symbol)->temp_var+", ax\n";

			  		if((yyvsp[-2].symbol)->var_type=="float" || (yyvsp[0].symbol)->var_type=="float") (yyval.symbol)->var_type="float";
					else (yyval.symbol)->var_type="int";
			  		fprintf(parseLog, "\nAt line no : %d simple_expression : simple_expression ADDOP term\n\n",yylineno ); 
					(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName()); 
					fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str()); 
					}
#line 2412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 833 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[0].symbol);
				fprintf(parseLog, "\nAt line no : %d term : unary_expression\n\n",yylineno ); 
				fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
				}
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 838 "lex.y" /* yacc.c:1646  */
    {
		 		(yyval.symbol)=(yyvsp[-2].symbol);
				(yyval.symbol)->code="\tmov ax,"+(yyvsp[-2].symbol)->temp_var+"\n";
				(yyval.symbol)->code+="\tmov bx,"+(yyvsp[0].symbol)->temp_var+"\n";
				(yyval.symbol)->code+="\txor dx,dx\n";
				char *temp=newTemp();
				(yyval.symbol)->temp_var=temp;
				if((yyvsp[-1].symbol)->getName()=="*"){
					(yyval.symbol)->code+="\tmul bx\n";
					(yyval.symbol)->code+="\tmov "+(yyval.symbol)->temp_var+",ax\n";
				}else if((yyvsp[-1].symbol)->getName()=="/"){
					(yyval.symbol)->code+="\tdiv bx\n";
					(yyval.symbol)->code+="\tmov "+(yyval.symbol)->temp_var+",ax\n";
				}else{
					(yyval.symbol)->code+="\tdiv bx\n";
					(yyval.symbol)->code+="\tmov "+string(temp)+",dx\n";
				}

		 		if((yyvsp[-1].symbol)->getName()!="%"){
					if((yyvsp[-2].symbol)->var_type=="float" || (yyvsp[0].symbol)->var_type=="float") (yyval.symbol)->var_type="float";
					else (yyval.symbol)->var_type="int";
				}else {
					if((yyvsp[-2].symbol)->var_type!="int" || (yyvsp[0].symbol)->var_type!="int"){
						yyerror(moderror);
					}else (yyval.symbol)->var_type="int";
				}
		 		
		 		fprintf(parseLog, "\nAt line no : %d term : term MULOP unary_expression\n\n",yylineno ); 
				(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName()); 
				fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str()); 
				}
#line 2458 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 871 "lex.y" /* yacc.c:1646  */
    {
					(yyval.symbol)=(yyvsp[0].symbol);
                    string temp=newTemp();
                    (yyval.symbol)->code+="\tmov ax,"+(yyval.symbol)->temp_var+"\n";
                    (yyval.symbol)->code+="\tmov "+temp+",ax\n";
					(yyval.symbol)->temp_var=temp;
					if((yyvsp[-1].symbol)->getName() == "-"){
						(yyval.symbol)->code="\tneg "+(yyvsp[0].symbol)->temp_var+"\n";
					}
					fprintf(parseLog, "\nAt line no : %d unary_expression : ADDOP unary_expression\n\n",yylineno ); 
					(yyval.symbol)->setName((yyvsp[-1].symbol)->getName()+(yyvsp[0].symbol)->getName()); 
					fprintf(parseLog,"%s\n",(yyvsp[-1].symbol)->getName().c_str()); 
					}
#line 2476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 884 "lex.y" /* yacc.c:1646  */
    {
			 		(yyval.symbol)=(yyvsp[0].symbol);
                    string t=newTemp();
                    (yyval.symbol)->code+="\tmov ax,"+(yyvsp[0].symbol)->temp_var+"\n";
                    (yyval.symbol)->code+="\tmov "+t+",ax\n";
                    (yyval.symbol)->temp_var=t;
                    (yyval.symbol)->code+="\tnot "+(yyval.symbol)->temp_var+"\n";

			 		(yyval.symbol)->var_type="int";
			 		fprintf(parseLog, "\nAt line no : %d unary_expression : NOT unary_expression\n\n",yylineno ); 
					(yyval.symbol)->setName("!"+(yyvsp[0].symbol)->getName()); 
					fprintf(parseLog,"%s\n",("!"+(yyvsp[0].symbol)->getName()).c_str()); 
					}
#line 2494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 897 "lex.y" /* yacc.c:1646  */
    {
			 		(yyval.symbol)=(yyvsp[0].symbol);
			 		fprintf(parseLog, "\nAt line no : %d unary_expression : factor\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 904 "lex.y" /* yacc.c:1646  */
    {

				(yyval.symbol)=(yyvsp[0].symbol);
				//cout<<$1->ret_type<<" "<<$1->getName()<<endl;
				//cout<<"mara"<<endl;
				if((yyvsp[0].symbol)->arr)
                {
                    string temp=newTemp();
                    (yyval.symbol)->code+="\tmov ax,"+(yyval.symbol)->temp_var+"\n";
                    (yyval.symbol)->code+="\tmov "+temp+",ax\n";
                    (yyval.symbol)->temp_var=temp;
                }

				fprintf(parseLog, "\nAt line no : %d factor : variable\n\n",yylineno ); 
				(yyval.symbol)->setName((yyvsp[0].symbol)->getName()); 
				fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
				}
#line 2526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 921 "lex.y" /* yacc.c:1646  */
    { /* Function Call */

				(yyval.symbol)->code="\tcall "+(yyvsp[-3].symbol)->getName()+"\n";
				(yyval.symbol)->arr=false;
				
				symbolInfo=getSymbol((yyvsp[-3].symbol)->getName()); if(symbolInfo!=0) {
					(yyval.symbol)->var_type=symbolInfo->ret_type;
					if(symbolInfo->parNum!=argNum){
						 yyerror("\nError at line %d, Parameter number doesn't match!\n");
						 cout<<symbolInfo->getName()<< " "<< symbolInfo->parNum<< " "<<argNum<<endl;
					}
					else if(!matchPL(symbolInfo->parTList,argType,argNum)) yyerror("\nError at line %d. Parameter type doesn't match\n");
					if(!symbolInfo->func_defined) yyerror("\nError at line :%d. Function %s not defined\n",(yyvsp[-3].symbol)->getName());
				} else{
					yyerror(undecfunc,(yyvsp[-3].symbol)->getName());
				} argNum=0;
				fprintf(parseLog, "\nAt line no : %d factor : ID LPAREN argument_list RPAREN\n\n",yylineno ); 
				(yyval.symbol)->setName((yyvsp[-3].symbol)->getName()+"("+(yyvsp[-1].symbol)->getName() +")" ); 
				fprintf(parseLog,"%s\n",(yyvsp[-3].symbol)->getName().c_str()); 
				}
#line 2551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 941 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[-1].symbol);
				fprintf(parseLog, "\nAt line no : %d factor : LPAREN expression RPAREN\n\n",yylineno ); 
				(yyval.symbol)->setName("("+(yyvsp[-1].symbol)->getName()+")"); 
				fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str()); 
				}
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 947 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[0].symbol);
				(yyval.symbol)->temp_var=(yyvsp[0].symbol)->getName();
				(yyval.symbol)->arr=false;
				
				vType="int"; (yyval.symbol)->var_type="int";
				fprintf(parseLog, "\nAt line no : %d factor : CONST_INT\n\n",yylineno ); 
				fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
				}
#line 2576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 956 "lex.y" /* yacc.c:1646  */
    { 
				(yyval.symbol)=(yyvsp[0].symbol);
				(yyval.symbol)->temp_var=(yyvsp[0].symbol)->getName();
				(yyval.symbol)->arr=false;

				vType="float"; (yyval.symbol)->var_type="float";
				fprintf(parseLog, "\nAt line no : %d factor : CONST_FLOAT\n\n",yylineno );
				fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
				}
#line 2590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 965 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[-1].symbol);
				(yyval.symbol)->code+="\tinc "+(yyvsp[-1].symbol)->temp_var+"\n";

				fprintf(parseLog, "\nAt line no : %d factor : variable INCOP\n\n",yylineno ); 
				(yyval.symbol)->setName((yyvsp[-1].symbol)->getName() + "++"); 
				fprintf(parseLog,"%s\n",(yyvsp[-1].symbol)->getName().c_str()); 
				}
#line 2603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 973 "lex.y" /* yacc.c:1646  */
    {
				(yyval.symbol)=(yyvsp[-1].symbol);
				(yyval.symbol)->code+="\tinc "+(yyvsp[-1].symbol)->temp_var+"\n";

				fprintf(parseLog, "\nAt line no : %d factor : variable DECOP\n\n",yylineno ); 
				(yyval.symbol)->setName((yyvsp[-1].symbol)->getName() + "--"); 
				fprintf(parseLog,"%s\n",(yyvsp[-1].symbol)->getName().c_str()); 
				}
#line 2616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 983 "lex.y" /* yacc.c:1646  */
    { 

					fprintf(parseLog, "\nAt line no : %d argument_list : arguments\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str()); 
					}
#line 2626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 988 "lex.y" /* yacc.c:1646  */
    {(yyval.symbol)=new SymbolInfo();}
#line 2632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 991 "lex.y" /* yacc.c:1646  */
    {
					
					argType[argNum]=(yyvsp[0].symbol)->var_type; argNum++;
					fprintf(parseLog, "\nAt line no : %d arguments : arguments COMMA logic_expression\n\n",yylineno ); 
					(yyval.symbol)->setName((yyvsp[-2].symbol)->getName()+","+(yyvsp[0].symbol)->getName()); 
					fprintf(parseLog,"%s\n",(yyvsp[-2].symbol)->getName().c_str());
					}
#line 2644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 998 "lex.y" /* yacc.c:1646  */
    {
			  		
					argType[argNum]=(yyvsp[0].symbol)->var_type; argNum++;
					fprintf(parseLog, "\nAt line no : %d arguments : logic_expression\n\n",yylineno );
					fprintf(parseLog,"%s\n",(yyvsp[0].symbol)->getName().c_str());
					}
#line 2655 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2659 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1007 "lex.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{
	

	int yydebug=1;
	FILE *input=0;

	if(argc<3){
		cout<<"Input not right!"<<endl;
	}else{
		input=fopen(argv[1],"r"); cout<<argv[1]<<endl;
		parseLog=fopen(argv[2],"w"); cout<<argv[2]<<endl;
		parseError=fopen(argv[3],"w"); cout<<argv[3]<<endl;
		gCode=fopen("code.asm","w");
	}
	
	//FILE *input=fopen("input.txt","r");
	yyin=input;

	//parseLog=fopen("log.txt","w");
	//parseError=fopen("error.txt","w");
	if(parseLog==NULL or input==NULL or parseError==NULL or gCode==NULL){
		printf("Error. Unable to open file\n");
		exit(1);
	}

	yyparse();
	

	fprintf(parseLog,"\n\ttotal lines: %d\n\n",yylineno);
	fprintf(parseError,"\ntotal errors: %d",tperror);
	
	fclose(parseLog);
	fclose(parseError);
	fclose(input);
	
	fprintf(logOut,"\nTotal errors: %d",terror);
	fclose(logOut);
	fclose(tokenOut);
	//fclose(fp2);
	//fclose(fp3);
	
	return 0;
}

/*if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	fp2= fopen(argv[2],"w");
	fclose(fp2);
	fp3= fopen(argv[3],"w");
	fclose(fp3);
	
	fp2= fopen(argv[2],"a");
	fp3= fopen(argv[3],"a");
	

	yyin=fp;*/
