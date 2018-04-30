#include "1505120_Symbol_Table.cpp"

void manage(char ch,string en1,string en2="\0"){
    int hashSize;

	switch(ch){
            case 'I':
                {
                    //cin>>en1>>en2;
                    if(st.Insert(en1,en2))
                        //cout<< "\n Inserted in ScopeTable# "<<st.getTableNumber()<< " at position "<<iIndex<< ", "<<iPosition<<endl;
			fprintf(logOut,"\n Inserten is Scopetable #%d at position %d %d\n",st.getTableNumber(),iIndex,iPosition);
                    else
                        cout<< "Error! already exist"<<endl;
		    st.PrintCurrent();

                    break;
                }
            case 'L':
                {
                    //cin>>en1;

                    if(st.Lookup(en1)!=0) cout<< "\n Found in ScopeTable# "<<iTable<< " at position "<<iIndex<<","<<iPosition<<endl;
                    else cout<< "Not found!"<<endl;
                    break;
                }
            case 'D':
                {
                    //cin>>en1;
                    if(st.Remove(en1)){
                        cout<< "\n Found in ScopeTable# "<<st.getTableNumber()<< " at position "<<iIndex<< ", "<<iPosition<<endl;
                    }
                    else cout<< "\n Not found!"<<endl;
                    break;
                }
            case 'P':
                {
                    //cin>>ch;
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
        }

}

int main(){
    freopen("Test.txt","r",stdin);

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

