#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
#define ls (p<<1)
#define rs ((p<<1)|1)
int a[N],b[N];
struct node{
  int x,d,tp;
  bool operator < (const node & b) const {
    return d < b.d;
  }
};
int fl[N];
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin>>n;
  priority_queue<node> q;
  for(int i=0;i<n;++i)
    cin>>a[i]>>b[i], q.push({i/2, b[i], 0});
  long long ans=0;
  for(int i=1;i<=n;++i){
    auto [x,d, tp]=q.top(); q.pop();
    while(tp==0 && fl[x]==1){
      x = q.top().x; d=q.top().d; 
      tp=q.top().tp;
      q.pop();
    }
    ans+=d;
    if(fl[x]==0) q.push({x,a[x*2]+a[x*2+1]-d, 1}),fl[x]=1;
    cout<<ans<<" ";
  }
}
