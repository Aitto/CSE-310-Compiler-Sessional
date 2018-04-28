
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<stdlib.h>

#define sf scanf
#define pf printf
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define lli long long int

using namespace std;

int iPosition;
int iIndex;
int iTable;

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

// Basically it's the hashTable
class ScopeTable{
private:
    int tableSize;
    int position;
    //Double pointer. For containing 2D pointer.
    SymbolInfo **HashFile;

    //Hash function
    int getIndex(string s){
        int len=s.length();
        lli index=7;
        for(int i=0;i<len;i++) index=index*31 + s[i];
        return (int)index%tableSize;
    }

public:
    //For keeping track from Symbol table
    ScopeTable *next;
    ScopeTable *prev;

    //Initialize with 1000 sized hash table
    ScopeTable(int n=1000){
        tableSize=n;
        HashFile=new SymbolInfo*[tableSize];
        for(int i=0;i<tableSize;i++) HashFile[i]=0;
        next=0;
        prev=0;
        position=0;
    }

    //Inserting into Hash table
    bool Insert(string symbol_name,string symbol_type){
        //If variable with the same name in the current scope, then return false
        if(Lookup(symbol_name)!=0) return false;

        int index=getIndex(symbol_name);
        iIndex=index;

        //If hash index is not empty, then increase members in chain.
        if(HashFile[index]!=0){
            SymbolInfo *newSymbol=new SymbolInfo;
            SymbolInfo *temp=HashFile[index];
            position=0;
            while(temp->next!=0) {
                temp=temp->next;
                position++;
            }

            iPosition=position;

            //Insert new item in the chain
            temp->next=newSymbol;
            newSymbol->setSymbol(symbol_name,symbol_type);
            newSymbol->prev=temp;
        }else{ //If empty Hash table, then allocate memory and put symbol info
            HashFile[index]=new SymbolInfo;
            HashFile[index]->setSymbol(symbol_name,symbol_type);
        }
        return true;
    }

    //Return true is symbol name is found and false otherwise
    SymbolInfo* Lookup(string symbol_name){
        int index=getIndex(symbol_name);

        SymbolInfo *ans=0;

        if(HashFile[index]==0) return 0;
        else{
            iIndex=index;
            SymbolInfo *temp;
            temp=HashFile[index];
            iPosition=0;
            while(temp!=0){
                if(temp->symbol_name==symbol_name){
                    ans=temp;
                    break;
                }
                temp=temp->next;
                iPosition++;
            }
        }
        return ans;
    }

    //Returns true if found. Otherwise return false;
    bool Delete(string symbol_name){

        int index=getIndex(symbol_name);

        bool ans=false;

        if(HashFile[index]==0) return false;
        else{
            iIndex=index;
            SymbolInfo *temp;
            temp=HashFile[index];
            iPosition=0;

            while(temp!=0){
                // If symbol matches
                if(temp->symbol_name==symbol_name){
                    if(temp->next!=0){
                        if(temp->prev!=0){
                            temp->prev->next=temp->next;
                            temp->next->prev=temp->prev;
                            free(temp);
                            ans=true;
                            break;
                        }else{
                            HashFile[index]=temp->next;
                            HashFile[index]->prev=0;
                            free(temp);
                            ans=true;
                            break;
                        }
                    }else{
                        if(temp->prev!=0){
                            temp->prev->next=0;
                            free(temp);
                            ans=true;
                            break;
                        }else{
                            HashFile[index]=0;
                            free(temp);
                            ans=true;
                            break;
                        }
                    }
                }
                temp=temp->next;
                iPosition++;
            }
        }

        return ans;
    }

    void Print(){
        cout<< "Printing Scope Table: "<<endl;
        for(int i=0;i<tableSize;i++){

            SymbolInfo *temp=HashFile[i];

            while(temp!=0){
                cout<<temp->symbol_name<< " "<<temp->symbol_type<<endl;
                temp=temp->next;
            }
        }
    }
};

class SymbolTable{
private:
    ScopeTable *head;
    ScopeTable *tail;
    int tableNumber;
public:

    SymbolTable(){
        head=0;
        tail=0;
        tableNumber=0;
    }

    //Creating a new scope and making it current scope
    void enterScope(int hashSize){
        tableNumber++;
        if(head==0){
            head=new ScopeTable(hashSize);
            head->next=0;
            head->prev=0;
            tail=head;
        }
        else{
            ScopeTable *newScope=new ScopeTable(hashSize);
            tail->next=newScope;
            newScope->prev=tail;
            tail=newScope;
            newScope->next=0;
        }
    }

    void exitScope(){
        tableNumber--;
        if(tail!=0){
            if(tail->prev!=0){
                tail->prev->next=0;
                tail=tail->prev;
                //free(tail);
            }else{
                head=0;
                tail=0;
                free(tail);
            }
        }
    }

    bool Insert(string symbol_name,string symbol_type){
        if(tail!=0){
            return tail->Insert(symbol_name,symbol_type);
        }
        return 0;
    }

    bool Remove(string symbol_name){
        if(tail!=0) return tail->Delete(symbol_name);
        return false;
    }

    SymbolInfo* Lookup(string symbol_name){
        if(tail==0) return 0;

        ScopeTable *temp=tail;
        SymbolInfo *ans=0;

        iTable=0;

        while(temp!=0){
            ans=temp->Lookup(symbol_name);
            if(ans!=0) {
                iTable=tableNumber-iTable;
                return ans;
            }
            temp=temp->prev;
            iTable++;
        }
        return 0;
    }

    void PrintCurrent(){
        cout<< "Printing Current Scope Table: "<<endl;

        if(tail!=0){
            tail->Print();
        }
    }

    void PrintAll(){
        cout<< "Printing All Scope table: "<<endl;

        ScopeTable *temp=head;

        while(temp!=0){

            temp->Print();

            temp=temp->next;
        }
    }
    int getTableNumber(){
        return tableNumber;
    }
};

int main(){
    freopen("test.txt","r",stdin);

    int hashSize;

    cin>>hashSize;

    char ch;
    string en1,en2;
    SymbolTable st;
    st.enterScope(hashSize);

    while(1){
        cin>>ch;

        switch(ch){
            case 'I':
                {
                    cin>>en1>>en2;
                    if(st.Insert(en1,en2))
                        cout<< " Inserted in ScopeTable# "<<st.getTableNumber()<< " at position "<<iIndex<< ", "<<iPosition<<endl;
                    else
                        cout<< "Error! already exist"<<endl;
                    break;
                }
            case 'L':
                {
                    cin>>en1;
                    //SymbolInfo *te;
                    if(st.Lookup(en1)!=0) cout<< "Found in ScopeTable# "<<iTable<< "at position "<<iIndex<<","<<iPosition<<endl;
                    else cout<< "Not found!"<<endl;
                    break;
                }
            case 'D':
                {
                    cin>>en1;
                    if(st.Remove(en1)){
                        cout<< "Found in ScopeTable# "<<st.getTableNumber()<< "at position "<<iIndex<< ", "<<iPosition<<endl;
                    }
                    else cout<< "Not found!"<<endl;
                    break;
                }
            case 'P':
                {
                    cin>>ch;
                    if(ch=='A') st.PrintAll();
                    else st.PrintCurrent();
                    break;
                }
            case 'S':
                {
                    st.enterScope(hashSize);
                    break;
                }
            case 'E':
                {
                    st.exitScope();
                    break;
                }
            default:
                exit(1);
        }
    }


    return 0;

}
