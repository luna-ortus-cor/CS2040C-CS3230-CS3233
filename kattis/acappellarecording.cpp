#include<bits/stdc++.h>
using namespace std;
//idea is to go thru notes, remove dupes, add to vector
//sort vector in asc order (or desc)
//then starting from first note go thru all notes
//ignore curr notes where curr-prev<=diff
//if curr-prev>diff then new recording needed
//so ans++, prev=curr

int main(){
    int n,d,p;cin>>n>>d;
    unordered_map<int,int> um;
    vector<int> v;
    while(cin>>p){
        if(um.contains(p))continue;
        um.emplace(p,1);
        v.push_back(p);
    }
    sort(v.begin(),v.end());
    vector<int>::iterator it=v.begin();
    int curr,prev,ans;prev=*it;ans=1;
    while(it!=v.end()){
        curr=*it;
        it++;
        if(curr-prev<=d)continue;
        prev=curr;ans++;
    }
    cout<<ans<<endl;
    return 0;
}
