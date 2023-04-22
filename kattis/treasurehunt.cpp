#include <bits/stdc++.h>

using namespace std;

int main(){
    int R,C;
    cin >> R >> C;
    vector<vector<char>> grid(R,vector<char>(C,'x'));
    vector<vector<int>> visited(R,vector<int>(C,'0'));
    for(int i = 0;i<R;i++){
        for(int j = 0;j<C;j++){
            char temp;
            cin>>temp;
            grid[i][j] = temp;
        }
    }
    char move = 'x';
    int r = 0;
    int c = 0;
    int count = 0;
    while(true){
        if(visited[r][c] == 1){
            cout<<"Lost"<<endl;
            return 0;
        }else{
            visited[r][c]=1;
        }
        move = grid[r][c];
        if(move=='N'){
            r--;
        }else if(move=='S'){
            r++;
        }else if(move=='E'){
            c++;
        }else if(move=='W'){
            c--;
        }else{
            cout<<count<<endl;
            return 0;
        }
        if(0<=r&&r<R&&0<=c&&c<C){
            count++;
        }else{
            cout<<"Out"<<endl;
            return 0;
        }
    }
}
