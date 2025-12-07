#include <bits/stdc++.h>
using namespace std;

//just simulate the entire thing with 1 stack
//at the end pop and sum all elements in stack
//then take modulo

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    cin>>n>>k;
    stack<int> s;
    string c;
    while(cin>>c){
        if(c=="undo"){
            cin>>c;
            int u=stoi(c);
            while(u--){
                s.pop();
            }
        }else{
            s.push(stoi(c));
        }
    }
    int ans=0;
    while(!s.empty()){
        ans+=s.top();
        s.pop();
    }
    cout<<(ans+1000000*n)%n;
    return 0;
}
