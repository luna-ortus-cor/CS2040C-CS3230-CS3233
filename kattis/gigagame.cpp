#include <cstdio>
#include <vector>
using namespace std;

int par[200001];
int depth[200001];
int sink[200001];

int root(int node){
  int temp=node;
  while(par[node]!=node){
    node=par[node];
  }
  return par[temp]=node;
}

bool isCon(int v1, int v2){
  return root(v1)==root(v2);
}

void join(int v1, int v2){
  if(depth[root(v1)]<depth[root(v2)]){
    sink[root(v2)]+=sink[root(v1)];
    par[root(v1)]=root(v2);
  }
  else if(depth[root(v1)]>depth[root(v2)]){
    sink[root(v1)]+=sink[root(v2)];
    par[root(v2)]=root(v1);
  }
  else{
    sink[root(v2)]+=sink[root(v1)];
    par[root(v1)]=root(v2);
    depth[root(v2)]++;
  }
}

int main(){
  int n;
  scanf("%d", &n);
  int a[n], b[n];
  for(int i=0;i<n;i++){
    scanf("%d", &a[i]);
  }
  for(int i=0;i<n;i++){
    scanf("%d", &b[i]);
  }
  int bots[n+1];
  for(int i=1;i<n+1;i++){
    bots[i]=0;
  }
  for(int i=0;i<n;i++){
    bots[b[i]]++;
  }
  for(int i=1;i<n+1;i++){
    par[i]=i;
    depth[i]=1;
    sink[i]=(bots[i]==2)?1:0;
  }
  for(int i=0;i<n;i++){
    if(!isCon(a[i], b[i])){
      join(a[i], b[i]);
    }
  }
  bool yes=true;
  for(int i=1;i<n+1;i++){
    if(sink[i]>1){
      yes=false;
    }
  }
  printf(yes?"YES":"NO");
  return 0;
}
