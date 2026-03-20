#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll L;
ll adj[14][14];
vector<ll> table[1<<14][14];

void dfs_left(int u,int mask,int count,ll current_l){
    if (count==N/2+1){
        table[mask][u].push_back(current_l);
        return;
    }
    for(int v=1;v<N;v++)
        if(!(mask&(1<<v)))
            if(current_l+adj[u][v]<L)
                dfs_left(v,mask|(1<<v),count+1,current_l+adj[u][v]);
}

bool dfs_right(int u,int mask,int count,ll current_l){
    if(count==N-N/2+1){
        int target_mask=(((1<<N)-1)^mask)|(1<<0)|(1<<u);
        ll target_l=L-current_l;
        auto& v=table[target_mask][u];
        return binary_search(v.begin(),v.end(),target_l);
    }
    for(int v=1;v<N;v++)
        if(!(mask&(1<<v)))
            if(current_l+adj[u][v]<L)
                if(dfs_right(v,mask|(1<<v),count+1,current_l+adj[u][v]))return true;
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>N>>L;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            cin>>adj[i][j];
    if(N==2){
        if(adj[0][1]+adj[1][0]==L)cout<<"possible";
        else cout<<"impossible";
        return 0;
    }
    dfs_left(0,1,1,0);
    for(int i=0;i<(1<<N);i++)
        for(int j=0;j<N;j++)
            if(!table[i][j].empty())sort(table[i][j].begin(),table[i][j].end());
    if(dfs_right(0,1,1,0))cout<<"possible";
    else cout<<"impossible";
    return 0;
}
