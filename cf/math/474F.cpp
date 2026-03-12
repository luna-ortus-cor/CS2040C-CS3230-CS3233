#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class SparseTable {
private:
    int n, max_log;
    vector<vector<int>> st;
    vector<int> logs;

    int combine(int a, int b) {
        return std::gcd(a, b);
    }

public:
    SparseTable(const vector<int>& a) {
        n = a.size();
        max_log = 32 - __builtin_clz(n);
        st.assign(max_log, vector<int>(n));
        logs.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) logs[i] = logs[i / 2] + 1;

        for (int i = 0; i < n; i++) st[0][i] = a[i];

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = combine(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int L, int R) {
        int j = logs[R - L + 1];
        return combine(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n; cin>>n;
    vector<int> s(n);
    map<int,vector<int>> pos;
    for(int i=0;i<n;i++){
        cin>>s[i];
        pos[s[i]].push_back(i);
    }
    SparseTable spt(s);
    int t;cin>>t;
    while(t--){
        int l,r;cin>>l>>r;
        l--;r--;
        int g=spt.query(l,r);
        int count=0;
        if(pos.count(g)){
            const auto& v=pos[g];
            auto it1=lower_bound(v.begin(),v.end(),l);
            auto it2=upper_bound(v.begin(),v.end(),r);
            count=distance(it1,it2);
        }
        int total_ants=r-l+1;
        cout<<total_ants-count<<"\n";
    }
    return 0;
}
