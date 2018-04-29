%option noyywrap

%{
#include<stdio.h>
int word=0;
%}

%%

[a-zA-Z]+	{
		word++;
}

%%

int main(int argc,char *argv[])
{
yylex();
printf("%d\n",word);
return 0;
}

