#include "1505120_Symbol_Table.cpp"

bool manage(char ch,string en1,string en2="a"){

	switch(ch){
            case 'I':
                {
                    /*
                        Insertion in the scope table
                    */
                    if(st.getTableNumber()==0) st.enterScope(hashSize); 
                    SymbolInfo *tmp=st.Lookup(en1);
                    if(tmp!=0){
                        if(tmp->symbol_type=="foo"){
                            cout<<"Variable or function with same name"<<endl; return false;
                        }
                    }
                    if(st.Insert(en1,en2)) return true;
                    cout<< "Not inserted!"<<endl;
		            //st.PrintCurrent();
                    break;
                    
                }
            case 'L':
                {

                    if(st.Lookup(en1)!=0){
                        //cout<< "\n Found in ScopeTable# "<<iTable<< " at position "<<iIndex<<","<<iPosition<<endl;
                        //fprintf(parseLog,"\n Found in ScopeTable# %d at position %d,%d\n",iTable,iIndex,iPosition);
                        return true;
                    }
                    else {
                        //cout<< "Not found!"<<endl;
                        //fprintf(parseLog,"Not found!\n");
                        return false;
                    }
                    
                }
            case 'D':
                {
                    //cin>>en1;
                    if(st.Remove(en1)){
                        cout<< "\n Found in ScopeTable# "<<st.getTableNumber()<< " at position "<<iIndex<< ", "<<iPosition<<endl;
                        fprintf(parseLog,"\n Found in ScopeTable# %d at position %d,%d\n",st.getTableNumber(),iIndex,iPosition);
                        return true;
                    }
                    else {
                        cout<< "Not found!"<<endl;
                        fprintf(parseLog,"Not found!\n");
                        return false;
                    }
                }
            case 'P':
                {
                    //cin>>ch;
                    if(ch=='A') st.PrintAll();
                    else st.PrintCurrent();
                    return true;
                }
            case 'S':
                {
                    st.enterScope(hashSize);
                    //int tn=st.getTableNumber();
                    
                    fprintf(parseLog,"\n Creating new Scope Table with id# %d\n\n",st.getTableNumber());

                    return true;
                }
            case 'E':
                {
                    st.PrintAll();
                    fprintf(parseLog, "\n Deleting table with Id# %d\n",st.getTableNumber() );
                    st.exitScope();
                    return true;
                }
        }
        return false;

}

SymbolInfo * getSymbol(string s){
    return st.Lookup(s);
}

/*int main(){
    //freopen("Test.txt","r",stdin);

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
                        cout<< "\n Inserted in ScopeTable# "<<st.getTableNumber()<< " at position "<<iIndex<< ", "<<iPosition<<endl;
                    else
                        cout<< "Error! already exist"<<endl;
                    break;
                }
            case 'L':
                {
                    cin>>en1;
                    //SymbolInfo *te;
                    if(st.Lookup(en1)!=0) cout<< "\n Found in ScopeTable# "<<iTable<< " at position "<<iIndex<<","<<iPosition<<endl;
                    else cout<< "Not found!"<<endl;
                    break;
                }
            case 'D':
                {
                    cin>>en1;
                    if(st.Remove(en1)){
                        cout<< "\n Found in ScopeTable# "<<st.getTableNumber()<< " at position "<<iIndex<< ", "<<iPosition<<endl;
                    }
                    else cout<< "\n Not found!"<<endl;
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

}*/

