%{
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define YYSTYPE double 
extern char *yytext;

void yyerror(char *s){
	printf("%s\n",s);
}

FILE *file;

int yylex(void);

%}

%union{
    int ival;
    float fval;
    double dval;
}

%token NEWLINE PLUS MINUS SLASH ASTERISK LPAREN RPAREN ID CONST_KEY
%token<fval> CFLOAT
%token<> CINT



%%

input:              /* empty string */
    | input line
    ;
line: NEWLINE
    | expr NEWLINE           { printf("\t%.10g\n",$1); }
    | key NEWLINE
    ;
key: CONST_KEY              {printf("%s",yytext);}
    | ID                    {printf("%s",yytext);}
    ;
expr: expr PLUS term         { $$ = $1 + $3; printf("matched rule: expr: expr PLUS term   \n"); }
    | expr MINUS term        { $$ = $1 - $3; printf("matched rule: expr: expr MINUS term   \n"); }
    | term  { printf("matched rule: expr: term   \n"); }
    ;
term: term ASTERISK factor   { $$ = $1 * $3; printf("matched rule: term: term ASTERISK factor   \n"); }
    | term SLASH factor      { $$ = $1 / $3; printf("matched rule: term: term SLASH factor   \n");  }
    | factor    { printf("matched rule: term: factor   \n"); }
    ;
factor:  LPAREN expr RPAREN  { $$ = $2; printf("matched rule: factor:  LPAREN expr RPAREN \n"); }
      | CFLOAT  { printf("matched rule: factor:  CFLOAT \n"); }
      | CINT    { printf("matched rule: factor:  CINT \n"); }
      ;
%%

int main(int argc,char *argv[])
{

    if((file=fopen("parser.txt","w"))==NULL){
        printf("Unable to ope file!");
        exit(1);
    }

    yyparse();
    exit(0);
}
