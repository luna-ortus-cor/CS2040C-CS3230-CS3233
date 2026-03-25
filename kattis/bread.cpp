#include <bits/stdc++.h>
using namespace std;

int parity(const vector<int>& v,const int N){
    vector<int> visited(N+1,0);
    int cycles=0;
    for(int i=1;i<=N;i++){
        if(visited[i])continue;
        int j=i;
        while(!visited[j]){
            visited[j]=1;
            j=v[j];
        }
        cycles++;
    }
    return (N-cycles)%2;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;cin>>N;
    vector<int> a(N+1),b(N+1);
    for(int i=1;i<=N;i++)cin>>a[i];
    for(int i=1;i<=N;i++)cin>>b[i];
    cout<<(parity(a,N)==parity(b,N)?"Possible":"Impossible");
    return 0;
}
