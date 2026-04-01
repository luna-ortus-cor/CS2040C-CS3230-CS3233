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
