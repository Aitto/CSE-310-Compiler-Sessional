%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
//#include "symbol.h"
//#define YYSTYPE SymbolInfo*
#define YYDEBUG 1

using namespace std;

int yyparse(void);
int yylex(void);
extern char* yytext;
extern int yylineno;
extern FILE *yyin;
extern FILE *logOut,*tokenOut;
FILE *parseLog=NULL;

//SymbolTable *table;


void yyerror(char *s)
{
	//write your code
	cout<<s<< " at line: "<<yylineno<<endl;
}


%}

%token IF ELSE FOR WHILE DO INT FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE BREAK CONST_INT CONST_FLOAT CONST_CHAR ID
%token ADDOP DECOP MULOP INCOP RELOP ASSIGNOP LOGICOP BITOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token STRING PRINTLN NEWLINE


%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

start : program
	{
		//write your code in this block in all the similar blocks below
	}
	;

program : program unit	{ fprintf(parseLog, "At line no : %d program : program unit \n",yylineno ); }
	| unit				{ fprintf(parseLog, "At line no : %d program : unit \n",yylineno ); }
	;
	
unit : var_declaration	{ fprintf(parseLog, "At line no : %d unit : var_declaration \n",yylineno ); }
     | func_declaration	{ fprintf(parseLog, "At line no : %d unit : func_declaration \n",yylineno ); }
     | func_definition	{ fprintf(parseLog, "At line no : %d unit : func_definition \n",yylineno ); }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON	{ fprintf(parseLog, "At line no : %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON \n",yylineno ); }
		| type_specifier ID LPAREN RPAREN SEMICOLON	{ fprintf(parseLog, "At line no : %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON \n",yylineno ); }
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement	{ fprintf(parseLog, "At line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement \n",yylineno ); }
		| type_specifier ID LPAREN RPAREN compound_statement	{ fprintf(parseLog, "At line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement \n",yylineno ); }
 		;				


parameter_list  : parameter_list COMMA type_specifier ID	{ fprintf(parseLog, "At line no : %d parameter_list : parameter_list COMMA type_specifier ID \n",yylineno ); }
		| parameter_list COMMA type_specifier				{ fprintf(parseLog, "At line no : %d parameter_list : parameter_list COMMA type_specifier \n",yylineno ); }
 		| type_specifier ID	{ fprintf(parseLog, "At line no : %d parameter_list : type_specifier ID \n",yylineno ); }
		| type_specifier	{ fprintf(parseLog, "At line no : %d parameter_list : type_specifier \n",yylineno ); }
 		;

 		
compound_statement : LCURL statements RCURL	{ fprintf(parseLog, "At line no : %d compound_statement : LCURL statements RCURL \n",yylineno ); }
 		    | LCURL RCURL	{ fprintf(parseLog, "At line no : %d compound_statement : LCURL RCURL \n",yylineno ); }
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON { fprintf(parseLog, "At line no : %d var_declaration : type_specifier declaration_list SEMICOLON \n",yylineno ); }
 		 ;
 		 
type_specifier	: INT	{ fprintf(parseLog, "At line no : %d type_specifier : INT \n",yylineno ); }
 		| FLOAT			{ fprintf(parseLog, "At line no : %d type_specifier : FLOAT \n",yylineno ); }
 		| VOID			{ fprintf(parseLog, "At line no : %d type_specifier : VOID \n",yylineno ); }
 		;
 		
declaration_list : declaration_list COMMA ID	{ fprintf(parseLog, "At line no : %d declaration_list : declaration_list COMMA ID \n",yylineno ); }
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{ fprintf(parseLog, "At line no : %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD \n",yylineno ); }
 		  | ID		{ fprintf(parseLog, "At line no : %d declaration_list : ID \n",yylineno ); }
 		  | ID LTHIRD CONST_INT RTHIRD	{ fprintf(parseLog, "At line no : %d declaration_list : ID LTHIRD CONST_INT RTHIRD \n",yylineno ); }
 		  ;
 		  
statements : statement			{ fprintf(parseLog, "At line no : %d statements : statement \n",yylineno ); }
	   | statements statement	{ fprintf(parseLog, "At line no : %d statements : statements statement \n",yylineno ); }
	   ;
	   
statement : var_declaration		{ fprintf(parseLog, "At line no : %d statement : var_declaration \n",yylineno ); }
	  | expression_statement	{ fprintf(parseLog, "At line no : %d statement : expression_statement \n",yylineno ); }
	  | compound_statement		{ fprintf(parseLog, "At line no : %d statement : compound_statement \n",yylineno ); }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement	{ fprintf(parseLog, "At line no : %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement \n",yylineno ); }
	  | IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE	{ fprintf(parseLog, "At line no : %d statement : IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE \n",yylineno ); }
	  | IF LPAREN expression RPAREN statement ELSE statement		{ fprintf(parseLog, "At line no : %d statement : IF LPAREN expression RPAREN statement ELSE statement \n",yylineno ); }
	  | WHILE LPAREN expression RPAREN statement	{ fprintf(parseLog, "At line no : %d statement : WHILE LPAREN expression RPAREN statement \n",yylineno ); }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON			{ fprintf(parseLog, "At line no : %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON \n",yylineno ); }
	  | RETURN expression SEMICOLON					{ fprintf(parseLog, "At line no : %d statement : RETURN expression SEMICOLON \n",yylineno ); }
	  ;
	  
