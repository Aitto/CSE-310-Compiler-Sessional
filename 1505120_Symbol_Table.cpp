#include "1505120_Scope_Table.cpp"

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
            head->setId(tableNumber);
        }
        else{
            ScopeTable *newScope=new ScopeTable(hashSize);
            tail->next=newScope;
            newScope->prev=tail;
            tail=newScope;
            newScope->next=0;
            tail->setId(tableNumber);
        }
    }

    void exitScope(){
        tableNumber--;
        if(tail!=0){
            if(tail->prev!=0){
                ScopeTable *temp=tail->prev;
                free(tail);
                temp->next=0;
                tail=temp;
                //free(tail);
            }else{
                ScopeTable *temp=tail;
                head=0;
                tail=0;
                free(temp);
            }
        }
    }

    bool Insert(string symbol_name,string symbol_type){
        if(tail!=0){
            return tail->Insert(symbol_type,symbol_name);
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
        //cout<< "Printing Current Scope Table: \n"<<endl;

        if(tail!=0){
            tail->Print();
        }
    }

    void PrintAll(){
        cout<< "Printing All Scope table: \n"<<endl;

        ScopeTable *temp=head;

        while(temp!=0){

            temp->Print();

            temp=temp->next;
        }
    }

    int getTableNumber(){
        return tail->getId();
    }
};


SymbolTable st;
