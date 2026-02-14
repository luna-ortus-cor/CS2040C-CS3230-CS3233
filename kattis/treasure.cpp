#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
int dr[]={-1,1,0,0};
int dc[]={0,0,-1,1};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N,M,K;
    cin>>N>>M>>K;
    vector<string> grid(N);
    int sr,sc,tr,tc;
    for(int i=0;i<N;i++) {
        cin>>grid[i];
        for(int j=0;j<M;j++){
            if(grid[i][j]=='S'){sr=i;sc=j;}
            if(grid[i][j]=='G'){tr=i;tc=j;}
        }
    }
    vector<vector<vector<int>>> dist(N,vector<vector<int>>(M,vector<int>(K+1,INF)));
    deque<tuple<int,int,int>> dq;
    dist[sr][sc][K]=1;
    dq.push_front({sr,sc,K});
    while(!dq.empty()){
        auto [r,c,k]=dq.front();dq.pop_front();
        if(r==tr&&c==tc){
            cout<<dist[r][c][k]<<"\n";
            return 0;
        }
        for(int i=0;i<4;i++) {
            int nr=r+dr[i],nc=c+dc[i];
            if(nr<0||nr>=N||nc<0||nc>=M||grid[nr][nc]=='#')continue;
            int cost=(grid[nr][nc]=='F'?2:(grid[nr][nc]=='M'?3:1));
            if(grid[nr][nc]=='G')cost=1;
            if(k>=cost){
                if(dist[nr][nc][k-cost]>dist[r][c][k]){
                    dist[nr][nc][k-cost]=dist[r][c][k];
                    dq.push_front({nr,nc,k-cost});
                }
            }
            if(K>=cost){
                if(dist[nr][nc][K-cost]>dist[r][c][k]+1) {
                    dist[nr][nc][K-cost]=dist[r][c][k]+1;
                    dq.push_back({nr,nc,K-cost});
                }
            }
        }
    }
    cout<<-1<<"\n";
    return 0;
}
