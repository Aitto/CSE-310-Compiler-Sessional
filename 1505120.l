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

char * fixS(char *s){
//abfnrt0\'

    char *ans=new char[sizeof(s) +1];
    int i=0,j=0;

    while(s[j]!='\0'){
        if(s[j]=='\\'){
            j++;
            switch(s[j]){
                case 'a':
                ans[i]='\a';
                break;
                case 'b':
                ans[i]='\b';
                break;
                case 'f':
                ans[i]='\f';
                break;
                case 'n':
                ans[i]='\n';
                break;
                case 'r':
                ans[i]='\r';
                break;
                case 't':
                ans[i]='\t';
                break;
                case '\n':
                break;
                default:
                ans[i]=s[j];

            }i++,j++;
            continue;
        }
        ans[i]=s[j];
        i++;
        j++;
    }

    ans[i]='\0';
    return ans;
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
unfcom \/\*([^*]|\*+[^/*])*
mlcom \/\*([^*]|\*+[^/*])*\*+\/
slcom \/\/((.*\\{newline}?.*)*|.*)
str \"(([^\\\n"]*(\\+\n?)?)*)\" 
unfstr \"(([^"\\\n]*(\\+\n?)?)*)
ifstr \"([^"\\]*\n[^"\\]*)\"

%%
({whitespace}*|\t*)	{//str \"(([^\\\n"]*\\+\n?[^"\\\n]*)*|[^"\\\n]*)\" 
			//unfstr \"([^"\n]*|([^"\\\n]*\\+\n?[^"]*)*)
			}
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
\'\'		{
		fprintf(logOut,"\nError at line %d: Empty character literal %s\n",nline,yytext),terror++;
		}
\'(\n|[^'\n]*\n|\\\')	{ //Unfinished character literal like 'b or 'bbbbasd
			fprintf(logOut,"\nError at line %d.Unterminated character literal %s\n",nline,yytext),terror++;
			int temp=strlen(yytext);
			for(int i=0;i<temp;i++) if(yytext[i]=='\n') nline++;
			//cout<<"Unfinished character literal "<<yytext<<endl; 
			}


\'([^'\\\n][^'\n]+|\\[^'\n][^'\n]+)\'	{ //Multichracter constant like 'abc' '\nb' 'b\n'
					fprintf(logOut,"\nError at line %d. Multicharacter constant error for character sequence %s\n",nline,yytext),terror++;
					int temp=strlen(yytext);
					for(int i=0;i<temp;i++) if(yytext[i]=='\n') nline++;
					//cout<<"detected "<<yytext<<endl;
					}

\'([^'\\\n]|\\['"\\abfnrtv0])\'	{ //Finding character literal
				
				fprintf(logOut,"\n Line No. %d: Token <CONST_CHAR> Lexeme %s found\n",nline,yytext); //Adding to log file
				fprintf(tokenOut,"<CONST_CHAR,%c>",fixL(yytext)); //Generating token
				manage('I',yytext,"CONST_CHAR"); //Add to Symbol table
				ttokens++;
				}


"++"|"--"	{
		fprintf(logOut,"\nLine No. %d: Token <INCOP> Lexeme %s found\n",nline,yytext);
		fprintf(tokenOut,"<INCOP,%s>",yytext),ttokens++;
		}
[+-]		{
		fprintf(logOut,"\nLine No. %d: Token <ADDOP> Lexeme %s found\n",nline,yytext);
		fprintf(tokenOut,"<ADDOP,%s>",yytext),ttokens++;
		}
[*/%]		{
		fprintf(logOut,"\nLine No. %d: Token <MULOP> Lexeme %s found\n",nline,yytext);
		fprintf(tokenOut,"<MULOP,%s>",yytext),ttokens++;
		}

"<"|"<="|">"|">="|"=="|"!="	{
				fprintf(logOut,"\nLine No. %d: Token <RELOP> Lexeme %s found\n",nline,yytext);
				fprintf(tokenOut,"<RELOP,%s>",yytext),ttokens++;
				}

=		{
		fprintf(logOut,"\nLine No. %d: Token <ASSIGNOP> Lexeme %s found\n",nline,yytext);
		fprintf(tokenOut,"<ASSIGNOP,%s>",yytext),ttokens++;
		}
"&&"|"||"	{
		fprintf(logOut,"\nLine No. %d: Token <LOGICOP> Lexeme %s found\n",nline,yytext);
		fprintf(tokenOut,"<LOGICOP,%s>",yytext),ttokens++;
		}
"&"|"|"|"^"|"<<"|">>"		{
				fprintf(logOut,"\nLine No. %d: Token <BITOP> Lexeme %s found\n",nline,yytext);
				fprintf(tokenOut,"<BITOP,%s>",yytext),ttokens++;
				}
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

{unfstr}	{//Unfinished String
		//\"([^"]*|[^"]*\\\n?[^"]*)
		fprintf(logOut,"\nError at line %d. Missing terminating character %s\n",nline,yytext),terror++;
		int temp=strlen(yytext);
		for(int i=0;i<temp;i++) if(yytext[i]=='\n') nline++;
		//cout<< "Unfinished string "<<yytext<<endl;
		}
{str}		{//String \"((.*\\{newline}.*)*|.*)\"
		// "([^"]*\\\n?[^"]*|[^"]*)\"
		fprintf(logOut,"\nLine No. %d: Token <STRING> Lexeme %s found\n",nline,yytext); //Adding to log file
		fprintf(tokenOut,"<STRING, %s>",fixS(yytext));
		int temp=strlen(yytext);
		for(int i=0;i<temp;i++) if(yytext[i]=='\n') nline++;
		//printf("String found: %s\n",yytext);
		}
{slcom}		{//single or \
		multilined comment
		fprintf(logOut,"\nLine No. %d: Token <COMMENT> Lexeme %s found\n",nline,yytext); //Adding to log file
		int temp=strlen(yytext);
		for(int i=0;i<temp;i++) if(yytext[i]=='\n') nline++;
		//printf("Single line comment found: %s\n",yytext);
		}

{unfcom}	{ //Unfinished comment
		fprintf(logOut,"\nError at line %d. Unfinished comment %s\n",nline,yytext),terror++;
		int temp=strlen(yytext);
		for(int i=0;i<temp;i++) if(yytext[i]=='\n') nline++;
		}
{mlcom}		{ //Multilined comment
		fprintf(logOut,"\nToken <COMMENT> Lexeme %s found\n",yytext);
		int temp=strlen(yytext);
		for(int i=0;i<temp;i++) if(yytext[i]=='\n') nline++;
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
.		{
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
	printf("total lines: %d\n",nline-1);
	printf("total errors: %d\n",terror);
	
	fprintf(logOut,"Total lines: %d\n",nline-1);
	fprintf(logOut,"Total errors: %d\n",terror);
	fclose(fin);
	fclose(tokenOut);
	fclose(logOut);

     	return 0;
}





