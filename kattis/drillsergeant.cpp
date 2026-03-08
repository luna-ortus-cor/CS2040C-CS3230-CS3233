#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll hashPair(ll a,ll b,ll N=1e9){
    return a*N+b;
}

ll contribution(ll cat,ll left,ll right, const unordered_set<ll> &dislike){
    bool dl=(left!=-1&&dislike.count(hashPair(left,cat)));
    bool dr=(right!=-1&&dislike.count(hashPair(cat,right)));
    if(dl&&dr)return 3233;
    if(dl)return 323;
    if(dr)return 32;
    return 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n,m,q;
    cin>>n>>m;
    unordered_set<ll> dislike;
    for(int i=0;i<m;i++){
        ll x,y;
        cin>>x>>y;
        dislike.insert(hashPair(x,y));
    }
    set<ll> line;
    unordered_map<int,int> contrib;
    ll ans=0;
    cin>>q;
    while(q--){
        ll d,z;
        cin>>d>>z;
        if(d==1){
            auto it=line.insert(z).first;
            bool hasLeft=(it!=line.begin());
            bool hasRight=(next(it)!=line.end());
            if(hasLeft){
                auto left=prev(it);
                ans-=contrib[*left];
                contrib[*left]=contribution(*left,(left==line.begin()?-1LL:*prev(left)),z,dislike);
                ans+=contrib[*left];
            }
            if(hasRight){
                auto right=next(it);
                ans-=contrib[*right];
                contrib[*right]=contribution(*right,z,(next(right)==line.end()?-1LL:*next(right)),dislike);
                ans+=contrib[*right];
            }
            contrib[z]=contribution(z,(it==line.begin()?-1LL:*prev(it)),(next(it)==line.end()?-1LL:*next(it)),dislike);
            ans+=contrib[z];
        }else{
            auto it=line.find(z);
            bool hasLeft=(it!=line.begin());
            bool hasRight=(next(it)!=line.end());
            if(hasLeft){
                auto left=prev(it);
                ans-=contrib[*left];
                contrib[*left]=contribution(*left,(left==line.begin()?-1LL:*prev(left)),(next(it)==line.end()?-1LL:*next(it)),dislike);
                ans+=contrib[*left];
            }
            if(hasRight){
                auto right=next(it);
                ans-=contrib[*right];
                contrib[*right]=contribution(*right,(it==line.begin()?-1LL:*prev(it)),(next(right)==line.end()?-1LL:*next(right)),dislike);
                ans+=contrib[*right];
            }
            ans-=contrib[z];
            contrib.erase(z);
            line.erase(z);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
