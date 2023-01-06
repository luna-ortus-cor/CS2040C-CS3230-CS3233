// Binary Tree Traversal
// Starts at root, or if root not given, designate any vertex as the root
// At each vertex, either visit the current vertex, the left vertex, or the right vertex, in any order
// This gives rise to the preorder, inorder, postorder traversals
// A binary tree is acyclic; there are no non-trivial cycles

// For a general graph however, there is no root vertex, we are not constrained to only 2 or fewer neighbours per vertex, we may have non-trivial cycles
// Typically need to pick a source vertex s for starting point of traversal

// Depth-First Search (DFS), O(V+E)
// Takes one input parameter, the source vertex s
// Uses recursion to traverse as deeply as possible before backtracking
// For a vertex u with n neighbours, DFS will visit v_1, recursively explore all reachable vertices from v_1, and backtrack to vertex u
// The same thing happens for v_2, v_3, ..., v_n until all neighbours have been traversed
// 5-3
