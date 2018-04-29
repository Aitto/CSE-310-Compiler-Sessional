#include "1505120_Symbol_Info.cpp"


class ScopeTable{
private:
    int tableSize;
    int position;
    int id;
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
    bool Insert(string symbol_type,string symbol_name){
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
            newSymbol->setSymbol(symbol_type,symbol_name);
            newSymbol->prev=temp;
        }else{ //If empty Hash table, then allocate memory and put symbol info
            HashFile[index]=new SymbolInfo;
            HashFile[index]->setSymbol(symbol_type,symbol_name);
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
        //cout<< " Scope Table # "<<id<< "\n"<<endl;
	fprintf(logOut," Scope Table # %d\n",id);
        for(int i=0;i<tableSize;i++){
	    SymbolInfo *temp=HashFile[i];
	    if(temp==0) continue;
            //cout<< " ["<<i<< "]-->";
	    fprintf(logOut," [%d]-->",i);
            

            while(temp!=0){
		const char *sn=new char[temp->symbol_name.length()+1];
		sn=temp->symbol_name.c_str();
		const char *st=new char[temp->symbol_type.length()+1];
		st=temp->symbol_type.c_str();
	        fprintf(logOut,"<%s, %s>",sn,st);
               // cout<<temp->symbol_name<< " "<<temp->symbol_type<<endl;
                temp=temp->next;
		//free(sn);
		//free(st);
            }
            fprintf(logOut,"\n");
        }
    }

    void setId(int x){
        id=x;
    }

    int getId(){
        return id;
    }
};
