#include <bits/stdc++.h>
using namespace std;

//simulate the entire process with a stack
//check for $,|,* characters and push to stack as b,t,j
//then if find b,t,j characters just check if stack not empty
//and top of stack is same character, else not possible
//finally check stack is empty, else not possible

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    string s;
    while(cin>>s){
        bool possible=true;
        stack<char> stk;
        for(auto c:s){
            if(c=='$'){
                stk.push('b');
            }else if(c=='|'){
                stk.push('t');
            }else if(c=='*'){
                stk.push('j');
            }else if(c=='.'){
                
            }else{
                if(stk.empty() || stk.top()!=c){
                    possible=false;
                    break;
                }else{
                    stk.pop();
                }
            }
        }
        if(!stk.empty())possible=false;
        if(possible)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
