#include<bits/stdc++.h>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;

class SymbolInfo
{
    string name;
    string type;

public:
    SymbolInfo * next;

    SymbolInfo(string n,string t)
    {
        name=n;
        type=t;
        next=0;
    }

    string getName()
    {
        return name;
    }

    string getType()
    {
        return type;
    }

};
