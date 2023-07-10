#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin>>N;
    if(N<99){
        cout<<99<<endl;
        return 0;
    }
    int rem = N%100;
    int a = 99-rem;
    int b = 100-a;
    cout<< N+(a<=b?a:-b)<<endl;
    return 0;
}
