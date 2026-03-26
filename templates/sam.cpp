#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SAM {
    struct Node {
        int len, link;
        map<char, int> next;
        ll count = 0; // Number of times this state occurs in the string
        bool is_clone = false;

        Node() : len(0), link(-1) {}
    };

    vector<Node> st;
    int last;

    SAM(const string& s) {
        st.emplace_back(); // Root node at index 0
        last = 0;
        for (char c : s) extend(c);
        compute_counts(s);
    }

    void extend(char c) {
        int cur = st.size();
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].count = 1; // New state corresponds to a new endpos
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.emplace_back();
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                st[clone].is_clone = true;
                st[clone].count = 0; // Clones don't represent new endpos initially
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // Required to calculate how many times each substring appears
    void compute_counts(const string& s) {
        vector<int> nodes_by_len(st.size());
        iota(nodes_by_len.begin(), nodes_by_len.end(), 0);
        sort(nodes_by_len.begin(), nodes_by_len.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });
        for (int v : nodes_by_len) {
            if (st[v].link != -1) {
                st[st[v].link].count += st[v].count;
            }
        }
    }
};

string get_smallest_cyclic_shift(int original_n) {
    int curr = 0;
    string res = "";
    for (int i = 0; i < original_n; i++) {
        // map stores keys in sorted order, 
        // so begin() is the smallest character transition
        auto it = st[curr].next.begin(); 
        res += it->first;
        curr = it->second;
    }
    return res;
}

int main() {
    string A = "banana";
    SAM sam(A);

    // 1. Count Distinct Substrings
    ll distinct = 0;
    for (int i = 1; i < sam.st.size(); i++) {
        distinct += sam.st[i].len - sam.st[sam.st[i].link].len;
    }
    cout << "Distinct Substrings of 'banana': " << distinct << endl;

    // 2. Longest Common Substring with "nanana"
    string B = "nanana";
    int v = 0, l = 0, best_len = 0;
    for (char c : B) {
        while (v != 0 && !sam.st[v].next.count(c)) {
            v = sam.st[v].link;
            l = sam.st[v].len;
        }
        if (sam.st[v].next.count(c)) {
            v = sam.st[v].next[c];
            l++;
        }
        best_len = max(best_len, l);
    }
    cout << "Longest Common Substring of 'banana' and 'nanana': " << best_len << endl;

    // 3. Number of occurrences of "ana"
    string sub = "ana";
    int curr = 0;
    bool exists = true;
    for (char c : sub) {
        if (!sam.st[curr].next.count(c)) { exists = false; break; }
        curr = sam.st[curr].next[c];
    }
    cout << "Occurrences of 'ana' in 'banana': " << (exists ? sam.st[curr].count : 0) << endl;

    // 4. Lexicographically smallest cyclic shift
    string s = "baca";
    string doubled = s + s;
    SAM sam(doubled);

    cout << "Smallest cyclic shift of 'baca': " 
         << sam.get_smallest_cyclic_shift(s.size()) << endl;

    return 0;
}
