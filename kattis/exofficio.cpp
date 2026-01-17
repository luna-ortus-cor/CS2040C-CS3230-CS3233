#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int dr[]={0,0,1,-1};
    int dc[]={-1,1,0,0};
    int r,c;
    cin>>r>>c;
    //initially all walls present
    //each wall unique by taking a cell r,c
    //and looking at the wall below and to the right
    vector<vector<vector<int>>> wall(r+1,vector<vector<int>>(c+1,vector<int>(2,1)));
    vector<vector<int>> d(r+1,vector<int>(c+1,-1));
    int src_r=r/2+1;
    int src_c=c/2+1;
    //we will BFS flood fill from the center
    //this will minimize the maximum gathering time
    //at each BFS step, we remove a wall from a "known"
    //cell connecting it to an "unknown" cell
    //this preserves the "exactly one way to travel" condition
    queue<pair<int,int>> q;
    q.push(make_pair(src_r,src_c));
    d[src_r][src_c]=0;
    //case where one or both of r,c even
    //then we initialize with all the "center" cells
    if(r%2==0&&c%2==0){
        q.push(make_pair(src_r-1,src_c));
        q.push(make_pair(src_r,src_c-1));
        q.push(make_pair(src_r-1,src_c-1));
        wall[src_r][src_c-1][1]=0;
        wall[src_r-1][src_c-1][0]=0;
        wall[src_r-1][src_c][0]=0;
        d[src_r][src_c-1]=0;
        d[src_r-1][src_c-1]=0;
        d[src_r-1][src_c]=0;
    }else if(r%2==0){
        q.push(make_pair(src_r-1,src_c));
        wall[src_r-1][src_c][0]=0;
        d[src_r-1][src_c]=0;
    }else if(c%2==0){
        q.push(make_pair(src_r,src_c-1));
        wall[src_r][src_c-1][1]=0;
        d[src_r][src_c-1]=0;
    }
    while(!q.empty()){
        auto [row,col]=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            auto nr=row+dr[i];
            auto nc=col+dc[i];
            if(nr<1||nc<1||nr>r||nc>c)continue;
            if(d[nr][nc]!=-1)continue;
            d[nr][nc]=d[row][col]+1;
            q.push(make_pair(nr,nc));
            if(row==nr){
                wall[row][min(col,nc)][1]=0;
            }else if(col==nc){
                wall[min(row,nr)][col][0]=0;
            }
        }
    }
    //we can take row,col directly from wall
    //since we use min above based on assignment
    //of walls to cells
    for(int row=0;row<r+1;row++){
        if(row==0){
            for(int col=0;col<2*c;col++){
                if(col%2==0)cout<<" ";
                else cout<<"_";
            }
            cout<<"\n";
        }else{
            for(int col=1;col<=2*c+1;col++){
                if(col==1)cout<<"|";
                else if(col==2*c+1)cout<<"|\n";
                else{
                    if(col%2==0){
                        if(row==r)cout<<"_";
                        else if(wall[row][col/2][0])cout<<"_";
                        else cout<<" ";
                    }else{
                        if(wall[row][(col-1)/2][1])cout<<"|";
                        else cout<<" ";
                    }
                }
            }
        }
    }
    return 0;
}
