#include<bits/stdc++.h>
using namespace std;

//look up Dilworth Theorem also
int main(){
    int t; 
    cin>>t;
    while(t--){
        vector<pair<int,int>> v;
        int m,w,h;
        cin>>m;
        for(int i=0;i<m;i++){
            cin>>w>>h;
            v.push_back({w,h});
        }
        sort(v.begin(),v.end(),[](const pair<int,int>& a,const pair<int,int>& b){
            if(a.first!=b.first)return a.first>b.first;
            return a.second<b.second;
        });
        vector<int> chains;
        for(auto p:v){
            auto it=upper_bound(chains.begin(),chains.end(),p.second);
            if(it==chains.end()){
                chains.push_back(p.second);
            }else{
                *it=p.second;
            }
        }
        cout<<chains.size()<<"\n";
    }
    return 0;
}
