%option noyywrap yylineno

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "y.tab.h"
extern YYSTYPE yylval;
int nline=0;
%}

newline \n
ws [ \t]
digit [0-9]
digits {digit}+
floats {digits}\.{digits}
keyword int|float|if|else
letter [a-z_A-z]
id {letter}({letter}|{digits})*

%%

{ws}        {   
    /* do nothing */
}

{newline}   { printf("%d",nline); nline++; return NEWLINE;}
{keyword}   {return CONST_KEY;}
{digits}    {
    //yylval.ival=atoi(yytext);
    sscanf(yytext,"%lf",&yylval);
    return CINT;
  }
{floats}    {
    //yylva.dval= new atof(yytext);
    sscanf(yytext,"%lf",&yylval);
    return CFLOAT;
}
{id}        {return ID;}
"+"       { return PLUS; }
"-"       { return MINUS; }
"/"       { return SLASH; }
"*"       { return ASTERISK; }
"("       { return LPAREN; }
")"       { return RPAREN; }


%%