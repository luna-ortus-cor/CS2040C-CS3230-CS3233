#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
#define ls (p<<1)
#define rs ((p<<1)|1)
int f[N<<2][10][10][2][2],sum[10][10],tag[N<<2];
int a[N];
void pushup(int p){
  for(int i=0;i<10;++i)
    for(int j=0;j<=i;++j)
      for(int x=0;x<2;++x)
        for(int y=0;y<2;++y)
          f[p][i][j][x][y]=f[ls][i][j][x][y]+f[rs][i][j][x][y];  
}
int g[2][2];
inline void upt(int p,int x){
  for(int i=0;i<10;++i)
    for(int j=0;j<=i;++j){
      int bx=(x>>i)&1, by=(x>>j)&1;
      for(int u=0;u<2;++u)
        for(int v=0;v<2;++v)
          g[u][v]=f[p][i][j][u^bx][v^by];
      for(int u=0;u<2;++u)
        for(int v=0;v<2;++v)
          f[p][i][j][u][v]=g[u][v];
    }
    tag[p]^=x;
}
void pushdown(int p){
  if(tag[p]){
    upt(ls,tag[p]),upt(rs,tag[p]);
    tag[p]=0;
  }
}
void query(int p,int l,int r,int ql,int qr){
  if(ql<=l&&r<=qr){
    for(int i=0;i<10;++i)
      for(int j=0;j<=i;++j)
        sum[i][j]+=f[p][i][j][1][1];
    return;
  }
  pushdown(p);
  int mid=(l+r)>>1;
  if(ql<=mid) query(ls,l,mid,ql,qr);
  if(mid<qr) query(rs,mid+1,r,ql,qr);
 // pushup(p);
}
void upt(int p,int l,int r,int ql,int qr,int x){
  if(ql<=l&&r<=qr) return upt(p, x);
  pushdown(p);
  int mid=(l+r)>>1;
  if(ql<=mid) upt(ls,l,mid,ql,qr,x);
  if(mid<qr) upt(rs,mid+1,r,ql,qr,x);
  pushup(p);
}
void build(int p,int l,int r){
  if(l==r){
    for(int i=0;i<10;++i)
      for(int j=0;j<=i;++j){
        int x=(a[l]>>i)&1, y=(a[l]>>j)&1;
        f[p][i][j][x][y]=1;
      }
      return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid);
  build(rs,mid+1,r);
  pushup(p);
}
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n,q;
  cin>>n>>q;
  for(int i=1;i<=n;++i)
    cin>>a[i];
  build(1,1,n);
  while(q--){
    int op,l,r,x;
    cin>>op>>l>>r;
    if(op==1) cin>>x, upt(1,1,n,l,r,x);
    else{
      long long ans=0;
      for(int i=0;i<10;++i)
        for(int j=0;j<=i;++j)
          sum[i][j]=0;
      query(1,1,n,l,r);
      for(int i=0;i<10;++i)
        for(int j=0;j<=i;++j)
          ans+=(1ll<<i)*(1ll<<j)*(i==j?1ll:2ll)*sum[i][j];
      cout<<ans<<"\n";
    }
  }
}
