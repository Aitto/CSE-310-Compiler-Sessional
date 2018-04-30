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
        //cout<< "Printing Current Scope Table: "<<endl;

        if(tail!=0){
            tail->Print();
        }
    }

    void PrintAll(){
        //cout<< "Printing All Scope table: "<<endl;

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



SymbolTable st;
