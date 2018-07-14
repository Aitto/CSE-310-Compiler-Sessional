%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "symbolMain.cpp"
#include "vars.h"
#include<vector>
#include<utility>


//#define YYDEBUG 1

using namespace std;

void initParNum();

int yyparse(void);
int yylex(void);
FILE *gCode=NULL;

string typeSp;
string vType;
string rType="none";
string par[10];
string parType[10];
string argType[10];


char * undecvar= "\nError at line: %d. Undeclared variable %s\n";
char * muldec= "\nError at line: %d. Multipe declaration of %s\n";
char * nonIn= "\nError at line: %d. Not-Integer Array Index used\n";
char * nonArr="\nError at line: %d. %s not an Array\n";
char * arrIn="\nError at line: %d. Trying to access array like normal variable!\n";
char * typemm= "\nError at line: %d. Type mismatched\n";
char * undecfunc="\nError at line: %d. Undeclared function %s\n";
char * moderror="\nError at ine: %d. Both operands on modulus should be Integer\n";
char * voidcall="\nError at line: %d. Can't call Void function for assignment or expression\n";

bool c;

int parNum=0;
int argNum=0;
int tperror=0;

SymbolInfo * symbolInfo;

extern char* yytext;
extern int yylineno;
extern FILE *yyin;
extern FILE *logOut,*tokenOut;
extern int terror;

void yyerror(char *s,string t)
{
	fprintf(parseError,s,yylineno,t.c_str());
	//else fprintf(parseError,s,yylineno);

	tperror++;
}

void yyerror(const char *s){
	fprintf(parseError,s,yylineno);
	tperror++;
}

void addToTable(){
	for(int i=0;i<parNum;i++){
		if(par[i]!=" "){
		manage('I',par[i],"ID");
		symbolInfo=getSymbol(par[i]);
		symbolInfo->var_type=parType[i];
		}
	}
}

void addToSymbol(SymbolInfo *s){
	if(s!=0) s->parSet(parType,parNum);
}

bool matchPL(string s1[], string s2[],int num){
	bool ans=true;
	for(int i=0;i<num;i++){
		if(s1[i]!=s2[i]){
			ans=false;
			break;
		}
	}
	return ans;
}

void initVtype(){
	vType="none";
}

void initRtype(){
	rType="none";
}

void initSymbol(){
	symbolInfo=0;
}

void initParNum(){
	parNum=0;
}

/**
	Variables for Intermediate code generation.
	string code contains corresponding code segment
	and string data contains corresponding code for data segment
	addToCode() --> Adds code to the code segment
	addTo
*/
string init=".model small\n.stack 100h\n";
string inStack="\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";
string outStack="\tpop ax\n\tpop bx\n\tpop cx\n\tpop dx\n";
string codeSegment=".code\n";
string dataSegment=".data\n";
vector<string> variables;
vector<pair<string,int>> avariables;
bool global=true;
string fname=" ";
int labelCount=0;
int tempCount=0;

void addCode(string s){
	codeSegment+=s;
}

void addData(string s){
	dataSegment+=s;
}

void addVars(string name,int num,bool array=false){
	if(array){
		if(!global) avariables.push_back(make_pair(fname+ name,num));
		else avariables.push_back(make_pair(name,num));
	}
	else for(int i=0;i<num;i++){
		if(!global) variables.push_back(name + par[i]);
		else variables.push_back(par[i]);
	}
}


char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	variables.push_back(string(t));
	return t;
}


%}

%union{
	SymbolInfo *symbol;
	char *str;
	int ival;
	float *dval;
}

%error-verbose

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
		//Initialize assembly
		//if(tperror==0 || tperror!=0){
			fprintf(gCode,(init+"\n.data\n").c_str());
			for(vector<string>::iterator it=variables.begin();it!=variables.end();it++){
				fprintf(gCode,("\t"+*it + " dw ?\n").c_str() );
			}
			for(int i=0;i<avariables.size();i++){
				fprintf(gCode,("\t"+avariables[i].first+ " dw %d dup (?)\n").c_str(),avariables[i].second );
			}
			fprintf(gCode,(printInit+".code\n"+pDec+ $1->code+"\nend main").c_str());
			
		//}
	}
	;

