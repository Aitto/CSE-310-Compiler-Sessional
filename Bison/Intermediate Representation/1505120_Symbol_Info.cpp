#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>

#define sf scanf
#define pf printf
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define lli long long int

using namespace std;


//Symbol info class. Containing symbol name and type
class SymbolInfo{
public:
    string symbol_name,symbol_type;
    string var_type,ret_type;
    string code;
    string temp_var;
    string var_name;

    int ival;
    float dval;
    int parNum;
    bool func_defined;
    bool func_declared;
    bool arr;
    string parTList[10];

    //This is separate chaining implementation. Next (pointer) for containing address to next pointer.
    SymbolInfo *next;
    SymbolInfo *prev;

    //Initialization
    SymbolInfo(string name=" ",string type=" "){
        symbol_name=name, symbol_type=type;
        next=0;
        prev=0;
        ival=0, parNum=0, func_defined=false, func_declared=false;
        dval=0; var_type="none", ret_type="none";
        arr=false;
    }

    void setName(string s){
        symbol_name=s;
    }

    string getName(){
        char *ans=new char[symbol_name.length() +1];
        strcpy(ans,symbol_name.c_str());
        return symbol_name;
        //return ans;
    }

    void setIval(int i){
        ival=i;
    }

    int getIval(){
        return ival;
    }

    void setDval(float d){
        dval=d;
    }

    float getDval(){
        return dval;
    }

    void setType(string s){
        symbol_type=s;
    }

    string getType(){
        char *ans=new char[symbol_type.length() +1];
        strcpy(ans,symbol_type.c_str());
        return symbol_type;
        //return ans;
    }

    void setSymbol(string name=0,string type=0){
        symbol_name=name, symbol_type=type;
        next=0;
        prev=0;
    }

    void parSet(string s[],int p){
        for(int i=0;i<p;i++){
            parTList[i]=s[i];
        }
    }
};


