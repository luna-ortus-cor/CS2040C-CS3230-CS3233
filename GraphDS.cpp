// Graphs are made up of Vertices and Edges that connect those vertices
// Graphs can be undirected or directed
// Graphs can be weighted or unweighted
// Typically we deal with simple graphs i.e. no self loops, and no multiple edges between same pair of vertices
// Number of edges E ranges from 0 to O(V^2)
// An undirected edge e(u,v) is incident with its two vertices u and v, and two vertices u,v are adjacent if they are incident with a common edge e
// Two edges are adjacent if they are incident with a common vertex v
// The degree of a vertex v in an undirected graph is the number of edges incident with v
// A vertex of degree 0 is an isolated vertex
// A subgraph G' of a graph G is a (smaller) graph that contains subsets of vertices and edges of G
// A path of length n in an (undirected) graph G is a sequence of vertices {v0, v1, ..., vn} such that there is an edge e_i between v_i and v_i+1 for all i in [0,n-1]
// If there is no repeated vertex along the path, then it is a simple path
// An undirected graph G is connected if there exists a path between every pair of distinct vertices of G
// An undirected graph C is a connected component of the undirected graph G if:
// 1. C is a subgraph of G
// 2. C is connected
// 3. No connected subgraph of G has C as a subgraph and contains vertices or edges not in C (i.e. C is the maximal subgraph that satisfies 1. and 2.)
// For a directed edge e(u,v), v is adjacent to u, but u is not necessarily adjacent to v
// For a directed graph, the in-degree of a vertex v is the number of edges coming into v
// For a directed graph, the out-degree of a vertex v is the nuumber of edges going out of v
// For a directed graph, a strongly connected graph is a graph where there exists a path between every pair of distinct vertices
// A strongly connected component (SCC) is a subgraph of a directed graph G that is strongly connected
// A cycle is a path that begins and ends with the same vertex
// An acyclic graph is a graph with no cycles
// In an undirected graph, each undirected edge creates a trivial cycle, but it is usually not classified as a cycle
// A directed acyclic graph (DAG) is a directed graph that is acyclic
// A sparse graph is a graph where E << V^2, and a dense graph is a graph where E ~ V^2
// Examples of graphs include trees, complete graphs, bipartite graphs, DAG, and less frequently planar graphs, line graphs, star graphs, wheel graphs

// Tree is a connected graph consisting of V vertices and E=V-1 edges
// Tree has 1 unique path between any pair of vertices
// Trees are usually undirected and unweighted, and acyclic
// Trees are sparse graphs
// Tree with one of its vertices designated as root is a rooted tree
// In a rooted tree, every vertex has a parent, except the root, which has NONE/NULL
// In a rooted tree, every vertex may or may not have children i.e. the vertex may be the parent vertex of another vertex
// In a rooted tree, the ancestors of a vertex are all the vertices contained in the path between the vertex and the root (inclusive)
// In a rooted tree, the descendants of a vertex are all the vertices for which the vertex is an ancestor
// The level of a tree starts from 0 (the root), and the height of a tree is its maximum level
// We can further define additional properties for various trees
// For a binary tree, it is a rooted tree where a vertex has at most two children
// A full binary tree is a binary tree where each non-leaf vertex has exactly two children
// A complete binary tree is a binary tree where each level, except possibly the last, is completely filled, and the last level has vertexes as far left as possible

// A complete graph has V vertices and E=V(V-1)/2=O(V^2) edges i.e. there exists an edge between every pair of distinct vertices
// A complete graph with V vertices is denoted by K_V
// A complete graph is the most dense simple graph

// A bipartite graph is an undirected graph with V vertices that can be partitioned into 2 disjoint sets of vertices of size m and n, V=m+n
// There is no edge between vertices in the same set
// Bipartite graphs do not have odd-length cycles, only even-length cycles (if any)
// A bipartite graph can also be complete, i.e. all m vertices from one disjoint set are connected to all n vertices in the other disjoint set
// When m=n=V/2, the complete bipartite graph has E=O(V^2)

// A DAG is a directed graph with no cycle
// Used in DP problems, has at least one topological sort/order (via slight modification to dfs/bfs)