expression_statement : SEMICOLON	{ fprintf(parseLog, "At line no : %d expression_statement : SEMICOLON \n",yylineno ); }
			| expression SEMICOLON	{ fprintf(parseLog, "At line no : %d expression_statement : expression SEMICOLON \n",yylineno ); }
			;
	  
variable : ID 						{ fprintf(parseLog, "At line no : %d variable : ID \n",yylineno ); }	
	 | ID LTHIRD expression RTHIRD 	{ fprintf(parseLog, "At line no : %d variable : ID LTHIRD expression RTHIRD \n",yylineno ); }
	 ;
	 
expression : logic_expression				{ fprintf(parseLog, "At line no : %d expression : logic_expression \n",yylineno ); }
	   | variable ASSIGNOP logic_expression	{ fprintf(parseLog, "At line no : %d expression : variable ASSIGNOP logic_expression \n",yylineno ); }
	   ;
			
logic_expression : rel_expression 	{ fprintf(parseLog, "At line no : %d logic_expression : rel_expression \n",yylineno ); }
		 | rel_expression LOGICOP rel_expression 	{ fprintf(parseLog, "At line no : %d logic_expression : rel_expression LOGICOP rel_expression \n",yylineno ); }
		 ;
			
rel_expression	: simple_expression		{ fprintf(parseLog, "At line no : %d rel_expression : simple_expression \n",yylineno ); }
		| simple_expression RELOP simple_expression	{ fprintf(parseLog, "At line no : %d rel_expression : simple_expression RELOP simple_expression \n",yylineno ); }
		;
				
simple_expression : term	{ fprintf(parseLog, "At line no : %d simple_expression : term \n",yylineno ); }
		  | simple_expression ADDOP term 	{ fprintf(parseLog, "At line no : %d simple_expression : simple_expression ADDOP term \n",yylineno ); }
		  ;
					
term :	unary_expression { fprintf(parseLog, "At line no : %d term : unary_expression \n",yylineno ); }
     |  term MULOP unary_expression	{ fprintf(parseLog, "At line no : %d term : term MULOP unary_expression \n",yylineno ); }
     ;

unary_expression : ADDOP unary_expression	{ fprintf(parseLog, "At line no : %d unary_expression : ADDOP unary_expression \n",yylineno ); }
		 | NOT unary_expression 			{ fprintf(parseLog, "At line no : %d unary_expression : NOT unary_expression \n",yylineno ); }
		 | factor 							{ fprintf(parseLog, "At line no : %d unary_expression : factor \n",yylineno ); }
		 ;
	
factor	: variable		{ fprintf(parseLog, "At line no : %d factor : variable \n",yylineno ); }
	| ID LPAREN argument_list RPAREN	{ fprintf(parseLog, "At line no : %d factor : ID LPAREN argument_list RPAREN \n",yylineno ); }
	| LPAREN expression RPAREN			{ fprintf(parseLog, "At line no : %d factor : LPAREN expression RPAREN \n",yylineno ); }
	| CONST_INT			{ fprintf(parseLog, "At line no : %d factor : CONST_INT DECOP \n",yylineno ); }
	| CONST_FLOAT		{ fprintf(parseLog, "At line no : %d factor : CONST_FLOAT \n",yylineno ); }
	| variable INCOP	{ fprintf(parseLog, "At line no : %d factor : variable INCOP \n",yylineno ); }
	| variable DECOP	{ fprintf(parseLog, "At line no : %d factor : variable DECOP \n",yylineno ); }
	;
	
argument_list : arguments	{ fprintf(parseLog, "At line no : %d argument_list : arguments\n",yylineno ); }
			  |
			  ;
	
arguments : arguments COMMA logic_expression	{ fprintf(parseLog, "At line no : %d arguments : arguments COMMA logic_expression\n",yylineno ); }
	      | logic_expression	{
			  fprintf(parseLog, "At line no : %d arguments : logic_expression\n",yylineno );
		  	  fprintf(parseLog,"\n%s\n",yytext); 
			}
	      ;
 

%%
int main(int argc,char *argv[])
{
	int yydebug=1;

	/*if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	fp2= fopen(argv[2],"w");
	fclose(fp2);
	fp3= fopen(argv[3],"w");
	fclose(fp3);
	
	fp2= fopen(argv[2],"a");
	fp3= fopen(argv[3],"a");
	

	yyin=fp;*/
	FILE *input=fopen("input.txt","r");
	yyin=input;

	parseLog=fopen("log.txt","w");
	if(parseLog==NULL or input==NULL){
		printf("Error. Unable to open file\n");
		exit(1);
	}

	int i=0;

	yyparse();
	//printf("%d",i);
	
	fclose(parseLog);
	fclose(input);

	

	fclose(logOut);
	fclose(tokenOut);
	//fclose(fp2);
	//fclose(fp3);
	
	return 0;
}

