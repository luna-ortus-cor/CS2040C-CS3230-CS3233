// Binary Tree Traversal
// Starts at root, or if root not given, designate any vertex as the root
// At each vertex, either visit the current vertex, the left vertex, or the right vertex, in any order
// This gives rise to the preorder, inorder, postorder traversals
// A binary tree is acyclic; there are no non-trivial cycles

// For a general graph however, there is no root vertex, we are not constrained to only 2 or fewer neighbours per vertex, we may have non-trivial cycles
// Typically need to pick a source vertex s for starting point of traversal

// Depth-First Search (DFS), O(V+E)
// Takes one input parameter, the source vertex s
// Uses recursion (implicit stack) to traverse as deeply as possible before backtracking
// For a vertex u with n neighbours, DFS will visit v_1, recursively explore all reachable vertices from v_1, and backtrack to vertex u
// The same thing happens for v_2, v_3, ..., v_n until all neighbours have been traversed
// To avoid problem of cycles (whereby vertices are visited over and over again), keep track of visited status with a vector, only visit if not visited yet
// When run out of new vertices to explore, backtrack to previous vertex
// Use another vector to keep track of predecessor/parent vertex, set predecessor of source vertex to -1, i.e. vector<int> p
// The sequence of vertices from a vertex u that is reachable from the source vertex s back to s forms the DFS spanning tree
// Explore all vertices = O(V), at each vertex explore all edges, total edges = E, so O(E) => total time complexity = O(V+E), only if use AL

// Breadth-First Search (BFS), O(V+E)
// Takes one input parameter, the source vertex s
// Uses a queue to traverse as broadly as possible before going deeper
// For a vertex u with n neighbours, BFS will visit v_1, v_2, ..., v_n in order, before visiting the immediate neighbours of v_1, then v_2, and so on
// To avoid problem of cycles (whereby vertices are visited over and over again), keep track of visited status with a vector, only visit if not visited yet
// No need to store predecessor/parent vertex as no backtracking involved, but we may for ease of printing out traversal path, i.e. vector<int> p
// The sequence of vertices from a vertex u that is reachable from the source vertex s back to s forms the BFS spanning tree
// The BFS spanning tree is also the SSSP spanning tree for unweighted graph
// Explore all vertices = O(V), at each vertex explore all edges, total edges = E, so O(E) => total time complexity = O(V+E), only if use AL

// Example use cases of DFS/BFS: 1. Reachability test, 2. Printing traversal path, 3. Identifying/labelling/counting connected components of undirected graphs,
// 4. Detecting if graph is cyclic, 5. Topological sort (only on DAG), 6. Bipartite graph checker, 7. Find cut vertices and bridge, 8. Find SCC, 9. 2-SAT checker

// To check if vertex s and vertex t are reachable from each other, call DFS(s) or BFS(s), check if visited[t] is visited; this is O(V+E)
// To print out traversal path, we set p[v]=u each time we traverse from vertex u to vertex v, to find traversed path from vertex s to vertex t, call DFS(s) or BFS(s),
// then backtrack(t), where (recursively)
void backtrack(t){
    if(t==-1) break;
    backtrack(p[t]);
    cout<<t<<endl;}
// or (iteratively), 
void backtrack(t){
    list<int> vertices;
    while(t!=-1){
        vertices.push_front(t);
        t=p[t];}
    for(auto v:vertices){
        cout<<v<<endl;}}
