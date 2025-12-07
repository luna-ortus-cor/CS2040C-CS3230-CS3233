#include <bits/stdc++.h>
using namespace std;

//for each set just iterate through the list
//keep track of current index through the list
//if index is even print
//else push to stack
//finally pop and print from stack until empty

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n=1;
    int m;
    cin>>m;
    while(m){
        cout<<"SET "<<n<<"\n";
        stack<string> s;
        string name;
        for(int i=0;i<m;i++){
            cin>>name;
            if(i%2){
                s.push(name);
            }else{
                cout<<name<<"\n";
            }
        }
        while(!s.empty()){
            cout<<s.top()<<"\n";
            s.pop();
        }
        n++;
        cin>>m;
    }
}
