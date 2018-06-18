%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "symbolMain.cpp"

//#define YYDEBUG 1

using namespace std;

int yyparse(void);
int yylex(void);

string typeSp;
string vType;
string rType;
string par[10];
string parType[10];

char * undecvar= "\nError at line: %d. Undeclared variable %s\n";
char * muldec= "\nError at line: %d. Multipe declaration of %s\n";
char * nonIn= "\nError at line: %d. Not-Integer Array Index used\n";
char * nonArr="\nError at line: %d. Not an Array\n";
char * arrIn="\nError at line: %d. Trying to access array like normal variable!\n";
char * typemm= "\nError at line: %d. Type mismatched\n";
char * undecfunc="\nError at line: %d. Undeclared function %s\n";
char * moderror="\nError at ine: %d. Both operands on modulus should be Integer\n";
char * voidcall="\nError at line: %d. Can't call Void function for assignment or expression\n";

bool c;

int parNum=0;
int tperror=0;

SymbolInfo * symbolInfo;

extern char* yytext;
extern int yylineno;
extern FILE *yyin;
extern FILE *logOut,*tokenOut;
extern int terror;

void yyerror(char *s,string t=".")
{
	if(t!=".") fprintf(parseError,s,yylineno,t.c_str());
	else fprintf(parseError,s,yylineno);

	tperror++;

	//cout<<s<< " at line: "<<yylineno<<endl;
}

void addToTable(){
	for(int i=0;i<parNum;i++){
		manage('I',par[i],parType[i]);
		symbolInfo=getSymbol(par[i]);
		symbolInfo->var_type=parType[i];
	}
}

void initVtype(){
	vType="none";
}

void initRtype(){
	rType="none";
}

%}

%union{
	SymbolInfo *symbol;
	char *str;
	int ival;
	float *dval;
}

%token DO SWITCH CASE DEFAULT CONTINUE BREAK  
%token DECOP INCOP BITOP NOT LTHIRD RTHIRD COMMA
%token STRING PRINTLN NEWLINE RETURN

%token<symbol> ID INT FLOAT DOUBLE VOID CONST_CHAR CONST_FLOAT CONST_INT ADDOP MULOP RELOP LOGICOP ASSIGNOP 
%token<symbol> SEMICOLON LCURL RCURL LPAREN RPAREN IF FOR WHILE

%type<symbol> declaration_list type_specifier var_declaration unit program parameter_list func_declaration func_definition
%type<symbol> variable expression factor unary_expression term simple_expression rel_expression logic_expression
%type<symbol> statement statements compound_statement expression_statement arguments argument_list

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%

start : program
	{
		//write your code in this block in all the similar blocks below
		manage('P',"...");
	}
	;

program : program unit	{
		fprintf(parseLog, "\nAt line no : %d program : program unit\n\n",yylineno );
		$$->setName($1->getName()+"\n"+$2->getName());
		fprintf(parseLog,"\n%s\n",$1->getName().c_str());
		}
	| unit				{
		fprintf(parseLog, "\nAt line no : %d program : unit\n\n",yylineno );
		fprintf(parseLog,"%s\n",$1->getName().c_str());
		}
	;
	
