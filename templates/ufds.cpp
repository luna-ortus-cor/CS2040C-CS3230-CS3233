#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

class DSU {
private:
    vector<int> p;       // Parent array
    vector<int> id;      // Mapping: Element -> Node ID
    vector<ll> sum;      // Sum of elements in set
    vector<int> mn, mx;  // Min and Max in set
    vector<int> sz;      // Size of set
    int node_count;      // Total physical nodes (including ghosts)
    int num_sets;

public:
    DSU(int n) {
        // We allocate 2*n to account for 'Move' operations creating new nodes
        p.assign(2 * n + 1, 0);
        id.assign(n + 1, 0);
        sum.assign(2 * n + 1, 0);
        mn.assign(2 * n + 1, 0);
        mx.assign(2 * n + 1, 0);
        sz.assign(2 * n + 1, 0);
        num_sets = n;
        node_count = n;
        for (int i = 1; i <= n; i++) {
            id[i] = i;       // Element i starts at node i
            p[i] = i;
            sum[i] = i;
            mn[i] = i;
            mx[i] = i;
            sz[i] = 1;
        }
    }

    int findSet(int i) {
        int root = id[i];
        while (p[root] != root) root = p[root];
        
        // Path compression for the specific ID mapping
        int curr = id[i];
        while (p[curr] != root) {
            int next = p[curr];
            p[curr] = root;
            curr = next;
        }
        return root;
    }
    
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    // Unite the sets containing elements i and j
    void unionSet(int i, int j) {
        int root_i = findSet(i);
        int root_j = findSet(j);
        if (root_i == root_j) return;

        // Union by size (keep root_i as the larger set)
        if (sz[root_i] < sz[root_j]) swap(root_i, root_j);

        p[root_j] = root_i;
        sz[root_i] += sz[root_j];
        sum[root_i] += sum[root_j];
        mn[root_i] = min(mn[root_i], mn[root_j]);
        mx[root_i] = max(mx[root_i], mx[root_j]);
        num_sets--;
    }

    // MOVE element i to the set containing element j
    void move_element(int i, int j) {
        int root_i = findSet(i);
        int root_j = findSet(j);
        if (root_i == root_j) return;

        // 1. Remove i from its current set's metadata
        sz[root_i]--;
        sum[root_i] -= i;
        // Note: Updating mn/mx after a removal is O(N) unless we use a multiset.

        // 2. Create a NEW physical node for element i
        int new_node = ++node_count;
        id[i] = new_node;
        
        // 3. Attach new node to the target set
        p[new_node] = root_j;
        sz[root_j]++;
        sum[root_j] += i;
        mn[root_j] = min(mn[root_j], i);
        mx[root_j] = max(mx[root_j], i);
    }

    // Utility methods
    ll get_sum(int i) { return sum[findSet(i)]; }
    int get_size(int i) { return sz[findSet(i)]; }
    int get_max(int i) { return mx[findSet(i)]; }
    int get_min(int i) { return mn[findSet(i)]; }
    int numDisjointSets() { return num_sets; }
};

int main() {
  printf("Assume that there are 5 disjoint sets initially\n");
  DSU dsu(5); // create 5 disjoint sets
  printf("%d\n", dsu.numDisjointSets()); // 5
  dsu.unionSet(0, 1);
  printf("%d\n", dsu.numDisjointSets()); // 4
  dsu.unionSet(2, 3);
  printf("%d\n", dsu.numDisjointSets()); // 3
  dsu.unionSet(4, 3);
  printf("%d\n", dsu.numDisjointSets()); // 2
  printf("isSameSet(0, 3) = %d\n", dsu.isSameSet(0, 3)); // will return 0 (false)
  printf("isSameSet(4, 3) = %d\n", dsu.isSameSet(4, 3)); // will return 1 (true)
  for (int i = 0; i < 5; i++) // findSet will return 1 for {0, 1} and 3 for {2, 3, 4}
    printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, dsu.findSet(i), i, dsu.get_size(i));
  dsu.unionSet(0, 3);
  printf("%d\n", dsu.numDisjointSets()); // 1
  for (int i = 0; i < 5; i++) // findSet will return 3 for {0, 1, 2, 3, 4}
    printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n", i, dsu.findSet(i), i, dsu.get_size(i));
  return 0;
}
