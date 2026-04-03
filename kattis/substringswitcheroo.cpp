#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull char_vals[26];

void init_hash() {
    mt19937_64 rng(42); 
    for(int i=0;i<26;i++)char_vals[i]=rng();
}

void solve(){
    string a,b;
    cin>>a>>b;
    int n=a.size(),m=b.size();
    vector<ull> pref_a(n+1,0),pref_b(m+1,0);
    for(int i=0;i<n;i++)pref_a[i+1]=pref_a[i]+char_vals[a[i]-'a'];
    for(int i=0;i<m;i++)pref_b[i+1]=pref_b[i]+char_vals[b[i]-'a'];
    for(int len=min(n,m);len>=1;len--){
        unordered_set<ull> b_hashes;
        b_hashes.reserve(m-len+1);
        for(int i=0;i<=m-len;i++){
            b_hashes.insert(pref_b[i+len]-pref_b[i]);
        }
        for(int i=0;i<=n-len;i++){
            ull target=pref_a[i+len]-pref_a[i];
            if(b_hashes.count(target)){
                cout<<a.substr(i,len)<<"\n";
                return;
            }
        }
    }
    cout<<"NONE\n";
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    init_hash();
    int n;
    cin>>n;
    while(n--)solve();
    return 0;
}
