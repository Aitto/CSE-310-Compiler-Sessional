%option noyywrap

%{
//#include<stdio.h>
//#include<stdlib.h>
#include "symbolMain.cpp"
int error=0;
int nline=1;
int tno=0;
int ttokens=0;
int terror=0;

//FILE *fin;
//FILE *tokenOut;
//FILE *logOut;

//For getting uppercase characters
char *uprstr(char *s){
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

char fixLiteral(char *s){
	return s[2];
}

//For cutting front zeroes and checking integer size
char *chknum(char *s){
    char *str=(char*)malloc(sizeof(char)*32);
    int i=0,j=0;

    while(s[i]=='0') i++;
    while(s[i]!='\0'){
        str[j]=s[i];
        i++,j++;
        if(j>9){
        fprintf(logOut,"Error at line %d, %s oo many digits for an integer\n",nline,yytext);
        break;
        }
    }
    str[j]='\0';

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
wid {digits}{alphabet}+


%%
{whitespace}*	{}
{newline}	{
		//if(!ttokens%5)fprintf(tokenOut,"\n");
		nline++;
		}
{keyword} 	{
		fprintf(logOut,"Line No. %d: Token <%s> Lexeme %s found\n",nline,uprstr(yytext),yytext);
		fprintf(tokenOut,"<%s>",uprstr(yytext));
		ttokens++;
		}
{wid}		{
		fprintf(logOut,"Error at line %d. Identifier %s defiened wrong\n",nline,yytext);
		}

{digits}	{
		fprintf(tokenOut,"<CONST_INT,%s>",chknum(yytext));
		manage('I',chknum(yytext),"CONST_INT");
		ttokens++;
		}
{floatingPoint} {
		fprintf(tokenOut,"<CONST_FLOAT,%s>",yytext);
		ttokens++;
		}
{expoNumber}	{
		fprintf(tokenOut,"<CONST_FLOAT,%s>",yytext);
		ttokens++;
		}
\'([^'\\]|\\['"\\abfnrtv0])\'	{
				fprintf(tokenOut,"<CONST_CHAR,%c>",fixLiteral(yytext));
				ttokens++;
				}
{alphanumeric}	{
		fprintf(tokenOut,"<ID,%s>",yytext);
		ttokens++;
		}


"++"|"--"	fprintf(tokenOut,"<INCOP,%s>",yytext),ttokens++;
[+-]		fprintf(tokenOut,"<ADDOP,%s>",yytext),ttokens++;
[*/%]		fprintf(tokenOut,"<MULOP,%s>",yytext),ttokens++;

"<"|"<="|">"|">="|"=="|"!="	fprintf(tokenOut,"<RELOP,%s>",yytext),ttokens++;

=		fprintf(tokenOut,"<ASSIGNOP,%s>",yytext),ttokens++;
"&&"|"||"			fprintf(tokenOut,"<LOGICOP,%s>",yytext),ttokens++;
"&"|"|"|"^"|"<<"|">>"		fprintf(tokenOut,"<BITOP,%s>",yytext),ttokens++;
"!"		{
		fprintf(tokenOut,"<NOT,!>");
		ttokens++;
		}
"("		{
		fprintf(tokenOut,"<LPAREN,(>");
		ttokens++;
		}
")"		{
		fprintf(tokenOut,"<RPAREN,)>");
		ttokens++;
		}
"{"		{
		fprintf(tokenOut,"<LCUR,{>");
		ttokens++;
		}
"}"		{
		fprintf(tokenOut,"<RCUR,}>");
		ttokens++;
		}
"["		{
		fprintf(tokenOut,"<LTHIRD,[>");
		ttokens++;
		}
"]"		{
		fprintf(tokenOut,"<RTHIRD,]>");
		ttokens++;
		}
","		{
		fprintf(tokenOut,"<COMMA,,>");
		ttokens++;
		}
";"		{
		fprintf(tokenOut,"<SEMICOLON,;>");
		ttokens++;
		}

%%

int main(int argc,char *argv[]){
	hashSize=50;
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	st.enterScope(hashSize);
	
	tokenOut=fopen("token.txt","w");
	logOut=fopen("log.txt","w");
	
	yyin= fin;
	yylex();
	printf("newines: %d\n",nline);

	fclose(fin);
	fclose(tokenOut);
	fclose(logOut);

     	return 0;
}