// This is O(V+E) for DFS/BFS and O(V) for backtrack
// Identifying connected components (i.e. enumerate all vertices reachable from vertex s) in an undirected graph can be done by calling DFS(s) or BFS(s) 
// and enumerate all vertex v that are visited; this forms 1 connected component (CC) and is O(V+E) for DFS/BFS and O(V) for checking visited array
// Counting number of CCs, O(V+E):
int main(){
  int numv; //number of vertices
  int cc = 0;
  vector<int> visited(numv,0);
  for(int i=0;i<numv;i++){
    if(visited[i]==0){
      cc++;
      DFS(i); //either this
      BFS(i); //or this
    }
  }
  cout<<cc<<endl;
  // possible to modify DFS/BFS if want to label which vertex in which cc
}
// To detect cycle using DFS, modify visited array to keep track of: unvisited (vertex unexplored), explored (vertex visited but have not visited all neighbours), 
// and visited (vertex and neighbours all visited, DFS is about to backtrack to predecessor)
// If DFS at vertex x and encounters vertex y, where visited[y] is explored, then cycle exists as vertex y from unvisited->explored, 
// but able to reach vertex x from vertex y, and from vertex x to vertex y again
// This DFS method works for both directed and undirected graphs. In particular, for undirected graph, we do not need explored, only need check for visited or not
// This method will not work for BFS on directed graphs
// For BFS cycle detection on undirected graphs, just check if vertex has been visited or not, i.e.
// From vertex x, check neighbour vertex y. If y is visited and x does not have y as a predecessor/parent, then there is a cycle
// Alternatively for directed graphs, use either BFS or DFS to check if there is a topological sort, if there isn't then there is a cycle
// To perform topological sort on a DAG, we can use either DFS or BFS. Topological sort is a linear ordering of the DAG's vertices in which each vertex comes before
// all vertices to which it has outbound edges
// Every DAG has at least one topological sorts/orderings
// For DFS:
int main(){
    int numv; //number of vertices
    vector<int> visited(numv,0);
    vector<int> topo;
    for(int i=0;i<numv;i++){
        if(visited[i]==0){
            DFS(i);
            topo.push_back(i);
        }
    }
    reverse(topo.begin(),topo.end());
    for(auto v:topo){
        cout<<v<<endl;
    }
}
// For BFS: Kahn's Algorithm
int main(){
    int numv;
    vector<vector<int>> AL; //adjacency list (or AM or EL, just change how neighbours are obtained)
    queue<int> Q;
    list<int> topo;
    visited<int>(numv,0);
    vector<int> source(numv,0);
    for(int i=0;i<numv;i++){ //add vertices with no incoming edge to Q
        for(int j:AL[i]){
            source[j]++;
        }
    }
    for(int i=0;i<numv;i++){
        if(source[i]==0){
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int u=Q.front();
        topo.push_back(u);
        visited[u]=1;
        Q.pop();
        vector<int> blank;
        for(int v:AL[u]){
            if(source[v]>0){
                v--;
            }
            if(source[v]==0&&visited[v]==0){
                visited[v]=1;
                Q.push(v);
            }
        }
        AL[u]=blank;
    }
    for(auto v:topo){
        cout<<v<<endl;
    }
}             
// Bipartite graph checker: use BFS, start from the source and colour source A. Then, colour all of its neighbours colour B. Continue BFS while alternating colours
// If at any point we find neighbour that is already coloured (i.e. visited) and is same colour as current vertex, then graph is not bipartite
// Typically bipartite graphs are undirected
bool isbipartite(){
    int numv;
    vector<vector<int>> AL; //adjacency list (or AM or EL, just change how neighbours are obtained)
    queue<pair<int,int>> Q;
    visited<int>(numv,-1);
    for(int i=0;i<numv;i++){
        if(visited[i]==-1){
            Q.push(make_pair(i,0));
            visited[i]=0;
            while(!Q.empty()){
                int u=Q.front().first;
                int col = Q.front().second;
                int newcol=(col+1)%2;
                Q.pop();
                for(int v:AL[u]){
                    if(visited[v]==-1){
                        visited[v]=newcol;
                        Q.push(make_pair(v,newcol));
                    }else if(visited[v]==col){
                        return false;
                    }else{
                        continue;
                    }
                }
            }
        }
    }
    return true;
}
// We can also check if a graph is bipartite using DFS instead, using a similar logic to BFS, but will need to modify the DFS method itself
bool DFS(int s){
    vector<int> neighbours = AL[s];
    for(auto v:neighbours){
        if(visited[v]==-1){
            visited[v]=(visited[s]+1)%2;
            DFS(v);
        }else if(visited[s]==visited[v]){
            return false;
        }else{
            continue;
        }
    }
    return true;
}
bool isbipartite(){
    int numv;
    vector<vector<int>> AL; //adjacency list (or AM or EL, just change how neighbours are obtained)
    visited<int>(numv,-1);
    for(int i=0;i<numv;i++){
        if(visited[i]==-1){
            visited[i]=0;
            if(DFS(i)==false){
                return false;
            }
        }
    }
    return true;
}
// To find cut vertices and bridge, we need to modify the DFS/BFS algorithm
// A cut vertex (aka articulation point), is a vertex of an undirected graph whereby removing the vertex would disconnect the graph
// Similarly, a bridge is an edge of an undirected graph whereby removing the edge would disconnect the graph

// TODO cut vertice and bridge implementation
// TODO find SCC implementation
// TODO 2-SAT implementation

// code for DFS/BFS
// TODO: numv,AL/AM/EL,visited,Q should be declared outside function
void DFS(int s){
    int numv; //number of vertices
    vector<vector<int>> AL; //adjacency list (or AM or EL, just change how neighbours are obtained)
    vector<int> visited(numv,0);
    if(visited[s]==0){
        vector<int> neighbours = AL[s];
        visited[s]=1;
        for(auto v:neighbours){
            if(visited[v]==0){
                DFS(v);
            }
        }
    }else{
        return;
    }
}

void BFS(int s){
    int numv; //number of vertices
    vector<vector<int>> AL; //adjacency list (or AM or EL, just change how neighbours are obtained)
    vector<int> visited(numv,0);
    queue<int> Q;
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        for(int v:AL[u]){
            if(visited[v]==0){
                visited[v]=1;
                Q.push(v);
            }
        }
    }
}
