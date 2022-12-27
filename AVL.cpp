// BST supports most operations in O(h)~O(N) time
// Need to create balanced BST such that h~logN, i.e. O(h)~O(logN)
// define height(v) for each vertex v, defined as:
// The number of edges on the path from vertex v down to its deepest leaf. 
// This attribute is saved in each vertex so we can access a vertex's height in O(1) without having to recompute it every time.
// i.e.
// v.height = -1 (if v is an empty tree)
// v.height = max(v.left.height, v.right.height) + 1 (otherwise)
// height of BST is then root.height
// if N elements, then lower bound is h>log2(N), upper bound is h<N
// for AVL tree, h<2*log2(N)
// at every insert/remove operation, we only change height of vertices located along insertion/removal path
// i.e. x.height = max(x.left.height, x.right.height) + 1
// Define AVL Tree Invariant i.e. property that will never change
// Vertex v is said to be height-balanced iff |v.left.height - v.right.height| <= 1
// Define balance factor bf(v)=v.left.height-v.right.height
// Then if bf(v) != 1 || bf(v) != -1 || bf(v) != 0: need to rotate in order to preserve both BST and AVL invariant
