#include <bits/stdc++.h>
using namespace std;

//use stack, read input one by one
//if sum of top of stack and current is even
//decrement n by 2, pop from stack
//else push current to stack
//since "greedy" algo will work here as only concerned with min number of cards left

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    stack<int> s;
    int num;
    while(cin>>num){
        if(!s.empty() && (s.top()+num)%2==0){
            n-=2;
            s.pop();
        }else{
            s.push(num);
        }
    }
    cout<<n;
    return 0;
}
