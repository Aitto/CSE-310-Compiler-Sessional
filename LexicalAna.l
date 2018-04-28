%option noyywrap

%{
#include<stdio.h>
#include<stdlib.h>

int count=0;
int strings=0;
int num=0;
int fnum=0;
int exnum=0;
int nline=0;
int wspace=0;
int lineNumber=0;

FILE *fin;
FILE *tokenOut;
FILE *logOut;

char *upstr(char *s){
	char* str=(char*)malloc((sizeof(char)*33));
	int i=0;
	while(s[i]!='\0'){
		if(s[i]>='a' && s[i]<='z'){
			str[i]=s[i]-'a' +'A';
		}else str[i]=s[i];

		i++;

	}
	str[i]='\0';
	return str;
}

%}

digit [0-9]
digits {digit}+
floatingPoint {digits}\.{digits}
expoNumber {digits}\.{digits}?[E][+-]?{digits}
whitespace " "
newline [\n]
alphabet [a-z_A-Z]
alphanumeric {alphabet}({alphabet}|{digit})*
keyword if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue

%%

{keyword} 	{
		fprintf(tokenOut,"<%s>",upstr(yytext));
		printf("Found keyword %s\n",yytext);
		count++;
		}
{whitespace}	{}
{newline}	{
		lineNumber++;
		}

{alphanumeric}	{
		printf("Found alphanumeric string %s\n",yytext);
		strings++;
		}
{digits}	{
	printf("Found digits %s\n",yytext);
	num++;
	}
{floatingPoint} {
		printf("Found floating point number %s\n",yytext);
		fnum++;
		}
{expoNumber}	{
		printf("Found exponential number %s\n",yytext);
		exnum++;
		}


%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	tokenOut=fopen("token.txt","w");
	logOut=fopen("log.txt","w");
	
	yyin= fin;
	yylex();
	printf("Strings %d\n",strings);
	printf("Key words %d\n",count);
	printf("integers: %d\n",num);
	printf("floating point: %d\n",fnum);
	printf("exponential number: %d\n",exnum);
	printf("newines: %d\n",lineNumber);
	//printf("ex: %s",strupr("medera hagoija"));

     	return 0;
}











