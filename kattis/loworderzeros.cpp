#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    vector<ll> digits(1000001);
    digits[0]=0;
    digits[1]=1;
    ll temp=1;
    for(int j=2;j<digits.size();j++){
        temp*=j;
        while(temp%10==0){
            temp/=10;
        }
        digits[j]=temp%10;
        temp=temp%1000000000; //but idk why, handles case of n%5==0, else use L((5a+b)!)=2^a*L(a!)*L(b!)
    }
    int f;
    cin>>f;
    while(f!=0){
        cout<<digits[f]<<endl;
        cin>>f;
    }
    return 0;
}