program : program unit	{
		$$=$1;
		$$->code=$1->code+$2->code;

		fprintf(parseLog, "\nAt line no : %d program : program unit\n\n",yylineno );
		$$->setName($1->getName()+"\n"+$2->getName());
		fprintf(parseLog,"\n%s\n",$1->getName().c_str());
		global=true;
		}
	| unit				{

		$$=$1;

		fprintf(parseLog, "\nAt line no : %d program : unit\n\n",yylineno );
		fprintf(parseLog,"%s\n",$1->getName().c_str());
		global=true;
		}
	;
	
unit : var_declaration	{
			$$=$1;
			fprintf(parseLog, "\nAt line no : %d unit : var_declaration\n\n",yylineno );
			fprintf(parseLog,"%s\n",$1->getName().c_str());
			}
     | func_declaration	{
		 	$$=$1;
		 	fprintf(parseLog, "\nAt line no : %d unit : func_declaration\n\n",yylineno );
			 fprintf(parseLog,"%s\n",$1->getName().c_str());
			 }
     | func_definition	{
		 	$$=$1;
		 	fprintf(parseLog, "\nAt line no : %d unit : func_definition\n\n",yylineno );
			 fprintf(parseLog,"%s\n",$1->getName().c_str());
			 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON	{

				c=manage('I',$2->getName(),"foo"); symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
					if(symbolInfo->func_declared || symbolInfo->func_defined){
						yyerror("\nWarning. At line : %d. %s Declared multiple times\n",$2->getName());
					}else{
						symbolInfo->func_declared=true;
						symbolInfo->ret_type=$1->getName();
						symbolInfo->parNum=parNum;
						addToSymbol(symbolInfo);
						
					}

				} initParNum();
				
				fprintf(parseLog, "\nAt line no : %d func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n",yylineno );
				$$->setName($1->getName()+" "+$2->getName()+"("+$4->getName()+");" );
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
		| type_specifier ID LPAREN RPAREN SEMICOLON	{
				c=manage('I',$2->getName(),"foo"); symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
					

					if(symbolInfo->func_declared || symbolInfo->func_defined){
						yyerror("\nWarning. At line : %d. %s Declared multiple times\n",$2->getName());
					}else{
						symbolInfo->func_declared=true;
						symbolInfo->ret_type=$1->getName();
						symbolInfo->parNum=0;
					}

				} initParNum();
				fprintf(parseLog, "\nAt line no : %d func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n",yylineno );
				$$->setName($1->getName()+" "+$2->getName() + "();");
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {
				
				global=false;
				fname=$2->getName();
				
				c=manage('I',$2->getName(),"foo"); if(!c){

					addVars($2->getName(),parNum);

					symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
						if(symbolInfo->func_defined){
							yyerror(muldec,$2->getName());
						}else {
							symbolInfo->func_defined=true;
							if(symbolInfo->func_declared){
								if(parNum!=symbolInfo->parNum){
									yyerror("\nError at line : %d. Parameter Number of %s doesn't match\n",$2->getName());
								}else if(!matchPL(symbolInfo->parTList,parType,parNum)){
									yyerror("Error at line : %d. Parameter types doesn't match!\n");
								}
								
							}else {

								//actually they'll never come in this stage
								
								symbolInfo->ret_type=$1->getName();
								symbolInfo->parNum=parNum;
								addToSymbol(symbolInfo);
								
							}
						}
					}
				}else{
					symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
					
					symbolInfo->ret_type=$1->getName();
					symbolInfo->parNum=parNum;
					
					addVars($2->getName(),parNum);

					addToSymbol(symbolInfo);
					symbolInfo->func_defined=true;
					}
				} 
				} compound_statement	{
				
				
				if($2->getName()=="main"){
					$$->code=$2->getName() + " proc\n";
					$$->code+="\tmov ax,@data\n\tmov ds,ax\n";
					$$->code+=$7->code;
					$$->code+="\tmov ah,4ch\n\tint 21h\nmain endp\n" ;
				}else{
					$$->code=$2->getName() + " proc\n" +inStack;
					$$->code+=$7->code;
					$$->code+=outStack + "ret\n" + $2->getName()+ " endp\n" ;
				}

				if($1->getName()!=rType){
						yyerror("\nError at line : %d. Return type doesn't match\n");
						//cout<<$1->getName()<< " "<<rType<<endl;
						rType="none";
				}

				fprintf(parseLog, "\nAt line no : %d func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n",yylineno );
				$$->setName($1->getName()+" "+$2->getName()+"("+$4->getName()+")"+$7->getName() );
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
		| type_specifier ID LPAREN RPAREN {
				
				global=false;
				fname=$2->getName();

				c=manage('I',$2->getName(),"foo"); if(!c){
					symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
						if(symbolInfo->func_defined){
							yyerror(muldec,$2->getName());
						}else {
							symbolInfo->func_defined=true;
							if(symbolInfo->func_declared){
								if(parNum!=symbolInfo->parNum){
									yyerror("\nError at line : %d. Parameter Number of %s doesn't match\n",$2->getName());
									cout<<parNum<< " "<<symbolInfo->parNum<<endl;
								}
								
							}else {
								
								symbolInfo->ret_type=$1->getName();
								symbolInfo->parNum=0;
							}
						}
					}
				}else{
					symbolInfo=getSymbol($2->getName()); if(symbolInfo!=0){
					
					symbolInfo->ret_type=$1->getName();
					symbolInfo->func_defined=true;
					symbolInfo->parNum=0;
					}
				}
				} compound_statement	{
				
				
				if($2->getName()=="main"){
					$$->code=$2->getName() + " proc\n";
					$$->code+="\tmov ax,@data\n\tmov ds,ax\n";
					$$->code+=$6->code;
					$$->code+="\tmov ah,4ch\n\tint 21h\nmain endp\n" ;
				}else{
					$$->code=$2->getName() + " proc\n" +inStack;
					$$->code+=$6->code;
					$$->code+=outStack + "ret\n" + $2->getName()+ " endp\n" ;
				}

				if($1->getName()!=rType){
						yyerror("\nError at line : %d. Return type doesn't match\n");
						rType="none";
				}
				fprintf(parseLog, "\nAt line no : %d func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n",yylineno );
				$$->setName($1->getName()+ " "+ $2->getName()+ "( )"+$6->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
 		;				

parameter_list  : parameter_list COMMA type_specifier ID	{
				$$=$1;
				par[parNum]=$4->getName(); parType[parNum]=$3->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : parameter_list COMMA type_specifier ID\n\n",yylineno );
				$$->setName($1->getName()+","+$3->getName()+" "+$4->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
		| parameter_list COMMA type_specifier				{
				$$=$1;
				par[parNum]=" "; parType[parNum]=$3->getName(); parNum++;
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
				par[parNum]=" "; parType[parNum]=$1->getName(); parNum++;
				fprintf(parseLog, "\nAt line no : %d parameter_list : type_specifier\n\n",yylineno );
				$$->setName($1->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
 		;

 		
compound_statement : LCURL {manage('S',"..."); addToTable(); initParNum(); } statements RCURL	{
					$$=$3;
					fprintf(parseLog, "\nAt line no : %d compound_statement : LCURL statements RCURL\n\n",yylineno );
					$$->setName("{\n"+$3->getName()+"}\n");
					fprintf(parseLog,"%s\n",$$->getName().c_str());
					manage('E',"...");
					}
 		    | LCURL {manage('S',"..."); addToTable(); initParNum(); } RCURL	{ 
			 		fprintf(parseLog, "\nAt line no : %d compound_statement : LCURL RCURL\n\n",yylineno );
					$$->setName("{\n}\n");
					fprintf(parseLog,"{\n}\n");
					manage('E',"...");
					}
 		    ;
 		    
var_declaration : type_specifier declaration_list {
						addVars(fname,parNum);
					} SEMICOLON {
					initParNum();

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
							symbolInfo->arr=false;
							if(!global) symbolInfo->temp_var=fname+$3->getName();
							else symbolInfo->temp_var=$3->getName();
							par[parNum]=$3->getName();
							parNum++;
						}}
						
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : declaration_list COMMA ID\n\n",yylineno );
						$$->setName($1->getName()+ "," + $3->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str()); 
						}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
			   			c=manage('I',$3->getName() ,"ID"); if(!c) yyerror(muldec, $3->getName()); else {
						symbolInfo=getSymbol($3->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->ret_type="array";
							symbolInfo->arr=true;
							if(!global) symbolInfo->temp_var=fname+$3->getName();
							else symbolInfo->temp_var=$3->getName();
							addVars($3->getName(),$5->ival,true);
						}}
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n",yylineno );
						$$->setName($1->getName()+"," + $3->getName()+"["+$5->getName()+"]");
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
 		  | ID							{
			   			c=manage('I',$1->getName(),"ID"); if(!c) yyerror(muldec,$1->getName()); else {
						symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->arr=false;
							if(!global) symbolInfo->temp_var=fname+$1->getName();
							else symbolInfo->temp_var=$1->getName();
							par[parNum]=$1->getName();
							parNum++;
						}}
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : ID\n\n",yylineno );
						$$->setName($1->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str()); 
						}
 		  | ID LTHIRD CONST_INT RTHIRD	{
			   			c=manage('I',$1->getName(),"ID"); if(!c) yyerror(muldec,$1->getName()); else {
						symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0){
							symbolInfo->var_type=vType;
							symbolInfo->ret_type="array";
							symbolInfo->arr=false;
							if(!global) symbolInfo->temp_var=fname+$1->getName();
							else symbolInfo->temp_var=$1->getName();
							addVars($1->getName(),$3->ival,true);
						}}
						
						fprintf(parseLog, "\nAt line no : %d declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n",yylineno );
						$$->setName($1->getName()+"["+$3->getName()+"]");
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
 		  ;
 		  
statements : statement			{
					$$=$1;
					fprintf(parseLog, "\nAt line no : %d statements : statement\n\n",yylineno );
					$$->setName($1->getName());
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	   | statements statement	{
		   			$$=$1;
					$$->code+=$2->code;
		   			fprintf(parseLog, "\nAt line no : %d statements : statements statement\n\n",yylineno );
					$$->setName($1->getName()+"\n"+$2->getName());
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	   ;
	   
statement : var_declaration		{
						$$=$1;
						fprintf(parseLog, "\nAt line no : %d statement : var_declaration\n\n",yylineno );
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | expression_statement	{
		  				$$=$1;
		  				fprintf(parseLog, "\nAt line no : %d statement : expression_statement\n\n",yylineno );
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | compound_statement		{
		  				$$=$1;
		  				fprintf(parseLog, "\nAt line no : %d statement : compound_statement\n\n",yylineno );
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement	{
		  				
						$$=$3;
                        string loop=newLabel();
                        string skip=newLabel();
                        $$->code+=loop+":\n";
                        $$->code+=$4->code;
                        $$->code+="\tcmp "+$4->temp_var+",0\n";
                        $$->code+="\tje "+skip+"\n";
                        $$->code+=$7->code+$5->code;
                        $$->code+="\tjmp "+loop+"\n";
                        $$->code+=skip+":\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n",yylineno );
						$$->setName("for("+$3->getName()+$4->getName()+$5->getName()+")"+$7->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE	{

						$$=$3;
						$$->code+="\n\tcmp "+$3->temp_var+",0\n";
						string skip=string(newLabel());
						$$->code+="\tje "+skip+"\n";
						$$->code+=$5->code;
						$$->code+=skip+":\n\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE\n\n",yylineno );
						$$->setName("if("+$3->getName()+")"+$5->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | IF LPAREN expression RPAREN statement ELSE statement		{
		  				
						$$=$3;
						$$->code+="\n\tcmp "+$3->temp_var+",0\n";
						string skip=string(newLabel());
						string else_code=string(newLabel());
						$$->code+="\tje "+else_code+"\n";
						$$->code+=$5->code;
						$$->code+="\tjmp "+skip+"\n";
						$$->code+=else_code+":\n\n";
						$$->code+=$7->code;
						$$->code+=skip+":\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : IF LPAREN expression RPAREN statement ELSE statement\n\n",yylineno );
						$$->setName("if("+$3->getName()+")"+$5->getName()+" else "+$7->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | WHILE LPAREN expression RPAREN statement	{

						$$=$3;
						string loop=newLabel();
						string skip=newLabel();
						$$->code="\n"+loop+":\n";
						$$->code+="\tcmp "+$3->temp_var+",0\n";
						$$->code+="je "+skip+"\n";
						$$->code+=$5->code+"\n\tjmp "+loop+"\n" ;
						$$->code+=skip+":\n";

		  				fprintf(parseLog, "\nAt line no : %d statement : WHILE LPAREN expression RPAREN statement\n\n",yylineno );
						$$->setName("while("+$3->getName()+")"+$5->getName());
						fprintf(parseLog,"%s\n",$1->getName().c_str());
						}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON			{
		  				symbolInfo=getSymbol($3->getName());
						$$->code="\tmov ax,"+symbolInfo->temp_var+"\n";
						cout<< "I thiknk jhamela is here : "<<$3->temp_var+"\n";
						$$->code+="\tmov printVar,ax\n";
						$$->code+="\tcall SHOW\n";
						
		  				fprintf(parseLog, "\nAt line no : %d statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n",yylineno );
						
						}
	  | RETURN expression SEMICOLON					{
		  				$$=$2;
		  				rType=$2->var_type;
						
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
					$$=$1;
					fprintf(parseLog, "\nAt line no : %d expression_statement : expression SEMICOLON\n\n",yylineno ); 
					$$->setName($1->getName()+";"); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
			;
	  
variable : ID 			{
				$$=$1;
				symbolInfo=getSymbol($1->getName());
				$$->temp_var=symbolInfo->temp_var;
                $$->arr=false;
				
				c=manage('L',$1->getName()); if(!c) yyerror(undecvar,$1->getName()); 
				
				if(symbolInfo!=0) {
					if(symbolInfo->ret_type=="array") yyerror(arrIn,$1->getName());
					$$->var_type=symbolInfo->var_type;
				}
				fprintf(parseLog, "\nAt line no : %d variable : ID\n\n",yylineno );
				$$->setName($1->getName());
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}	
	 | ID LTHIRD expression RTHIRD 	{
		 		symbolInfo=getSymbol($1->getName());
		 		$$=$1;
				$$->code+=$3->code;
				$$->code+="\tmov bx,"+$3->temp_var+"\n";
            	$$->code+="\tshl bx,1\n";
	            $$->temp_var=symbolInfo->temp_var+"[bx]";
		 		$$->arr=true;
				c=manage('L',$1->getName()); if(!c) yyerror(undecvar,$1->getName()); 

		 		if($3->var_type=="void") yyerror(voidcall);
		 		else if($3->var_type!="int") yyerror(nonIn);
				
				if(symbolInfo!=0) {
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
					$$=$1;

					fprintf(parseLog, "\nAt line no : %d expression : logic_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
	   | variable ASSIGNOP logic_expression	{
		   			$$=$1;

					$$->code+=$3->code;
                    $$->code+="\tmov ax,"+$3->temp_var+"\n";
                    $$->code+="\tmov "+$1->temp_var+",ax\n";
                    $$->temp_var=newTemp();
                    $$->code+="\tmov "+$$->temp_var+",ax\n";

					if($3->var_type=="void") yyerror(voidcall);
					else if($1->var_type!=$3->var_type) yyerror(typemm);
					//cout<<$1->getName()<<" "<< $1->var_type<< " "<<$3->var_type<<endl;
					
		   			fprintf(parseLog, "\nAt line no : %d expression : variable ASSIGNOP logic_expression\n\n",yylineno ); 
					$$->setName($1->getName()+"="+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
	   ;
			
logic_expression : rel_expression 	{
					$$=$1;
					fprintf(parseLog, "\nAt line no : %d logic_expression : rel_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 | rel_expression LOGICOP rel_expression 	{
			 		$$=$1;
					$$->code+=$3->code;
					char *temp=newTemp();
					$$->code+="\tmov ax,"+$1->temp_var+"\n";
					$$->temp_var=string(temp);
					if($2->getName()=="&&"){
						$$->code+="\tand ax,"+$3->temp_var+"\n";
					}else{
						$$->code+="\tor ax,"+$3->temp_var+"\n";
					}
					$$->code+="\tmov "+$$->code+",ax\n";

			 		$$->var_type="int";  
			 		fprintf(parseLog, "\nAt line no : %d logic_expression : rel_expression LOGICOP rel_expression\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 ;
			
rel_expression	: simple_expression		{
					$$=$1; 
					fprintf(parseLog, "\nAt line no : %d rel_expression : simple_expression\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		| simple_expression RELOP simple_expression	{ /* Relational Opertator type is Integer */
					$$=$1;
					char *temp=newTemp();
					$$->temp_var=string(temp);
					$$->code+="\tmov ax,"+$1->temp_var+"\n";
					$$->code+="\tcmp ax,"+$3->temp_var+"\n";
					string do_work=string(newLabel());
					string escape_work=string(newLabel());

					if($2->getName()=="<")
                    	$$->code+="\tjge "+do_work+"\n";
                    else if($2->getName()=="<=")
                        $$->code+="\tjg "+do_work+"\n";
                    else if($2->getName()==">")
                        $$->code+="\tjle "+do_work+"\n";
                    else if($2->getName()==">=")
                        $$->code+="\tjl "+do_work+"\n";
                    else
                        $$->code+="\tjne "+do_work+"\n";
					
					$$->code+="\tmov "+$$->temp_var+",1\n";
                    $$->code+="\tjmp "+escape_work+"\n";
                    $$->code+=do_work+":\n";
					$$->code+="\tmov "+$$->temp_var+",0\n";
                    $$->code+=escape_work+":\n";

					$$->var_type="int"; 
					fprintf(parseLog, "\nAt line no : %d rel_expression : simple_expression RELOP simple_expression\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		;
				
simple_expression : term	{
					$$=$1;
					fprintf(parseLog, "\nAt line no : %d simple_expression : term\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		  | simple_expression ADDOP term 	{
			  		$$=$1;
					$$->code+=$3->code;
					$$->code+="\tmov ax,"+$1->temp_var+"\n";
					$$->code+="\tmov bx,"+$3->temp_var+"\n";
					char* temp=newTemp();
					$$->temp_var=string(temp);

					if($2->getName()=="+"){
						$$->code+="\tadd ax,bx\n";
						
					}else{
						$$->code+="\\tsub ax,bx\n";
					}
					$$->code+="\tmov "+$$->temp_var+", ax\n";

			  		if($1->var_type=="float" || $3->var_type=="float") $$->var_type="float";
					else $$->var_type="int";
			  		fprintf(parseLog, "\nAt line no : %d simple_expression : simple_expression ADDOP term\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		  ;
					
term :	unary_expression {
				$$=$1;
				fprintf(parseLog, "\nAt line no : %d term : unary_expression\n\n",yylineno ); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
     |  term MULOP unary_expression	{
		 		$$=$1;
				$$->code="\tmov ax,"+$1->temp_var+"\n";
				$$->code+="\tmov bx,"+$3->temp_var+"\n";
				$$->code+="\txor dx,dx\n";
				char *temp=newTemp();
				$$->temp_var=temp;
				if($2->getName()=="*"){
					$$->code+="\tmul bx\n";
					$$->code+="\tmov "+$$->temp_var+",ax\n";
				}else if($2->getName()=="/"){
					$$->code+="\tdiv bx\n";
					$$->code+="\tmov "+$$->temp_var+",ax\n";
				}else{
					$$->code+="\tdiv bx\n";
					$$->code+="\tmov "+string(temp)+",dx\n";
				}

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
					$$=$2;
                    string temp=newTemp();
                    $$->code+="\tmov ax,"+$$->temp_var+"\n";
                    $$->code+="\tmov "+temp+",ax\n";
					$$->temp_var=temp;
					if($1->getName() == "-"){
						$$->code="\tneg "+$2->temp_var+"\n";
					}
					fprintf(parseLog, "\nAt line no : %d unary_expression : ADDOP unary_expression\n\n",yylineno ); 
					$$->setName($1->getName()+$2->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 | NOT unary_expression 			{
			 		$$=$2;
                    string t=newTemp();
                    $$->code+="\tmov ax,"+$2->temp_var+"\n";
                    $$->code+="\tmov "+t+",ax\n";
                    $$->temp_var=t;
                    $$->code+="\tnot "+$$->temp_var+"\n";

			 		$$->var_type="int";
			 		fprintf(parseLog, "\nAt line no : %d unary_expression : NOT unary_expression\n\n",yylineno ); 
					$$->setName("!"+$2->getName()); 
					fprintf(parseLog,"%s\n",("!"+$2->getName()).c_str()); 
					}
		 | factor 							{
			 		$$=$1;
			 		fprintf(parseLog, "\nAt line no : %d unary_expression : factor\n\n",yylineno ); 
					fprintf(parseLog,"%s\n",$1->getName().c_str()); 
					}
		 ;
	
factor	: variable		{

				$$=$1;
				//cout<<$1->ret_type<<" "<<$1->getName()<<endl;
				//cout<<"mara"<<endl;
				if($1->arr)
                {
                    string temp=newTemp();
                    $$->code+="\tmov ax,"+$$->temp_var+"\n";
                    $$->code+="\tmov "+temp+",ax\n";
                    $$->temp_var=temp;
                }

				fprintf(parseLog, "\nAt line no : %d factor : variable\n\n",yylineno ); 
				$$->setName($1->getName()); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| ID LPAREN argument_list RPAREN	{ /* Function Call */

				$$->code="\tcall "+$1->getName()+"\n";
				$$->arr=false;
				
				symbolInfo=getSymbol($1->getName()); if(symbolInfo!=0) {
					$$->var_type=symbolInfo->ret_type;
					if(symbolInfo->parNum!=argNum){
						 yyerror("\nError at line %d, Parameter number doesn't match!\n");
						 cout<<symbolInfo->getName()<< " "<< symbolInfo->parNum<< " "<<argNum<<endl;
					}
					else if(!matchPL(symbolInfo->parTList,argType,argNum)) yyerror("\nError at line %d. Parameter type doesn't match\n");
					if(!symbolInfo->func_defined) yyerror("\nError at line :%d. Function %s not defined\n",$1->getName());
				} else{
					yyerror(undecfunc,$1->getName());
				} argNum=0;
				fprintf(parseLog, "\nAt line no : %d factor : ID LPAREN argument_list RPAREN\n\n",yylineno ); 
				$$->setName($1->getName()+"("+$3->getName() +")" ); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| LPAREN expression RPAREN			{
				$$=$2;
				fprintf(parseLog, "\nAt line no : %d factor : LPAREN expression RPAREN\n\n",yylineno ); 
				$$->setName("("+$2->getName()+")"); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| CONST_INT			{
				$$=$1;
				$$->temp_var=$1->getName();
				$$->arr=false;
				
				vType="int"; $$->var_type="int";
				fprintf(parseLog, "\nAt line no : %d factor : CONST_INT\n\n",yylineno ); 
				fprintf(parseLog,"%s\n",$1->getName().c_str());
				}
	| CONST_FLOAT		{ 
				$$=$1;
				$$->temp_var=$1->getName();
				$$->arr=false;

				vType="float"; $$->var_type="float";
				fprintf(parseLog, "\nAt line no : %d factor : CONST_FLOAT\n\n",yylineno );
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| variable INCOP	{
				$$=$1;
				$$->code+="\tinc "+$1->temp_var+"\n";

				fprintf(parseLog, "\nAt line no : %d factor : variable INCOP\n\n",yylineno ); 
				$$->setName($1->getName() + "++"); 
				fprintf(parseLog,"%s\n",$1->getName().c_str()); 
				}
	| variable DECOP	{
				$$=$1;
				$$->code+="\tinc "+$1->temp_var+"\n";

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
					
					argType[argNum]=$3->var_type; argNum++;
					fprintf(parseLog, "\nAt line no : %d arguments : arguments COMMA logic_expression\n\n",yylineno ); 
					$$->setName($1->getName()+","+$3->getName()); 
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	      | logic_expression	{
			  		
					argType[argNum]=$1->var_type; argNum++;
					fprintf(parseLog, "\nAt line no : %d arguments : logic_expression\n\n",yylineno );
					fprintf(parseLog,"%s\n",$1->getName().c_str());
					}
	      ;
 

%%
int main(int argc,char *argv[])
{
	

	int yydebug=1;
	FILE *input=0;

	if(argc<3){
		cout<<"Input not right!"<<endl;
	}else{
		input=fopen(argv[1],"r"); cout<<argv[1]<<endl;
		parseLog=fopen(argv[2],"w"); cout<<argv[2]<<endl;
		parseError=fopen(argv[3],"w"); cout<<argv[3]<<endl;
		gCode=fopen("code.asm","w");
	}
	
	//FILE *input=fopen("input.txt","r");
	yyin=input;

	//parseLog=fopen("log.txt","w");
	//parseError=fopen("error.txt","w");
	if(parseLog==NULL or input==NULL or parseError==NULL or gCode==NULL){
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