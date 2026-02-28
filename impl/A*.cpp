#include <bits/stdc++.h>
using namespace std;

int numv;
vector<vector<pair<int,int>>> AL;  // {neighbor, weight}
vector<int> g;      // distance from source
vector<int> p;      // predecessor
vector<int> closed; // visited / finalized

int h(int v){
    // User-defined heuristic
    // Example: return 0;  // reduces A* to Dijkstra
    return 0;
}

void Astar(int s, int t){

    g.assign(numv, INT_MAX);
    p.assign(numv, -1);
    closed.assign(numv, 0);

    // Min-heap: {f(v), vertex}
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    g[s] = 0;
    pq.push({h(s), s});  // f(s) = g(s) + h(s)

    while(!pq.empty()){

        int u = pq.top().second;
        pq.pop();

        if(closed[u]) continue;
        closed[u] = 1;

        if(u == t) break;  // stop when target reached

        for(auto edge : AL[u]){
            int v = edge.first;
            int weight = edge.second;

            if(closed[v]) continue;

            if(g[u] + weight < g[v]){
                g[v] = g[u] + weight;
                p[v] = u;
                int f = g[v] + h(v);
                pq.push({f, v});
            }
        }
    }
}

void backtrack(int t){
    list<int> path;
    while(t != -1){
        path.push_front(t);
        t = p[t];
    }
    for(auto v : path){
        cout << v << endl;
    }
}
