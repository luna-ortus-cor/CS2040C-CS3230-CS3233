#include<bits/stdc++.h>
using namespace std;

//use |x1-x2|+|y1-y2|=max(|(x1+y1)-(x2+y2)|,|(x1-y1)-(x2-y2)|)
//equivalent |dx|+|dy|=max(|dx+dy|,|dx-dy|)
//if dx,dy same sign, then |dx|+|dy|=|dx+dy|
//if dx,dy diff sign, then |dx|+|dy|=|dx-dy|
//then just precalculate dist from existing stands
//using multi-source BFS (in O(wh))
//then to check, iterate through grid and take all
//coords where exising dist>=dist to check
//the max(x+y),min(x+y),max(x-y),min(x-y) over all pairs
//lastly just need to check that some pair exists
//so that their dist is >=dist to check as well
//using above identity the max dist achievable between
//all of these pairs is then (abstracting out the abs)
//max(Smax-Smin,Dmax-Dmin)
//total runtime O(wh log 2000)

bool check(const int dist, const int w, const int h, const vector<vector<int>>& d){
    int Smax=-1e9,Smin=1e9,Dmax=-1e9,Dmin=1e9;
    for(int x=0;x<w;x++){
        for(int y=0;y<h;y++){
            if(d[x][y]>=dist){
                Smax=max(Smax,x+y);
                Smin=min(Smin,x+y);
                Dmax=max(Dmax,x-y);
                Dmin=min(Dmin,x-y);
            }
        }
    }
    return max(Smax-Smin,Dmax-Dmin)>=dist;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t,n,w,h;
    cin>>t;
    while(t--){
        cin>>n>>w>>h;
        vector<vector<int>> d(w,vector<int>(h,1e9));
        queue<tuple<int,int,int>> q;
        int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
        for(int i=0;i<n;i++){
            int x,y;
            cin>>x>>y;
            q.push({x,y,0});
        }
        while(!q.empty()){
            auto [x,y,dist]=q.front();q.pop();
            if(d[x][y]!=1e9)continue;
            d[x][y]=dist;
            for(int i=0;i<4;i++){
                int nx=x+dx[i],ny=y+dy[i];
                if(0<=nx&&nx<w&&0<=ny&&ny<h&&d[nx][ny]==1e9){
                    q.push({nx,ny,dist+1});
                }
            }
        }
        int lo=0,hi=2000,ans=0;
        while(lo<=hi){
            int mid=(lo+hi)/2;
            if(check(mid,w,h,d)){
                ans=mid;
                lo=mid+1;
            }else hi=mid-1;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
