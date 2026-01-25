#include <bits/stdc++.h>
using namespace std;

bool valid(vector<int>& a){
    int n=a.size();
    vector<int> suffix(n);
    suffix[n-1]=a[n-1];
    for(int i=n-2;i>-1;i--){
        suffix[i]=max(suffix[i+1],a[i]);
    }
    set<int> left;
    left.insert(a[0]);
    for(int j=1;j<n-1;j++){
        auto it=left.upper_bound(a[j]);
        if(it!=left.end()&&suffix[j+1]>*it)return true;
        left.insert(a[j]);
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int k,n,h;
    cin>>k;
    int s=0;
    vector<int> ans;
    for(int i=0;i<k;i++){
        cin>>n;
        vector<int> a;
        while(n--){
            cin>>h;
            a.push_back(h);
        }
        if(valid(a)){
            s++;
            ans.push_back(i+1);
        }
    }
    cout<<s<<"\n";
    for(int i=0;i<s;i++){
        cout<<ans[i]<<"\n";
    }
    return 0;
}
