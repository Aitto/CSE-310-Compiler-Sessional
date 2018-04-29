#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>

#define sf scanf
#define pf printf
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define lli long long int

using namespace std;

int iPosition;
int iIndex;
int iTable;
int hashSize;

FILE *fin;
FILE *tokenOut;
FILE *logOut;

//Symbol info class. Containing symbol name and type
class SymbolInfo{
public:
    string symbol_name,symbol_type;
    //This is separate chaining implementation. Next (pointer) for containing address to next pointer.
    SymbolInfo *next;
    SymbolInfo *prev;

    //Initialization
    SymbolInfo(){
        next=0;
    }

    void setSymbol(string n=0,string t=0){
        symbol_name=n, symbol_type=t;
        next=0;
        prev=0;
    }
};