unit : var_declaration	{
			fprintf(parseLog, "\nAt line no : %d unit : var_declaration\n\n",yylineno );
			fprintf(parseLog,"%s\n",$1->getName().c_str());
			}
     | func_declaration	{
		 	fprintf(parseLog, "\nAt line no : %d unit : func_declaration\n\n",yylineno );
			 fprintf(parseLog,"%s\n",$1->getName().c_str());
			 }
     | func_definition	{
		 	fprintf(parseLog, "\nAt line no : %d unit : func_definition\n\n",yylineno );
			 fprintf(parseLog,"%s\n",$1->getName().c_str());
			 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON	{
				fprintf(parseLog, "\nAt line no : %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n",yylineno );
				$$->setName($1->getName()+" "+$2->getName()+"("+$4->getName()+");" );
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
		| type_specifier ID LPAREN RPAREN SEMICOLON	{
				fprintf(parseLog, "\nAt line no : %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n",yylineno );
				$$->setName($1->getName()+" "+$2->getName() + "();");
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement	{
				manage('I',$2->getName(),"foo"); symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
					symbolInfo->ret_type=$1->getName();
				}
				fprintf(parseLog, "\nAt line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n",yylineno );
				$$->setName($1->getName()+" "+$2->getName()+"("+$4->getName()+")"+$6->getName() );
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
		| type_specifier ID LPAREN RPAREN compound_statement	{
				manage('I',$2->getName(),"foo"); symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
					symbolInfo->ret_type=$1->getName();
				}
				fprintf(parseLog, "\nAt line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n",yylineno );
				$$->setName($1->getName()+ " "+ $2->getName()+ "( )"+$5->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
 		;				

parameter_list  : parameter_list COMMA type_specifier ID	{
				par[parNum]=$4->getName(); parType[parNum]=$3->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : parameter_list COMMA type_specifier ID\n\n",yylineno );
				$$->setName($1->getName()+","+$3->getName()+" "+$4->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
		| parameter_list COMMA type_specifier				{
				fprintf(parseLog, "\nAt line no : %d parameter_list : parameter_list COMMA type_specifier\n\n",yylineno );
				$$->setName($1->getName()+","+$3->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
 		| type_specifier ID	{
			 	par[parNum]=$2->getName(); parType[parNum]=$1->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : type_specifier ID\n\n",yylineno );
				$$->setName($1->getName()+" "+$2->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
		| type_specifier	{
				fprintf(parseLog, "\nAt line no : %d parameter_list : type_specifier\n\n",yylineno );
				$$->setName($1->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
 		;

 		
compound_statement : LCURL {manage('S',"..."); addToTable(); } statements RCURL	{
					parNum=0; fprintf(parseLog, "\nAt line no : %d compound_statement : LCURL statements RCURL\n\n",yylineno );
					$$->setName("{\n"+$3->getName()+"}\n");
					fprintf(parseLog,"%s\n",$$->getName().c_str());
					manage('E',"...");
					}
 		    | LCURL {manage('S',"..."); addToTable();} RCURL	{ parNum=0;
			 		fprintf(parseLog, "\nAt line no : %d compound_statement : LCURL RCURL\n\n",yylineno );
					$$->setName("{\n}\n");
					fprintf(parseLog,"{\n}\n");
					manage('E',"...");
					}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON {
					
					if(vType=="void") yyerror("\nError at line  %d. Variable type Cannot be Void\n"),initVtype;

					fprintf(parseLog, "\nAt line no : %d var_declaration : type_specifier declaration_list SEMICOLON\n\n",yylineno );
					$$->setName($1->getName()+ " "+$2->getName() + ";");
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
 		 ;
 		 
type_specifier	: INT	{
					vType="int"; rType="int";
					fprintf(parseLog, "\nAt line no : %d type_specifier : INT\n\n",yylineno );
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					} 
 		| FLOAT			{
					vType="float"; rType="float";
					fprintf(parseLog, "\nAt line no : %d type_specifier : FLOAT\n\n",yylineno );
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					} 
 		| VOID			{
					vType="void"; rType="void";
					fprintf(parseLog, "\nAt line no : %d type_specifier : VOID\n\n",yylineno );
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					} 
 		;
 		
declaration_list : declaration_list COMMA ID	{
						c=manage('I',$3->getName(),"ID"); if(!c) yyerror(muldec,$3->getName()); else{
						symbolInfo=getSymbol($3->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
						}}
						fprintf(parseLog, "\nAt line no : %d declaration_list : declaration_list COMMA ID\n\n",yylineno );
						$$->setName($1->getName()+ "," + $3->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str()); 
						}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
			   			c=manage('I',$3->getName()+ "[]" ,"ID"); if(!c) yyerror(muldec, $3->getName()); else {
						symbolInfo=getSymbol($3->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->ret_type="array";
						}}
						fprintf(parseLog, "\nAt line no : %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n",yylineno );
						$$->setName($1->getName()+"," + $3->getName()+"["+$5->getName()+"]");
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
 		  | ID							{
			   			c=manage('I',$1->getName(),"ID"); if(!c) yyerror(muldec,$1->getName()); else {
						symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
						}}
						fprintf(parseLog, "\nAt line no : %d declaration_list : ID\n\n",yylineno );
						$$->setName($1->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str()); 
						}
 		  | ID LTHIRD CONST_INT RTHIRD	{
			   			c=manage('I',$1->getName()+"[]","ID"); if(!c) yyerror(muldec,$1->getName()); else {
						symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->ret_type="array";
						}}
						fprintf(parseLog, "\nAt line no : %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n",yylineno );
						$$->setName($1->getName()+"["+$3->getName()+"]");
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
 		  ;
 		  
statements : statement			{
					fprintf(parseLog, "\nAt line no : %d statements : statement\n\n",yylineno );
					$$->setName($1->getName());
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	   | statements statement	{
		   			fprintf(parseLog, "\nAt line no : %d statements : statements statement\n\n",yylineno );
					$$->setName($1->getName()+"\n"+$2->getName());
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	   ;
	   
statement : var_declaration		{
						fprintf(parseLog, "\nAt line no : %d statement : var_declaration\n\n",yylineno );
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | expression_statement	{
		  				fprintf(parseLog, "\nAt line no : %d statement : expression_statement\n\n",yylineno );
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | compound_statement		{
		  				fprintf(parseLog, "\nAt line no : %d statement : compound_statement\n\n",yylineno );
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement	{
		  				fprintf(parseLog, "\nAt line no : %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n",yylineno );
						$$->setName("for("+$3->getName()+$4->getName()+$5->getName()+")"+$7->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE	{
		  				fprintf(parseLog, "\nAt line no : %d statement : IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE\n\n",yylineno );
						$$->setName("if("+$3->getName()+")"+$5->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | IF LPAREN expression RPAREN statement ELSE statement		{
		  				fprintf(parseLog, "\nAt line no : %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n",yylineno );
						$$->setName("if("+$3->getName()+")"+$5->getName()+" else "+$7->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | WHILE LPAREN expression RPAREN statement	{
		  				fprintf(parseLog, "\nAt line no : %d statement : WHILE LPAREN expression RPAREN statement\n\n",yylineno );
						$$->setName("while("+$3->getName()+")"+$5->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON			{
		  				fprintf(parseLog, "\nAt line no : %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n",yylineno );
						}
	  | RETURN expression SEMICOLON					{
		  				/*if(rType!=vType) fprintf(parseError,"\nError at line %d Function return type not matched!\n",yylineno);*/
						fprintf(parseLog, "\nAt line no : %d statement : RETURN expression SEMICOLON\n\n",yylineno );
						$$->setName("return " +$2->getName()+";"); 
						fprintf(parseLog,"return %s ;\n",$2->getName().c_str());
						}
	  ;
	  
expression_statement : SEMICOLON	{ 
					fprintf(parseLog, "\nAt line no : %d expression_statement : SEMICOLON\n\n",yylineno );
					$$->setName(";\n"); fprintf(parseLog,";\n"); 
					}
			| expression SEMICOLON	{ 
					fprintf(parseLog, "\nAt line no : %d expression_statement : expression SEMICOLON\n\n",yylineno ); 
					$$->setName($1->getName()+";"); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
			;
	  
variable : ID 			{ 
				c=manage('L',$1->getName()); if(!c) yyerror(undecvar,$1->getName());
				
				symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0) {
					if(symbolInfo->ret_type=="array") yyerror(arrIn,$1->getName());
					$$->var_type=symbolInfo->var_type;
				}

				fprintf(parseLog, "\nAt line no : %d variable : ID\n\n",yylineno );
				$$->setName($1->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}	
	 | ID LTHIRD expression RTHIRD 	{
		 		if($3->var_type=="void") yyerror(voidcall);
		 		else if($3->var_type!="int") yyerror(nonIn);
				
				symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0) {
					if(symbolInfo->ret_type!="array") yyerror(nonArr,$1->getName());
					$$->var_type=symbolInfo->var_type;
				}

				c=manage('L',$1->getName()); if(!c) yyerror(undecvar,$1->getName());
				fprintf(parseLog, "\nAt line no : %d variable : ID LTHIRD expression RTHIRD\n\n",yylineno ); 
				$$->setName($1->getName()+"["+$3->getName()+"]"); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	 ;

expression : logic_expression				{ 
					fprintf(parseLog, "\nAt line no : %d expression : logic_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
	   | variable ASSIGNOP logic_expression	{

					if($3->var_type=="void") yyerror(voidcall);
					else if($1->var_type!=$3->var_type) yyerror(typemm);
					
		   			fprintf(parseLog, "\nAt line no : %d expression : variable ASSIGNOP logic_expression\n\n",yylineno ); 
					$$->setName($1->getName()+"="+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
	   ;
			
logic_expression : rel_expression 	{ 
					fprintf(parseLog, "\nAt line no : %d logic_expression : rel_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 | rel_expression LOGICOP rel_expression 	{
			 		$$->var_type="int";  
			 		fprintf(parseLog, "\nAt line no : %d logic_expression : rel_expression LOGICOP rel_expression\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 ;
			
rel_expression	: simple_expression		{ 
					fprintf(parseLog, "\nAt line no : %d rel_expression : simple_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		| simple_expression RELOP simple_expression	{ /* Relational Opertator type is Integer */
					$$->var_type="int"; 
					fprintf(parseLog, "\nAt line no : %d rel_expression : simple_expression RELOP simple_expression\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		;
				
simple_expression : term	{ 
					fprintf(parseLog, "\nAt line no : %d simple_expression : term\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		  | simple_expression ADDOP term 	{
			  		if($1->var_type=="float" || $3->var_type=="float") $$->var_type="float";
					else $$->var_type="int";
			  		fprintf(parseLog, "\nAt line no : %d simple_expression : simple_expression ADDOP term\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		  ;
					
term :	unary_expression { 
				fprintf(parseLog, "\nAt line no : %d term : unary_expression\n\n",yylineno ); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
     |  term MULOP unary_expression	{
		 		if($2->getName()!="%"){
					if($1->var_type=="float" || $3->var_type=="float") $$->var_type="float";
					else $$->var_type="int";
				}else {
					if($1->var_type!="int" || $3->var_type!="int"){
						yyerror(moderror);
					}else $$->var_type="int";
				}
		 		
		 		fprintf(parseLog, "\nAt line no : %d term : term MULOP unary_expression\n\n",yylineno ); 
				$$->setName($1->getName()+$2->getName()+$3->getName()); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
     ;

unary_expression : ADDOP unary_expression	{
					$$->var_type=$2->var_type; 
					fprintf(parseLog, "\nAt line no : %d unary_expression : ADDOP unary_expression\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 | NOT unary_expression 			{
			 		$$->var_type="int";
			 		fprintf(parseLog, "\nAt line no : %d unary_expression : NOT unary_expression\n\n",yylineno ); 
					$$->setName("!"+$2->getName()); 
					fprintf(parseLog,"%s\n",("!"+$2->getName()).c_str()); 
					}
		 | factor 							{
			 		fprintf(parseLog, "\nAt line no : %d unary_expression : factor\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 ;
	
factor	: variable		{ 
				fprintf(parseLog, "\nAt line no : %d factor : variable\n\n",yylineno ); 
				$$->setName($1->getName()); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| ID LPAREN argument_list RPAREN	{ /* Function Call */
				symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0) $$->var_type=symbolInfo->ret_type; else{
					yyerror(undecfunc,$1->getName());
				}
				fprintf(parseLog, "\nAt line no : %d factor : ID LPAREN argument_list RPAREN\n\n",yylineno ); 
				$$->setName($1->getName()+"("+$3->getName() +")" ); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| LPAREN expression RPAREN			{
				$$->var_type=$2->var_type;
				fprintf(parseLog, "\nAt line no : %d factor : LPAREN expression RPAREN\n\n",yylineno ); 
				$$->setName("("+$2->getName()+")"); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| CONST_INT			{ 
				vType="int"; $$->var_type="int";
				fprintf(parseLog, "\nAt line no : %d factor : CONST_INT\n\n",yylineno ); 
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
	| CONST_FLOAT		{ 
				vType="float"; $$->var_type="float";
				fprintf(parseLog, "\nAt line no : %d factor : CONST_FLOAT\n\n",yylineno );
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| variable INCOP	{
				$$->var_type=$1->var_type;
				fprintf(parseLog, "\nAt line no : %d factor : variable INCOP\n\n",yylineno ); 
				$$->setName($1->getName() + "++"); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| variable DECOP	{
				$$->var_type=$1->var_type;
				fprintf(parseLog, "\nAt line no : %d factor : variable DECOP\n\n",yylineno ); 
				$$->setName($1->getName() + "--"); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	;
	
argument_list : arguments	{ 
					fprintf(parseLog, "\nAt line no : %d argument_list : arguments\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
			  | 	{$$=new SymbolInfo();}
			  ;
	
arguments : arguments COMMA logic_expression	{ 
					fprintf(parseLog, "\nAt line no : %d arguments : arguments COMMA logic_expression\n\n",yylineno ); 
					$$->setName($1->getName()+","+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	      | logic_expression	{
					fprintf(parseLog, "\nAt line no : %d arguments : logic_expression\n\n",yylineno );
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	      ;
 

%%
int main(int argc,char *argv[])
{
	

	int yydebug=1;

	
	FILE *input=fopen("input.txt","r");
	yyin=input;

	parseLog=fopen("log.txt","w");
	parseError=fopen("error.txt","w");
	if(parseLog==NULL or input==NULL or parseError==NULL){
		printf("Error. Unable to open file\n");
		exit(1);
	}

	yyparse();
	

	fprintf(parseLog,"\n\ttotal lines: %d\n\n",yylineno);
	fprintf(parseError,"\ntotal errors: %d",tperror);
	
	fclose(parseLog);
	fclose(parseError);
	fclose(input);
	
	fprintf(logOut,"\nTotal errors: %d",terror);
	fclose(logOut);
	fclose(tokenOut);
	//fclose(fp2);
	//fclose(fp3);
	
	return 0;
}

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