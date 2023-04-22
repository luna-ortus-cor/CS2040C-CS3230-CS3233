#include <bits/stdc++.h>

using namespace std;

bool checkbounds(int r, int c, int rr, int cc){
    if(rr<0||cc<0||rr>=r||cc>=c){
        return false;
    }
    return true;
}

//we maintain one visited array and use it to fill it in "UFDS" fashion, using idx to indicate contiguous groups
int main(){
    int r,c;
    cin>>r>>c;
    vector<vector<int>> m(r,vector<int>(c,-1));
    vector<vector<int>> visited(r,vector<int>(c,-1));
    for(int i=0;i<r;i++){
        for(int j =0;j<c;j++){
            char c;
            cin>>c;
            m[i][j]=c-'0';
        }
    }
    int dirr[4]= {1,-1,0,0};
    int dirc[4]= {0,0,-1,1};
    int n;
    cin>>n;
    int idx = 0;
    
    for(int i=0;i<n;i++){
        int r1,c1,r2,c2;
        cin>>r1>>c1>>r2>>c2;
        r1--; c1--; r2--; c2--;
        if(m[r1][c1]!=m[r2][c2]){
            cout<<"neither"<<endl;
            continue;
        }
        
        queue<pair<int,int>> q;
        q.push(make_pair(r1,c1));
        while(!q.empty()){
            int rr=q.front().first;
            int cc = q.front().second;
            q.pop();
            
            if(visited[rr][cc]!=-1){
                continue;
            }else{
                visited[rr][cc]=idx;
            }
            for(int j =0;j<4;j++){
                if(checkbounds(r,c,rr+dirr[j],cc+dirc[j])&&visited[rr+dirr[j]][cc+dirc[j]]==-1 && m[rr+dirr[j]][cc+dirc[j]]==m[rr][cc]){
                    q.push(make_pair(rr+dirr[j],cc+dirc[j]));
                }
            }
        }
        idx++;
        if(visited[r1][c1]==visited[r2][c2]&&visited[r1][c1]!=-1){
            if(m[r1][c1]==1){
                cout<<"decimal"<<endl;
            }else{
                cout<<"binary"<<endl;
            }
        }else{
            cout<<"neither"<<endl;
        }
    }
}
