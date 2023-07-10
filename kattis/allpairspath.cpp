#include <bits/stdc++.h>
using namespace std;
#define inf 10000000
//all pair shortest path is just FW, O(V^3)

int main(){
    int n,m,q;
    cin>>n>>m>>q;
    while(n){
        vector<vector<int>> vvi(n,vector<int>(n,inf));
        for(int i=0;i<m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            vvi[u][v] = w<vvi[u][v]?w:vvi[u][v];
        }
        for(int i = 0;i<n;i++){
            vvi[i][i] = 0;
        }
        //normal FW
        for(int k = 0;k<n;k++){
            for(int i = 0;i<n;i++){
                for(int j = 0;j<n;j++){
                    //possible that vvi[i][k]==inf,0>vvi[k][j]>-inf due to -ve cycle
                    //which will lead to 0<vvi[i][j]<inf even when i j are not reachable
                    if(vvi[i][j]>vvi[i][k]+vvi[k][j] && vvi[i][k]<inf && vvi[k][j]<inf){
                        vvi[i][j] = vvi[i][k] + vvi[k][j];
                    }
                }
            }
        }
        //handle -ve cycle
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++){
                for(int k = 0;k<n;k++){
                    if(vvi[k][k]<0 && vvi[i][k]!=inf && vvi[k][j]!=inf){
                        vvi[i][j] = -inf;
                    }
                }
            }
        }
        for(int i = 0;i<q;i++){
            int u,v;
            cin>>u>>v;
            if(vvi[u][v]==inf){
                cout<<"Impossible"<<endl;
            }else if(vvi[u][v]==-inf){
                cout<<"-Infinity"<<endl;
            }else{
                cout<<vvi[u][v]<<endl;
            }
        }
        cout<<endl;
        cin>>n>>m>>q;
    }
    return 0;
}
