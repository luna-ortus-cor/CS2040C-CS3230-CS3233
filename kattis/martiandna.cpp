#include <bits/stdc++.h>
using namespace std;

//we keep track of the number of required bases in s
//and also the number of encountered bases in um
//then we just employ a sliding window
//encountered bases can be negative count
//i.e. we encounter more than required
//this allows for potentially shorter substring
//as we shorten the sliding window and remove redundant encounters

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,k,r;
    cin>>n>>k>>r;

    vector<int> v(n);
    for(int i=0;i<n;i++) cin>>v[i];

    unordered_map<int,int> um;
    int s=0;
    for (int i=0;i<r;i++) {
        int a,b;
        cin>>a>>b;
        um[a]=b;
        s+=b;
    }

    int start=0;
    int m=INT_MAX;

    for (int end=0;end<n;end++) {
        if(um.count(v[end])){
            if(um[v[end]]>0) s--;
            um[v[end]]--;
        }
        while(s==0){
            m=min(m,end-start+1);
            if(um.count(v[start])){
                um[v[start]]++;
                if(um[v[start]]>0) s++;
            }
            start++;
        }
    }

    if(m==INT_MAX) cout<<"impossible\n";
    else cout<<m<<"\n";
    return 0;
}
