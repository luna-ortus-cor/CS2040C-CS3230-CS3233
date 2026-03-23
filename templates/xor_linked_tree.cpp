#include <bits/stdc++.h>
using namespace std;

// Based on https://codeforces.com/blog/entry/135239
template <bool weighted = false, typename T = int>
struct XorLinkedTree {
  uint32_t n = 0;
  vector<uint32_t> deg;
  vector<uint32_t> link;
  vector<T> val;

  XorLinkedTree() = default;
  explicit XorLinkedTree(uint32_t _n) { init(_n); };

  void init(uint32_t _n) {
    n = _n;
    deg.assign(n, 0);
    link.assign(n, 0);
    if constexpr (weighted) val.assign(n, 0);
  }

  void add_edge(uint32_t u, uint32_t v) requires(!weighted) {
    assert(u < n && v < n);
    assert(u != v);
    ++deg[u], link[u] ^= v;
    ++deg[v], link[v] ^= u;
  }

  void add_edge(uint32_t u, uint32_t v, T w) requires(weighted) {
    assert(u < n && v < n);
    assert(u != v);
    ++deg[u], link[u] ^= v, val[u] ^= w;
    ++deg[v], link[v] ^= u, val[v] ^= w;
  }

  template <typename F>
  void build(uint32_t root, F&& func) {
    assert(root < n);
    ++deg[root];

    for (uint32_t i = 0; i < n; ++i) {
      uint32_t u = i;
      while (deg[u] == 1) {
        uint32_t v = link[u];
        if constexpr (weighted) {
          T w = val[u];
          func(u, v, w);
          val[v] ^= w;
        } else {
          func(u, v);
        }
        deg[u] = 0;
        --deg[v], link[v] ^= u;
        u = v;
      }
    }
  }
};

template <bool weighted = false, typename T = int>
struct XorTreeOps {
    uint32_t n;
    uint32_t root;
    vector<uint32_t> parent;
    vector<uint32_t> depth;
    vector<uint32_t> order; // BFS / Root-to-Leaf Order
    vector<T> dist;         // Root distance
    vector<T> edge_to_p;    // Weight to parent
    
    // LCA / Binary Lifting
    vector<vector<uint32_t>> up;
    uint32_t LOG;

    XorTreeOps(XorLinkedTree<weighted, T>& tree, uint32_t _root) : n(tree.n), root(_root) {
        parent.assign(n, n);
        depth.assign(n, 0);
        dist.assign(n, 0);
        edge_to_p.assign(n, 0);
        vector<pair<uint32_t, uint32_t>> edges;
        vector<T> weights;

        // Step 1: Reconstruct using the template's build (Leaf-to-Root)
        tree.build(root, [&](uint32_t u, uint32_t v, T w = 0) {
            parent[u] = v;
            edge_to_p[u] = w;
            order.push_back(u);
        });
        order.push_back(root);
        reverse(order.begin(), order.end()); // Root-to-Leaf (BFS Order)

        // Step 2: Build Basic Tree Info
        for (uint32_t u : order) {
            if (u != root) {
                depth[u] = depth[parent[u]] + 1;
                if constexpr (weighted) dist[u] = dist[parent[u]] + edge_to_p[u];
            }
        }

        LOG = 32 - __builtin_clz(n);
        up.assign(n, vector<uint32_t>(LOG, n));
    }

    // 1. BFS / DFS Traversal Logic
    // Forward iteration over 'order' is BFS (Level-order)
    for (uint32_t u : order) { }
    // Backward iteration over 'order' is DFS Post-order (Subtree DP)
    for (auto it = order.rbegin(); it != order.rend(); ++it) { }

    // 2. Binary Lifting (LCA & K-th Ancestor)
    void build_lca() {
        for (uint32_t i = 0; i < n; i++) up[i][0] = parent[i];
        for (uint32_t j = 1; j < LOG; j++) {
            for (uint32_t i = 0; i < n; i++) {
                if (up[i][j - 1] != n)
                    up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }

    uint32_t get_lca(uint32_t u, uint32_t v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int j = LOG - 1; j >= 0; j--) {
            if (depth[u] - (1 << j) >= depth[v]) u = up[u][j];
        }
        if (u == v) return u;
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    uint32_t get_kth_ancestor(uint32_t u, uint32_t k) {
        for (int j = 0; j < LOG; j++) {
            if ((k >> j) & 1) {
                u = up[u][j];
                if (u == n) break;
            }
        }
        return u;
    }

    // 3. Diameter (DP Approach - O(N))
    T get_diameter() {
        vector<T> max_h(n, 0);
        T diameter = 0;
        // Process in reverse topological order (Leaves-to-Root)
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            uint32_t u = *it;
            uint32_t p = parent[u];
            if (p != n) {
                T w = (weighted ? edge_to_p[u] : 1);
                diameter = max(diameter, max_h[p] + max_h[u] + w);
                max_h[p] = max(max_h[p], max_h[u] + w);
            }
        }
        return diameter;
    }

    // 4. Subtree Sizes (O(N))
    vector<uint32_t> get_subtree_sizes() {
        vector<uint32_t> sz(n, 1);
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            uint32_t u = *it;
            if (parent[u] != n) sz[parent[u]] += sz[u];
        }
        return sz;
    }

    // 5. Tree Distance (Weighted or Unweighted)
    T get_dist(uint32_t u, uint32_t v) {
        if constexpr (weighted) {
            return dist[u] + dist[v] - 2 * dist[get_lca(u, v)];
        } else {
            return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
        }
    }
};
//todo check
