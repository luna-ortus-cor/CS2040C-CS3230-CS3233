#include <bits/stdc++.h>
using namespace std;

//straightforward, just index a vector with the company indexes
//and values as the addresses
//then just simulate update of values if operation 1
//and calculating absolute value between values at 2 indices if operation 2

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,q,a,b,c;
    cin>>n>>q;
    vector<int> v;
    for(int i=0;i<n;i++){
        cin>>a;
        v.push_back(a);
    }
    while(q--){
        cin>>a;
        if(a==1){
            cin>>b>>c;
            v[b-1]=c;
        }else{
            cin>>b>>c;
            cout<<abs(v[b-1]-v[c-1])<<"\n";
        }
    }
    return 0;
}
