#include<bits/stdc++.h>
using namespace std;

//this looks like mincut/maxflow initially but that will TLE (i tried)
//notice however that we can instead thnk about constructing a path of blocked cells
//from topright to bottom left
//if a cell is a wall, it has cost 0 (can be used in path freely)
//if a cell is magic immune, cost inf (cannot be used) and we do not add to our deque
//if a cell is normal, it has cost 1 (use magic spell)
//then we can do 0-1 bfs with deque on this graph, push cost 0 to front and cost 1 to back
//use of bfs guarantees first cell we hit from top right to bottom left is an optimal minimum solution
//note that we are free to use blockings in all 8 directions (rather than the 4 the enemies can use)
const int INF=1e9;
int dr[]={-1,-1,-1,0,0,1,1,1};
int dc[]={-1,0,1,-1,1,-1,0,1};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int R,C;
    while(cin>>R>>C&&(R||C)){
        vector<string> grid(R);
        for(int i=0;i<R;i++)cin>>grid[i];
        vector<int> dist(R*C,INF);
        deque<int> dq;
        auto add_source=[&](int r,int c){
            int idx=r*C+c;
            int cost=(grid[r][c]=='.')?1:(grid[r][c]=='#'?0:INF);
            if(cost<dist[idx]){
                dist[idx]=cost;
                if(cost==0)dq.push_front(idx);
                else dq.push_back(idx);
            }
        };
        for(int c=0;c<C;c++)add_source(0,c);
        for(int r=0;r<R;r++)add_source(r,C-1);
        int ans=-1;
        while(!dq.empty()){
            int u=dq.front();
            dq.pop_front();
            int r=u/C;
            int c=u%C;
            int d=dist[u];
            if(r==R-1||c==0){ans=d;break;}
            for (int i=0;i<8;i++){
                int nr=r+dr[i];
                int nc=c+dc[i];
                if(nr>=0&&nr<R&&nc>=0&&nc<C){
                    int v=nr*C+nc;
                    int cost=(grid[nr][nc]=='.')?1:(grid[nr][nc]=='#'?0:INF);
                    if(cost!=INF){
                        if(dist[u]+cost<dist[v]){
                            dist[v]=dist[u]+cost;
                            if(cost==0)dq.push_front(v);
                            else dq.push_back(v);
                        }
                    }
                }
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
