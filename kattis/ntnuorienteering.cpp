#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T,C,L,i,j,t,c,s,e;
    cin>>T;
    while(T--){
        cin>>C>>L;
        vector<vector<int>> adj(C,vector<int>(C, 0));
        for(int k=0;k<C*(C-1)/2;k++){
            cin>>i>>j>>t;
            adj[i][j]=t;
            adj[j][i]=t;
        }

        for(int k=0;k<C;k++)
            for(int row=0;row<C;row++)
                for(int col=0;col<C;col++)
                    if(adj[row][k]+adj[k][col]<adj[row][col])
                        adj[row][col]=adj[row][k]+adj[k][col];

        vector<tuple<int,int,int>> lect(L);
        for(int k=0;k<L;k++){
            cin>>c>>s>>e;
            lect[k]={s,e,c};
        }
        sort(lect.begin(),lect.end());

        vector<int> dp(L,1);
        int max_lectures=0;
        for(int curr=0;curr<L;curr++){
            for(int prev=0; prev<curr; prev++){
                auto [s1,e1,c1]=lect[prev];
                auto [s2,e2,c2]=lect[curr];
                if(e1+adj[c1][c2]<=s2)
                    dp[curr]=max(dp[curr],dp[prev]+1);
            }
            max_lectures=max(max_lectures,dp[curr]);
        }
        cout<<max_lectures<<"\n";
    }
    return 0;
}
