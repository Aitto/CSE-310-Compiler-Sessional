%option noyywrap yylineno

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "y.tab.h"

%}

ws [ \t\b]
digit [0-9]
number [+-]?{digit}+(\.{digit}+)?

%%
{number}    {
                sscanf(yytext,"%lf", &yylval);
                return NUMBER;
            }
"+"       { return PLUS; }
"-"       { return MINUS; }
"/"       { return SLASH; }
"*"       { return ASTERISK; }
"("       { return LPAREN; }
")"       { return RPAREN; }
"\n"      { return NEWLINE; }

{ws}    {/* ignore... do nothing */}

%%

