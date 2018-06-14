#include<bits/stdc++.h>
#include<cstring>
#include<cstdlib>
using namespace std;

class SymbolInfo
{
    string name;
    string type;

public:
    SymbolInfo * next;

    SymbolInfo()
    {
        name="null";
        type="null";
        next=0;
    }

    SymbolInfo(string n,string t)
    {
        name=n;
        type=t;
        next=0;
    }

    void setSymbol(string n,string t)
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

class ScopeTable
{
    SymbolInfo **arr;
    int capacity;
    int amount;
    int id;

public:
    ScopeTable * parentScope;
    ScopeTable(int cap,int l)
    {
        capacity=cap;
        id=l;
        amount=0;
        arr=new SymbolInfo*[capacity];
        for(int i=0;i<capacity;i++)
        {
            arr[i]=0;
        }
    }

    unsigned long hashfunc(string key)
    {
        unsigned long h = 5381;

        for(int i=0;i<key.length();i++)
        {
            h = ((h << 5) + h) + (int)key[i];
        }

        return (h%capacity);
    }

    bool sinsert(string n,string t)
    {
        int hx;

        hx=hashfunc(n);

        SymbolInfo *tem;
        tem=new SymbolInfo();
        tem->setSymbol(n,t);
        tem->next = arr[hx];
        arr[hx]=tem;
        amount++;
        return true;
    }

    SymbolInfo* slook_up(string key)
    {
        int hx;
        int count=0;

        hx=hashfunc(key);

        SymbolInfo *tem;
        tem=arr[hx];
        while(tem!=0)
        {
            string o1=tem->getName();
            if(o1 == key)
            {
                return tem;
            }
            tem=tem->next;
            count++;
        }
        return 0;
    }

    bool sdelete(string key)
    {
        int hx,count=0;

        hx=hashfunc(key);

        SymbolInfo *tem, *prev ;
        tem = arr[hx] ;
        while (tem != 0)
        {
            if (tem->getName() == key) break ;
            prev = tem;
            tem = tem->next ;
            count++;
        }
        if (tem == 0) return false ; //item not found to delete
        if (tem == arr[hx]) //delete the first node
        {
            amount--;
            arr[hx] = arr[hx]->next ;
            delete(tem) ;
        }
        else
        {
            amount--;
            prev->next = tem->next ;
            delete(tem);
        }
        return true;
    }

    void printScopeTable()
    {
        cout<<"ScopeTable # "<<id<<endl;
        for(int i=0;i<capacity;i++)
        {
            cout<<i<<" --> ";
            SymbolInfo* temp;
            temp=arr[i];
            while(temp!=0)
            {
                cout<<"<"<<temp->getName()<<", "<<temp->getType()<<">";
                temp=temp->next;
            }
            cout<<endl;
        }
    }

    int getId()
    {
        return id;
    }

};

class SymbolTable
{
    int no;
public:
    ScopeTable * currentScope;
    SymbolTable()
    {
        currentScope=0;
        no=0;
    }

    int EnterScope(int s)
    {
        int t;
        no++;
        t=no;
        ScopeTable * x;
        x= new ScopeTable(s,no);
        x->parentScope=currentScope;
        currentScope=x;
        return t;
    }

    int ExitScope()
    {
        if(currentScope==0)
        {
            cout<<"No scope table found from which we can exit"<<endl;
            return 0;
        }
        int t=no;
        no--;
        ScopeTable * tem;
        tem=currentScope;
        currentScope=currentScope->parentScope;
        delete(tem);
        return t;
    }

    bool syinsert(string n,string t)
    {
        bool k;
        if(currentScope==0)
        {
            k=false;
            cout<<"Create a scopetable first and then try to insert"<<endl;
            return k;
        }
        //p1=currentScope->getId();
        SymbolInfo * tem= currentScope->slook_up(n);
        if(tem==0)
        {
            k=currentScope->sinsert(n,t);
        }
        else
        {
            k=false;
        }
        return k;
    }

    bool syremove(string n)
    {
        if(currentScope==0)
        {
            cout<<"Create a scopetable first and then try to insert and then delete item"<<endl;
            return false;
        }
        //p1=currentScope->getId();
        bool k=currentScope->sdelete(n);
        return k;
    }

    SymbolInfo * sylook_up(string n)
    {
        if(currentScope==0)
        {
            cout<<"Create a scopetable first and then try to insert and then search an item"<<endl;
            return 0;
        }
        ScopeTable * cur=currentScope;
        SymbolInfo * f;
        while(cur!=0)
        {
            f= cur->slook_up(n);
            if(f==0)
            {
                cur=cur->parentScope;
            }
            else
            {
                //p1=currentScope->getId();
                break;
            }
        }
        return f;
    }

    void printCurrentScope()
    {
        if(currentScope==0)
        {
            cout<<"No scope table present"<<endl;
            return;
        }
        currentScope->printScopeTable();
    }

    void printAllScope()
    {
        if(currentScope==0)
        {
            cout<<"No scope table present"<<endl;
            return;
        }
        ScopeTable * cur=currentScope;
        while(cur!=0)
        {
            cur->printScopeTable();
            cur=cur->parentScope;
        }
    }
};
