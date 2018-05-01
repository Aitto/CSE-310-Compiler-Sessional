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
char fixL(char *s){

    char ch;
	if(strlen(s)>3)
	switch(s[2]){
        case 'a': ch='\a';
            break;
        case 'b':
            ch='\b';
            break;
        case 'f':
            ch='\f';
            break;
        case 'n':
            ch='\n';
            break;
        case 'r':
            ch='\r';
            break;
        case 't':
            ch='\t';
            break;
        case '0':
            ch=0;
            break;
        case '\'':
            ch='\'';
            break;
        case '\\':
            ch='\\';
            break;
	}else return s[1];
	return ch;
}

//For cutting front zeroes and checking integer size
char *chknum(char *s,bool flag=true){
    char *str=(char*)malloc(sizeof(char)*32);
    int i=0,j=0;

    while(s[i]=='0') i++;
    while(s[i]!='\0'){
        str[j]=s[i];
        i++,j++;
        if(j>9 and flag){
        if(flag)fprintf(logOut,"Error at line %d: so many digits for an integer %s\n",nline,yytext);
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
expoNumber {digits}(\.{digits})?[E][+-]?{digits}
whitespace " "
newline \n
alphabet [a-z_A-Z]
alphanumeric {alphabet}({alphabet}|{digit})*
keyword if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue
wid {digits}{alphabet}+
ifn {expoNumber}\.{digit}*
tmdp {floatingPoint}(\.{digit}*)*

%%
{whitespace}*	{}
{newline}	{
		//if(!ttokens%5)fprintf(tokenOut,"\n");
		nline++;
		}
{keyword} 	{
		fprintf(logOut,"\nLine No. %d: Token <%s> Lexeme %s found\n",nline,uprstr(yytext),yytext); //Adding to log file
		fprintf(tokenOut,"<%s>",uprstr(yytext)); //Generating token
		ttokens++;
		}

{digits}	{//Integer
		fprintf(logOut,"\nLine No. %d: Token <CONST_INT> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<CONST_INT,%s>",yytext); //Generating token
		manage('I',yytext,"CONST_INT"); //Add to Symbol table
		ttokens++;
		}
{floatingPoint} {//Float
		fprintf(logOut,"\nLine No. %d: Token <CONST_FLOAT> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<CONST_FLOAT,%s>",yytext); //Generating token
		manage('I',yytext,"CONST_FLOAT"); //Add to Symbol table
		ttokens++;
		}
{expoNumber}	{//Exponential Float
		fprintf(logOut,"\nLine No. %d: Token <CONST_FLOAT> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<CONST_FLOAT,%s>",yytext); //Generating token
		//manage('I',yytext,"CONST_FLOAT"); //Add to Symbol table
		ttokens++;
		}

\'(\n|[^'\n]*\n)	{ //Unfinished character literal like 'b or 'bbbbasd
			fprintf(logOut,"\nError at line %d.Unfinished character %s\n",nline,yytext),terror++;
			//cout<<"Unfinished character literal "<<yytext<<endl; 
			}


\'([^'\\\n][^'\n]+|\\[^'\n][^'\n]+)\'	{ //Multichracter constant like 'abc' '\nb' 'b\n'
					fprintf(logOut,"\nError at line %d. Multicharacter constant error for character sequence %s\n",nline,yytext);
					//cout<<"detected "<<yytext<<endl;
					}

\'([^'\\]|\\['"\\abfnrtv0])\'	{ //Finding character literal
				
				fprintf(logOut,"\nLine No. %d: Token <CONST_CHAR> Lexeme %s found\n",nline,yytext); //Adding to log file
				fprintf(tokenOut,"<CONST_CHAR,%c>",fixL(yytext)); //Generating token
				manage('I',yytext,"CONST_CHAR"); //Add to Symbol table
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
		fprintf(logOut,"\nLine No. %d: Token <NOT> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<NOT,!>");
		ttokens++;
		}
"("		{
		fprintf(logOut,"\nLine No. %d: Token <LPAREN> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<LPAREN,(>");
		ttokens++;
		}
")"		{
		fprintf(logOut,"\nLine No. %d: Token <RPAREN> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<RPAREN,)>");
		ttokens++;
		}
"{"		{
		fprintf(logOut,"\nLine No. %d: Token <LCUR> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<LCUR,{>");
		ttokens++;
		}
"}"		{
		fprintf(logOut,"\nLine No. %d: Token <RCUR> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<RCUR,}>");
		ttokens++;
		}
"["		{
		fprintf(logOut,"\nLine No. %d: Token <LTHIRD> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<LTHIRD,[>");
		ttokens++;
		}
"]"		{
		fprintf(logOut,"\nLine No. %d: Token <RTHIRD> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<RTHIRD,]>");
		ttokens++;
		}
","		{
		fprintf(logOut,"\nLine No. %d: Token <COMMA> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<COMMA,,>");
		ttokens++;
		}
";"		{
		fprintf(logOut,"\nLine No. %d: Token <SEMICOLON> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<SEMICOLON,;>");
		ttokens++;
		}
\"([^"\\]*\n[^"\\]*)\"	{//Ill formed string
			fprintf(logOut,"\nError ad line %d. Ill formed string %s. Missing \\ \n",nline,yytext),terror++;
			//cout<< "Ill formed string: "<<yytext<<endl;
			}
\"([^"]*|[^"]*\\\n?[^"]*)	{//Unfinished String
				//\"([^"]*|[^"]*\\\n?[^"]*)
				fprintf(logOut,"\nError at line %d. Unfinished string %s\n",nline,yytext),terror++;
				//cout<< "Unfinished string "<<yytext<<endl;
				}
\"([^"]*\\\n?[^"]*|[^"]*)\"	{//String \"((.*\\{newline}.*)*|.*)\"
				// "([^"]*\\\n?[^"]*|[^"]*)\"
				fprintf(logOut,"\nLine No. %d: Token <STRING> Lexeme %s found\n",nline,yytext); //Adding to log file
				//printf("String found: %s\n",yytext);
				}
\/\/((.*\\{newline}?.*)*|.*)	{//single or \
				multilined comment
				fprintf(logOut,"\nLine No. %d: Token <COMMENT> Lexeme %s found\n",nline,yytext); //Adding to log file
				//printf("Single line comment found: %s\n",yytext);
				}
\/\*([^*]|\*+[^/*])*\*+\/	{ //Multilined comment
				fprintf(logOut,"\nToken <COMMENT> Lexeme %s found\n",yytext);
				//cout<<"Multilined comment found! "<<yytext<<endl; 
				 // \/\*([^*])\*\/
				}


{alphanumeric}	{
		fprintf(logOut,"\nLine No. %d: Token <ID> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<ID,%s>",yytext);
		manage('I',yytext,"ID"); //Add to Symbol table
		ttokens++;
		}
{wid}		{//Wrong identifier
		fprintf(logOut,"\nError at line %d. Invalid prefix on ID or invalid suffix on Number %s\n",nline,yytext),terror++;
		}
{ifn}		{//Ill formed number
		fprintf(logOut,"\nError at line %d. Ill formed Number %s\n",nline,yytext),terror++;
		}
{tmdp}		{//too many decimal points
		fprintf(logOut,"\nError at line %d. Too many decimal points for %s\n",nline,yytext),terror++;
		}
.	{
	fprintf(logOut,"\nError at line %d. unrecognized character %s\n",nline,yytext),terror++;
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
	
	fprintf(logOut,"Total lines: %d\n",nline);
	fprintf(logOut,"Total errors: %d\n",terror);
	fclose(fin);
	fclose(tokenOut);
	fclose(logOut);

     	return 0;
}





