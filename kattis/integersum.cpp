#include<bits/stdc++.h>
using namespace std;
#define ls (p<<1)
#define rs ((p<<1)|1)
const int N=60000;
int a[105],f[N],ct[105][10],pw[100];
int cnt[N][10];
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin>>n;
  pw[0]=1;
  for(int i=1;i<=10;++i) pw[i]=pw[i-1]*3;
  for(int i=0;i<pw[10];++i){
    for(int j=1;j<10;++j)
      cnt[i][j]=cnt[i/3][j-1];
    cnt[i][0]=i%3;
  }
  for(int i=1;i<=n;++i){
    cin>>a[i];
    int x=a[i];
    if(x==0) ct[i][0]=1;
    while(x) ct[i][x%10]++,x/=10;
    int fl=0;
    for(int j=0;j<10;++j)
      if(ct[i][j]>2) fl=1;
    if(fl) continue;
    int state=0;
    for(int j=0;j<10;++j)
      state+=pw[j]*ct[i][j];
    for(int j=pw[10]-1;j>=0;--j){
      fl=1;
      for(int k=0;k<10;++k)
        if(cnt[j][k]<ct[i][k]) fl=0;
      if(fl) f[j]=max(f[j],f[j-state]+a[i]);
    }
  }      
  int ans=0;
  for(int j=0;j<pw[10];++j) ans=max(ans,f[j]);
  cout<<ans<<"\n";
}
