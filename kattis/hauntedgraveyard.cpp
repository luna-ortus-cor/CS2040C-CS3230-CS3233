#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
    int W,H;
    while(cin>>W>>H){
        if(!W&&!H)break;
        vector<vector<int>> gy(W,vector<int>(H,1));
        int G;cin>>G;
        for(int i=0;i<G;i++){
            int X,Y;
            cin>>X>>Y;
            gy[X][Y]=INF;
        }
        int E;cin>>E;
        vector<vector<int>> holes(W,vector<int>(H,0));
        vector<vector<pair<int,int>>> to(W,vector<pair<int,int>>(H));
        for(int i=0;i<E;i++){
            int X1,Y1,X2,Y2,T;
            cin>>X1>>Y1>>X2>>Y2>>T;
            gy[X1][Y1]=T;
            holes[X1][Y1]=1;
            to[X1][Y1]={X2,Y2};
        }
        vector<int> dist(W*H,INF);
        dist[0]=0;
        for(int i=0;i<W*H-1;i++){
            for(int x=0;x<W;x++){
                for(int y=0;y<H;y++){
                    if(dist[x*H+y]==INF||gy[x][y]==INF)continue;
                    if(x==W-1&&y==H-1)continue;
                    if(holes[x][y]){
                        auto [nx,ny]=to[x][y];
                        dist[nx*H+ny]=min(dist[nx*H+ny],dist[x*H+y]+gy[x][y]);
                    }else{
                        for(int j=0;j<4;j++){
                            int nx=x+dx[j],ny=y+dy[j];
                            if(nx>=0&&nx<W&&ny>=0&&ny<H){
                                dist[nx*H+ny]=min(dist[nx*H+ny],dist[x*H+y]+gy[x][y]);
                            }
                        }
                    }
                }
            }
        }
        bool negcycle=false;
        for(int x=0;x<W;x++){
            for(int y=0;y<H;y++){
                if(dist[x*H+y]==INF||gy[x][y]==INF)continue;
                if(x==W-1&&y==H-1)continue;
                if(holes[x][y]){
                    auto [nx,ny]=to[x][y];
                    if(dist[x*H+y]+gy[x][y]<dist[nx*H+ny])negcycle=true;
                }else{
                    for(int j=0;j<4;j++){
                        int nx=x+dx[j],ny=y+dy[j];
                        if(nx>=0&&nx<W&&ny>=0&&ny<H){
                            if(dist[x*H+y]+gy[x][y]<dist[nx*H+ny])negcycle=true;
                        }
                    }
                }
            }
        }
        if(negcycle)cout<<"never"<<"\n";
        else if(dist[W*H-1]==INF)cout<<"impossible"<<"\n";
        else cout<<dist[W*H-1]<<"\n";
    }
    return 0;
}
