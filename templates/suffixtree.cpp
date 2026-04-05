#include <bits/stdc++.h>
using namespace std;

struct SuffixTree {
    struct Node {
        int start, *end, link;
        map<char, int> next;
        Node(int s, int *e) : start(s), end(e), link(0) {}
        int len(int pos) { return min(*end, pos) - start + 1; }
    };

    string s;
    vector<Node> tree;
    int root, last_added, remainder, active_node, active_edge, active_len;
    int leaf_end = -1;

    SuffixTree(string str) : s(str) {
        root = active_node = newNode(-1, new int(-1));
        remainder = active_len = 0;
        active_edge = -1;
        for (int i = 0; i < s.size(); i++) extend(i);
    }

    int newNode(int start, int *end) {
        tree.emplace_back(start, end);
        return tree.size() - 1;
    }

    void extend(int pos) {
        leaf_end = pos;
        remainder++;
        last_added = root;
        while (remainder > 0) {
            if (active_len == 0) active_edge = pos;
            auto it = tree[active_node].next.find(s[active_edge]);
            
            if (it == tree[active_node].next.end()) {
                tree[active_node].next[s[active_edge]] = newNode(pos, &leaf_end);
                add_link(active_node);
            } else {
                int next_node = it->second;
                if (walk_down(next_node, pos)) continue;
                if (s[tree[next_node].start + active_len] == s[pos]) {
                    active_len++;
                    add_link(active_node);
                    break;
                }
                int *split_end = new int(tree[next_node].start + active_len - 1);
                int split = newNode(tree[next_node].start, split_end);
                tree[active_node].next[s[active_edge]] = split;
                tree[split].next[s[pos]] = newNode(pos, &leaf_end);
                tree[next_node].start += active_len;
                tree[split].next[s[tree[next_node].start]] = next_node;
                add_link(split);
            }
            remainder--;
            if (active_node == root && active_len > 0) {
                active_len--;
                active_edge = pos - remainder + 1;
            } else if (active_node != root) {
                active_node = tree[active_node].link;
            }
        }
    }

    void add_link(int node) {
        if (last_added != root) tree[last_added].link = node;
        last_added = node;
    }

    bool walk_down(int node, int pos) {
        int edge_len = tree[node].len(pos);
        if (active_len >= edge_len) {
            active_edge += edge_len;
            active_len -= edge_len;
            active_node = node;
            return true;
        }
        return false;
    }

    // --- Search Function ---
    bool search(string pattern) {
        int curr_node = root;
        int i = 0;
        while (i < pattern.size()) {
            auto it = tree[curr_node].next.find(pattern[i]);
            if (it == tree[curr_node].next.end()) return false;

            int next_node = it->second;
            int edge_start = tree[next_node].start;
            int edge_len = tree[next_node].len(s.size() - 1);

            for (int j = 0; j < edge_len && i < pattern.size(); j++, i++) {
                if (s[edge_start + j] != pattern[i]) return false;
            }
            curr_node = next_node;
        }
        return true;
    }
};

int main() {
    // Note: Suffix trees usually append a sentinel '$' to ensure 
    // every suffix ends at a leaf node.
    string text = "banana$";
    SuffixTree st(text);

    cout << "Suffix Tree built for: " << text << endl;
    cout << "---------------------------------" << endl;

    vector<string> queries = {"ana", "nana", "ban", "apple", "banana", "nan"};

    for (const string& q : queries) {
        cout << "Search '" << q << "': " 
             << (st.search(q) ? "FOUND" : "NOT FOUND") << endl;
    }

    return 0;
}
