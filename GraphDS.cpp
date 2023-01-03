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

