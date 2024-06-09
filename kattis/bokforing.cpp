#include<bits/stdc++.h>
using namespace std;
//this is just simple modelling with unordered map
//set is O(1), print is O(1), restart is (effectively) O(1)
//use dummy variable to hold restart value (r)
//if ele in um then set/print as normal
//if ele not in um, then emplace (if set), else print r (if print)
//if restart then um.clear(), set new r

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N,Q;cin>>N>>Q;
    string s;int i,x;
    unordered_map<int,int> um;
    int r=0;
    while(Q--){
        cin>>s;
        if(s=="SET"){
            cin>>i>>x;
            if(um.contains(i))um[i]=x;
            else um.emplace(i,x);
        }else if(s=="PRINT"){
            cin>>i;
            if(!um.contains(i))cout<<r<<"\n";
            else cout<<um[i]<<"\n";
        }else{
            cin>>x;
            r=x;um.clear();
        }
    }
    return 0;
}
