%option noyywrap yylineno

%{
#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"

%}

digit [0-9]
digits {digit}+
floatingPoint {digits}\.{digits}
expoNumber {digits}(\.{digits})?[E][+-]?{digits}
whitespace " "
newline \n
alphabet [a-z_A-Z]
alphanumeric {alphabet}({alphabet}|{digit})*
wid ({digits}|{floatingPoint}|{expoNumber}){alphabet}+
ifn {expoNumber}(\.{digit}*)+
tmdp {floatingPoint}(\.{digit}*)*
unfcom \/\*([^*]|\*+[^/*])*
mlcom \/\*([^*]|\*+[^/*])*\*+\/
slcom \/\/((.*\\{newline}?.*)*|.*)
str \"(\\*[^\\\n"]*|\\(\\\\)*\"|\\+\n)*(\\\\)*\"
unfstr \"(\\*[^\\\n"]*|\\(\\\\)*\"|\\+\n)*
ifstr \"([^"\\]*\n[^"\\]*)\"
keyword if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue

%%
({whitespace}*|\t*)	{ //do nothing just ignore
					}
{newline}	{
			return NEWLINE;
			}

"if"	{return IF;}
"else"	{return ELSE;}
"for"	{return FOR;}
"while"	{return WHILE;}
"do"	{return DO;}
"break"	{return BREAK;}
"int"	{return INT;}
"char"	{return CHAR;}
"float"	{return FLOAT;}
"double"	{return DOUBLE;}
"void"	{return VOID;}
"return"	{return RETURN;}
"switch"	{return SWITCH;}
"case"	{return CASE;}
"default"	{return DEFAULT;}
"continue"	{return CONTINUE;}

{digits}	{//Integer
				sscanf(yytext,"%lf", &yylval);
				return CONST_INT;
			}
{floatingPoint} {//Float
					sscanf(yytext,"%lf", &yylval);
					return CONST_FLOAT;
				}
{expoNumber}	{//Exponential Float
					sscanf(yytext,"%lf", &yylval);
					return CONST_FLOAT;
				}
\'\'		{
				printf("\nError at line %d: Empty character literal %s\n",nline,yytext);
			}
\'(\n|[^'\n]*\n|\\\')	{ //Unfinished character literal like 'b or 'bbbbasd
							printf("\nError at line %d.Unterminated character literal %s\n",nline,yytext);
							//cout<<"Unfinished character literal "<<yytext<<endl; 
						}


\'([^'\\\n][^'\n]+|\\[^'\n][^'\n]+)\'	{ //Multichracter constant like 'abc' '\nb' 'b\n'
					printf("\nError at line %d. Multicharacter constant error for character sequence %s\n",nline,yytext);
					//cout<<"detected "<<yytext<<endl;
					}

\'([^'\\\n]|\\['"\\a-zA-Z0])\'	{ //Finding character literal
				return CONST_CHAR;
				}


"++"|"--"	{
		return INCOP;
		}
[+-]		{
		return ADDOP;
		}
[*/%]		{
		return MULOP;
		}

"<"|"<="|">"|">="|"=="|"!="	{
				return RELOP;
				}

=		{
		return ASSIGNOP;
		}
"&&"|"||"	{
		return LOGICOP;
		}
"&"|"|"|"^"|"<<"|">>"		{
				return BITOP;
				}
"!"		{
		return NOT;
		}
"("		{
		return LPAREN;
		}
")"		{
		return RPAREN;
		}
"{"		{
		return LCUR;
		}
"}"		{
		return RCUR;
		}
"["		{
		return LTHIRD;
		}
"]"		{
		return RTHIRD;
		}
","		{
		return COMMA;
		}
";"		{
		return SEMICOLON;
		}
{unfstr}	{//Unfinished String
		printf("\nError at line %d. Missing terminating character %s\n",nline,yytext);
		}

{str}		{//detecting string
		return STRING;
		}
{slcom}		{//single line comment
		printf("\nLine No. %d: Token <COMMENT> Lexeme %s found\n",nline,yytext);
		}

{unfcom}	{ //Unfinished comment
		printf("\nError at line %d. Unfinished comment %s\n",nline,yytext);
		}
{mlcom}		{ //Multilined comment
		printf("\nToken <COMMENT> Lexeme %s found\n",yytext);
		}
{alphanumeric}	{//Identifier
		return ID;
		}
{wid}	{//Wrong identifier
		printf("\nError at line %d. Invalid prefix on ID or invalid suffix on Number %s\n",nline,yytext);
		}
{ifn}	{//Ill formed number
		printf("\nError at line %d. Ill formed Number %s\n",nline,yytext);
		}
{tmdp}	{//too many decimal points
		printf("\nError at line %d. Too many decimal points for %s\n",nline,yytext);
		}
.		{
		printf("\nError at line %d. unrecognized character %s\n",nline,yytext);
		}

%%






