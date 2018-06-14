%option yylineno

%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "1505120_Symbol_Info.cpp"
#include "y.tab.h"


int error=0;
int tno=0;
int terror=0;
int ttokens=0;
extern YYSTYPE yylval;

//FILE *fin;
FILE *tokenOut=fopen("scanner_token.txt","w");
FILE *logOut=fopen("scanner_log.txt","w");

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
		i++,j++;
                break;
                case 'b':
                ans[i]='\b';
		i++,j++;
                break;
                case 'f':
                ans[i]='\f';
		i++,j++;
                break;
                case 'n':
                ans[i]='\n';
		i++,j++;
                break;
		case '0':
		//ans[i]='\\',i++;
		ans[i]=27;
		i++,j++;
		break;
                case 'r':
                ans[i]='\r';
		i++,j++;
                break;
                case 't':
                ans[i]='\t';
		i++,j++;
                break;
                case '\n':
		ans[i]=' ';
		i++,j++;
                break;
                default:
                ans[i]=s[j];
		i++,j++;

            }//i++,j++;
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
            ch=1;
            break;
        case '\'':
            ch='\'';
            break;
        case '\\':
            ch='\\';
            break;
	default:
	    ch=s[2];
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
        if(flag)fprintf(logOut,"Error at line %d: so many digits for an integer %s\n",yylineno,yytext);
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
wid ({digits}|{floatingPoint}|{expoNumber}){alphabet}+
ifn {expoNumber}(\.{digit}*)+
tmdp {floatingPoint}(\.{digit}*)*
unfcom \/\*([^*]|\*+[^/*])*
mlcom \/\*([^*]|\*+[^/*])*\*+\/
slcom \/\/((.*\\{newline}?.*)*|.*)
str \"(\\*[^\\\n"]*|\\(\\\\)*\"|\\+\n)*(\\\\)*\"
unfstr \"(\\*[^\\\n"]*|\\(\\\\)*\"|\\+\n)*
ifstr \"([^"\\]*\n[^"\\]*)\"

%%
({whitespace}*|\t*)	{ //just ignore

}
{newline}	{
			//return NEWLINE;
			//I think I'll just ignore it. Don't need to do anything!
			}
if		{
			fprintf(logOut,"\nLine No. %d: Token <IF> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<IF>",yytext); yylval.symbol=new SymbolInfo(yytext);
			return IF; 
		}
else	{
	fprintf(logOut,"\nLine No. %d: Token <ELSE> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<ELSE>",yytext); yylval.symbol=new SymbolInfo(yytext);
	return ELSE;
	}
for	{
	fprintf(logOut,"\nLine No. %d: Token <FOR> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<FOR>",yytext); //yylval.symbol=new SymbolInfo(yytext);
	return FOR;
	}
while	{
	fprintf(logOut,"\nLine No. %d: Token <WHILE> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<WHILE>",yytext); yylval.symbol=new SymbolInfo(yytext);
	return WHILE;
}
do	{
	fprintf(logOut,"\nLine No. %d: Token <DO> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<DO>",yytext);
	return DO;
}
break	{
	fprintf(logOut,"\nLine No. %d: Token <BREAK> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<BREAK>",yytext); 
	return BREAK;
}
int	{
	fprintf(logOut,"\nLine No. %d: Token <INT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<INT>",yytext); yylval.symbol=new SymbolInfo(yytext);
	return INT;
}
float	{
	fprintf(logOut,"\nLine No. %d: Token <FLOAT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<FLOAT>",yytext);	yylval.symbol=new SymbolInfo(yytext);
	return FLOAT;
	}
double	{
	fprintf(logOut,"\nLine No. %d: Token <DOUBLE> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<DOUBLE>",yytext);
	return DOUBLE;
	}
void	{
	fprintf(logOut,"\nLine No. %d: Token <VID> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<VOID>",yytext);	yylval.symbol=new SymbolInfo(yytext);
	return VOID;
	}
return	{
	fprintf(logOut,"\nLine No. %d: Token <RETURN> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<RETURN>",yytext);
	return RETURN;
	}
switch	{
	fprintf(logOut,"\nLine No. %d: Token <SWITCH> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<SWITCH>",yytext);
	return SWITCH;
	}
case	{
	fprintf(logOut,"\nLine No. %d: Token <CASE> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<CASE>",yytext);
	return CASE;
	}
default	{
	fprintf(logOut,"\nLine No. %d: Token <DEFAULT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<DEFAULT>",yytext);
	return DEFAULT;
	}
continue	{
	fprintf(logOut,"\nLine No. %d: Token <CONTINUE> Lexeme %s found\n",yylineno,yytext); //Adding to log file
	fprintf(tokenOut,"<CONTINUE>",yytext);
	return CONTINUE;
	}

{digits}	{//Integer
				fprintf(logOut,"\nLine No. %d: Token <CONST_INT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
				fprintf(tokenOut,"<CONST_INT,%s>",yytext); //Generating token
				
				ttokens++; yylval.symbol=new SymbolInfo(yytext); yylval.symbol->setIval(atoi(yytext));

				return CONST_INT;
			}
{floatingPoint} {//Float
				fprintf(logOut,"\nLine No. %d: Token <CONST_FLOAT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
				fprintf(tokenOut,"<CONST_FLOAT,%s>",yytext); //Generating token
				
				ttokens++; yylval.symbol=new SymbolInfo(yytext); yylval.symbol->setDval(atof(yytext));
				return CONST_FLOAT;
				}
{expoNumber}	{//Exponential Float
				fprintf(logOut,"\nLine No. %d: Token <CONST_FLOAT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
				fprintf(tokenOut,"<CONST_FLOAT,%s>",yytext); //Generating token
				
				ttokens++; yylval.symbol=new SymbolInfo(yytext); yylval.symbol->setDval(atof(yytext));
				return CONST_FLOAT;
				}
\'\'		{
				fprintf(logOut,"\nError at line %d: Empty character literal %s\n",yylineno,yytext),terror++;
			}
\'(\n|[^'\n]*\n|\\\')	{ //Unfinished character literal like 'b or 'bbbbasd
							fprintf(logOut,"\nError at line %d.Unterminated character literal %s\n",yylineno,yytext),terror++;
						}


\'([^'\\\n][^'\n]+|\\[^'\n][^'\n]+)\'	{ //Multichracter constant like 'abc' '\nb' 'b\n'
											fprintf(logOut,"\nError at line %d. Multicharacter constant error for character sequence %s\n",yylineno,yytext),terror++;
										}

\'([^'\\\n]|\\['"\\a-zA-Z0])\'	{ //Finding character literal
				
									fprintf(logOut,"\n Line No. %d: Token <CONST_CHAR> Lexeme %s found\n",yylineno,yytext); //Adding to log file
									fprintf(tokenOut,"<CONST_CHAR,%c>",fixL(yytext)); //Generating token
									ttokens++;
									return CONST_CHAR;
								}


"++"|"--"	{
				fprintf(logOut,"\nLine No. %d: Token <INCOP> Lexeme %s found\n",yylineno,yytext);
				fprintf(tokenOut,"<INCOP,%s>",yytext),ttokens++;
				return INCOP;
			}
[+-]		{
				fprintf(logOut,"\nLine No. %d: Token <ADDOP> Lexeme %s found\n",yylineno,yytext);
				fprintf(tokenOut,"<ADDOP,%s>",yytext),ttokens++; yylval.symbol=new SymbolInfo(yytext);
				return ADDOP;
			}
[*/%]		{
				fprintf(logOut,"\nLine No. %d: Token <MULOP> Lexeme %s found\n",yylineno,yytext);
				fprintf(tokenOut,"<MULOP,%s>",yytext),ttokens++; yylval.symbol=new SymbolInfo(yytext);
				return MULOP;
			}

"<"|"<="|">"|">="|"=="|"!="	{
								fprintf(logOut,"\nLine No. %d: Token <RELOP> Lexeme %s found\n",yylineno,yytext);
								fprintf(tokenOut,"<RELOP,%s>",yytext),ttokens++; yylval.symbol=new SymbolInfo(yytext);
								return RELOP;
							}

=		{
			fprintf(logOut,"\nLine No. %d: Token <ASSIGNOP> Lexeme %s found\n",yylineno,yytext);
			fprintf(tokenOut,"<ASSIGNOP,%s>",yytext),ttokens++; yylval.symbol=new SymbolInfo(yytext);
			return ASSIGNOP;
		}
"&&"|"||"	{
				fprintf(logOut,"\nLine No. %d: Token <LOGICOP> Lexeme %s found\n",yylineno,yytext);
				fprintf(tokenOut,"<LOGICOP,%s>",yytext),ttokens++; yylval.symbol=new SymbolInfo(yytext);
				return LOGICOP;
			}
"&"|"|"|"^"|"<<"|">>"	{
							fprintf(logOut,"\nLine No. %d: Token <BITOP> Lexeme %s found\n",yylineno,yytext);
							fprintf(tokenOut,"<BITOP,%s>",yytext),ttokens++;
							return BITOP;
						}
"!"		{
			fprintf(logOut,"\nLine No. %d: Token <NOT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<NOT,!>");
			return NOT;
		}
"("		{
			fprintf(logOut,"\nLine No. %d: Token <LPAREN> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<LPAREN,(>"); yylval.symbol=new SymbolInfo(yytext);
			return LPAREN;
		}
")"		{
			fprintf(logOut,"\nLine No. %d: Token <RPAREN> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<RPAREN,)>"); yylval.symbol=new SymbolInfo(yytext);
			return RPAREN;
		}
"{"		{
			fprintf(logOut,"\nLine No. %d: Token <LCUR> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<LCUR,{>"); yylval.symbol=new SymbolInfo(yytext);
			return LCURL;
		}
"}"		{
			fprintf(logOut,"\nLine No. %d: Token <RCUR> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<RCUR,}>"); yylval.symbol=new SymbolInfo(yytext);
			return RCURL;
		}
"["		{
			fprintf(logOut,"\nLine No. %d: Token <LTHIRD> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<LTHIRD,[>");
			return LTHIRD;
		}
"]"		{
			fprintf(logOut,"\nLine No. %d: Token <RTHIRD> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<RTHIRD,]>");
			return RTHIRD;
		}
","		{
			fprintf(logOut,"\nLine No. %d: Token <COMMA> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<COMMA,,>");
			return COMMA;
		}
";"		{
			fprintf(logOut,"\nLine No. %d: Token <SEMICOLON> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			fprintf(tokenOut,"<SEMICOLON,;>"); yylval.symbol=new SymbolInfo(yytext);
			return SEMICOLON;
		}
{unfstr}	{//Unfinished String
				fprintf(logOut,"\nError at line %d. Missing terminating character %s\n",yylineno,yytext),terror++;
			}

{str}		{//String
				fprintf(logOut,"\nLine No. %d: Token <STRING> Lexeme %s found\n",yylineno,yytext); //Adding to log file
				fprintf(tokenOut,"<STRING, %s>",fixS(yytext)); yylval.str=yytext;
				return STRING;
			}
{slcom}		{//single or \
				multilined comment
				fprintf(logOut,"\nLine No. %d: Token <COMMENT> Lexeme %s found\n",yylineno,yytext); //Adding to log file
			}

{unfcom}	{ //Unfinished comment
				fprintf(logOut,"\nError at line %d. Unfinished comment %s\n",yylineno,yytext),terror++;
			}
{mlcom}		{ //Multilined comment
				fprintf(logOut,"\nToken <COMMENT> Lexeme %s found\n",yytext);
			}
{alphanumeric}	{
					fprintf(logOut,"\nLine No. %d: Token <ID> Lexeme %s found\n",yylineno,yytext); //Adding to log file
					fprintf(tokenOut,"<ID,%s>",yytext);
					yylval.symbol=new SymbolInfo(yytext);
					return ID;
				}
{wid}		{//Wrong identifier
		fprintf(logOut,"\nError at line %d. Invalid prefix on ID or invalid suffix on Number %s\n",yylineno,yytext),terror++;
		}
{ifn}		{//Ill formed number
		fprintf(logOut,"\nError at line %d. Ill formed Number %s\n",yylineno,yytext),terror++;
		}
{tmdp}		{//too many decimal points
		fprintf(logOut,"\nError at line %d. Too many decimal points for %s\n",yylineno,yytext),terror++;
		}
.		{
		fprintf(logOut,"\nError at line %d. unrecognized character %s\n",yylineno,yytext),terror++;
		}

%%

/*int main(int argc,char *argv[]){

	nothing to do here

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
	
	tokenOut=fopen("1505120_token.txt","wb");
	logOut=fopen("1505120_log.txt","w");
	
	yyin= fin;
	yylex();
	printf("total lines: %d\n",yylineno);
	printf("total errors: %d\n",terror);
	
	fprintf(logOut,"Total lines: %d\n",yylineno);
	fprintf(logOut,"Total errors: %d\n",terror);
	fclose(fin);
	fclose(tokenOut);
	fclose(logOut);

     	return 0;
}*/

/*int main(){
	yyin=fopen("input.txt","r");
	int i=0;
	while(1){
		yylex();
		printf("%d ",i);
		i++;
		if(i > 100000) break;
	}

	fclose(logOut);
	fclose(tokenOut);
	return 0;
}*/





