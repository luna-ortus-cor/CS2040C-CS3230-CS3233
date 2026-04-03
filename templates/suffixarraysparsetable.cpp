#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    int n;
    string s;
    vector<int> sa, lcp, rank;

    SuffixArray(string _s) : s(_s + "$") { // Add sentinel for lexicographical safety
        n = s.size();
        sa.resize(n);
        rank.resize(n);
        build_sa();
        build_lcp();
    }

    void build_sa() {
        int m = 256; // Initial alphabet size
        vector<int> cnt(max(n, m), 0), x(n), y(n);

        for (int i = 0; i < n; i++) cnt[x[i] = s[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[x[i]]] = i;

        for (int k = 1; k < n; k <<= 1) {
            int p = 0;
            for (int i = n - k; i < n; i++) y[p++] = i;
            for (int i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;

            fill(cnt.begin(), cnt.begin() + m, 0);
            for (int i = 0; i < n; i++) cnt[x[y[i]]]++;
            for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];

            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && 
                            (sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1) == 
                            (sa[i] + k < n ? y[sa[i] + k] : -1)) ? p - 1 : p++;
            }
            if (p >= n) break;
            m = p;
        }
        // Remove sentinel effect for user access
        sa.erase(sa.begin());
        n--;
    }

    void build_lcp() {
        rank.resize(n);
        lcp.assign(n, 0);
        for (int i = 0; i < n; i++) rank[sa[i]] = i;
        
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
            if (k > 0) k--;
        }
    }
};

struct LCPQueries {
    int n;
    vector<int> rank;
    vector<vector<int>> st;
    vector<int> lg;

    // We pass the SuffixArray object's data here
    LCPQueries(const vector<int>& _sa, const vector<int>& _lcp, const vector<int>& _rank) {
        n = _sa.size();
        rank = _rank;
        
        // Precompute logs for O(1) query
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;
        st.assign(K, vector<int>(n));

        // Initialize Sparse Table with the LCP array
        for (int i = 0; i < n - 1; i++) st[0][i] = _lcp[i];

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n - 1; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query_lcp(int i, int j) {
        if (i == j) return n - i; // LCP with itself is the suffix length
        int l = rank[i], r = rank[j];
        if (l > r) swap(l, r);
        
        // We need the minimum in LCP range [l, r-1]
        r--; 
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int main() {
    string s = "abracadabra";
    SuffixArray sa_obj(s);
    LCPQueries lcp_solver(sa_obj.sa, sa_obj.lcp, sa_obj.rank);

    // Suffixes:
    // Index 0: abracadabra
    // Index 7: abra
    cout << "LCP of suffix 0 and 7: " << lcp_solver.query_lcp(0, 7) << endl; 
    // Output: 4 ("abra")

    // Index 1: bracadabra
    // Index 8: bra
    cout << "LCP of suffix 1 and 8: " << lcp_solver.query_lcp(1, 8) << endl;
    // Output: 3 ("bra")

    return 0;
}
