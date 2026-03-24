#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll N;
    cin>>N;
    cout<<"2\n";
    if(N==8)cout<<"4 4";
    else{
        if(N%3==1)cout<<4<<" "<<N-4;
        if(N%3==2)cout<<8<<" "<<N-8;
        if(N%3==0)cout<<6<<" "<<N-6;
    }
    return 0;
}
