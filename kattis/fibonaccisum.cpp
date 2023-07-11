#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//this problem is just greedy, as we know
//each fibo number cn = c(n-1)+c(n-2)
//thus selecting largest cn always minimizes
//number of fibo nums selected
//given target integer n
//generate all fibo up to n
//reverse
//initialize pointer, while pointer not end
//and pointer > n, pointer increment
//subtract pointer element from n
//push back pointer element to ans
//reverse ans and print

int main(){
    ll n;
    cin>>n;
    vector<ll> fibo = {1,1};
    while(*(fibo.end()-1)<=n){
        fibo.push_back(*(fibo.end()-2)+*(fibo.end()-1));
    }
    reverse(fibo.begin(),fibo.end());
    vector<ll>::iterator it = fibo.begin();
    vector<ll> ans;
    while(n){
        while(it<fibo.end() && *it>n){
            it++;
        }
        ans.push_back(*it);
        n-=*it;
    }
    reverse(ans.begin(),ans.end());
    for(auto a:ans){
        cout<<a<<" ";
    }
    return 0;
}
