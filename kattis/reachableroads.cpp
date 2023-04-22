#include <iostream>
#include <vector>

using namespace std;

int find(vector<int> &conn, int i) {
    if(conn[i] < 0) {
        return i;
    }

    conn[i] = find(conn, conn[i]);
    return conn[i];
}

void join(vector<int>& conn, int a, int b) {
    a = find(conn, a);
    b = find(conn, b);

    if(a == b) {
        return;
    }

    conn[b] = a;
}

int main() {
    int cases;
    cin >> cases;

    vector<int> conn;

    while(cases--) {
        // Read in input
        int cities, roads;
        cin >> cities >> roads;

        // Clear old roads
        conn.clear();
        conn.resize(cities, -1);

        // Connect each set of roads
        for(int i = 0; i < roads; i++) {
            int r1, r2;
            cin >> r1 >> r2;
            join(conn, r1, r2);
        }

        // Count the roads needed
        int extras = 0;
        for(int i = 1; i < cities; i++) {
            if(find(conn, 0) != find(conn, i)) {
                join(conn, 0, i);
                extras++;
            }
        }
        cout << extras << endl;
    }
}

//above uses UFDS method
//below is BFS method to count number of CC and -1
/*
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i = 0;i<n;i++){
        int m;
        cin>>m;
        vector<int> visited(m,0);
        vector<vector<int>> AL(m,vector<int>());
        int r;
        cin>>r;
        for(int j=0;j<r;j++){
            int a,b;
            cin>>a>>b;
            AL[a].push_back(b);
            AL[b].push_back(a);
        }
        int count = 0;
        for(int k = 0;k<m;k++){
            if(visited[k]==0){
                count++;
            }
            queue<int> q;
            q.push(k);
            while(!q.empty()){
                int idx = q.front();
                q.pop();
                if(visited[idx]==1){
                    continue;
                }else{
                    visited[idx]=1;
                }
                for(int c:AL[idx]){
                    if(visited[c]==0){
                        q.push(c);
                    }
                }
            }
        }
        cout<<count-1<<endl;
    }
    return 0;
}
*/
