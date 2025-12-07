#include <bits/stdc++.h>
using namespace std;

//just simulate the entire process with 2 stacks
//increment moves taken by 1 everytime move from stack1 to stack2 or stack1 and stack2 match, pop both

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int num;
    stack<int> s1,s2;
    for(int i=0;i<2*n;i++){
        cin>>num;
        s1.push(num);
    }
    int ans=0;
    while(!s1.empty()){
        if(!s2.empty() && s1.top()==s2.top()){
            ans++;
            s1.pop();
            s2.pop();
        }else{
            s2.push(s1.top());
            s1.pop();
            ans++;
        }
    }
    if(s2.empty()){
        cout<<ans;
    }else{
        cout<<"impossible";
    }
    return 0;
}
