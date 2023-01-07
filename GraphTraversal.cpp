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
// Use another vector to keep track of predecessor/parent vertex, set predecessor of source vertex to -1
// The sequence of vertices from a vertex u that is reachable from the source vertex s back to s forms the DFS spanning tree
// Explore all vertices = O(V), at each vertex explore all edges, total edges = E, so O(E) => total time complexity = O(V+E), only if use AL

// Breadth-First Search (BFS), O(V+E)
// Takes one input parameter, the source vertex s
// Uses a queue to traverse as broadly as possible before going deeper
// For a vertex u with n neighbours, BFS will visit v_1, v_2, ..., v_n in order, before visiting the immediate neighbours of v_1, then v_2, and so on
// To avoid problem of cycles (whereby vertices are visited over and over again), keep track of visited status with a vector, only visit if not visited yet
// No need to store predecessor/parent vertex as no backtracking involved
// The sequence of vertices from a vertex u that is reachable from the source vertex s back to s forms the BFS spanning tree
// The BFS spanning tree is also the SSSP spanning tree for unweighted graph
// Explore all vertices = O(V), at each vertex explore all edges, total edges = E, so O(E) => total time complexity = O(V+E), only if use AL

// 7


