#include <bits/stdc++.h>
using namespace std;

struct SCS {
    int n;
    vector<string> s;
    vector<vector<int>> overlap;
    vector<vector<int>> dp;
    vector<vector<int>> parent;

    SCS(vector<string> input) {
        // 1. Remove strings that are substrings of others
        sort(input.begin(), input.end(), [](const string& a, const string& b) {
            return a.size() > b.size();
        });
        for (auto& str : input) {
            bool redundant = false;
            for (auto& kept : s) {
                if (kept.find(str) != string::npos) { redundant = true; break; }
            }
            if (!redundant) s.push_back(str);
        }
        n = s.size();
        overlap.assign(n, vector<int>(n));
        dp.assign(1 << n, vector<int>(n, 1e9));
        parent.assign(1 << n, vector<int>(n, -1));
    }

    void precompute() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                for (int len = min(s[i].size(), s[j].size()); len >= 0; len--) {
                    if (s[i].substr(s[i].size() - len) == s[j].substr(0, len)) {
                        overlap[i][j] = len;
                        break;
                    }
                }
            }
        }
    }

    string solve() {
        precompute();
        for (int i = 0; i < n; i++) dp[1 << i][i] = s[i].size();

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i)) || dp[mask][i] == 1e9) continue;
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) continue;
                    int next_mask = mask | (1 << j);
                    int new_len = dp[mask][i] + s[j].size() - overlap[i][j];
                    if (new_len < dp[next_mask][j]) {
                        dp[next_mask][j] = new_len;
                        parent[next_mask][j] = i;
                    }
                }
            }
        }

        int last = 0, mask = (1 << n) - 1;
        for (int i = 1; i < n; i++) if (dp[mask][i] < dp[mask][last]) last = i;

        // Path reconstruction
        string res = "";
        vector<int> path;
        while (last != -1) {
            path.push_back(last);
            int prev = parent[mask][last];
            mask ^= (1 << last);
            last = prev;
        }
        reverse(path.begin(), path.end());
        res = s[path[0]];
        for (int i = 1; i < path.size(); i++) {
            res += s[path[i]].substr(overlap[path[i - 1]][path[i]]);
        }
        return res;
    }
};

struct ClosestString {
    int n, L, k;
    vector<string> s;
    string res;

    bool dfs(string& curr, int dist_left) {
        int far_idx = -1, max_d = -1;
        for (int i = 0; i < n; i++) {
            int d = 0;
            for (int j = 0; j < L; j++) if (curr[j] != s[i][j]) d++;
            if (d > k) {
                if (d > max_d) { max_d = d; far_idx = i; }
            }
        }
        if (far_idx == -1) { res = curr; return true; }
        if (dist_left == 0) return false;

        vector<int> diff_pos;
        for (int j = 0; j < L; j++) if (curr[j] != s[far_idx][j]) diff_pos.push_back(j);

        // Branching: only need to try changing k+1 positions where curr and s[far_idx] differ
        for (int i = 0; i < min((int)diff_pos.size(), k + 1); i++) {
            char old_char = curr[diff_pos[i]];
            curr[diff_pos[i]] = s[far_idx][diff_pos[i]];
            if (dfs(curr, dist_left - 1)) return true;
            curr[diff_pos[i]] = old_char;
        }
        return false;
    }

    string solve() {
        string template_s = s[0];
        if (dfs(template_s, k)) return res;
        return "No Solution";
    }
};

#include <bits/stdc++.h>
using namespace std;

struct KStringDP {
    int k;
    vector<string> s;
    map<vector<int>, int> memo_lcs, memo_scs;

    KStringDP(vector<string> _s) : s(_s), k(_s.size()) {}

    // Longest Common Subsequence
    int lcs(vector<int> idx) {
        for (int i = 0; i < k; i++) if (idx[i] == 0) return 0;
        if (memo_lcs.count(idx)) return memo_lcs[idx];

        bool all_match = true;
        char c = s[0][idx[0] - 1];
        for (int i = 1; i < k; i++) if (s[i][idx[i] - 1] != c) all_match = false;

        if (all_match) {
            vector<int> next_idx = idx;
            for (int& x : next_idx) x--;
            return memo_lcs[idx] = 1 + lcs(next_idx);
        } else {
            int res = 0;
            for (int i = 0; i < k; i++) {
                if (idx[i] > 0) {
                    vector<int> next_idx = idx;
                    next_idx[i]--;
                    res = max(res, lcs(next_idx));
                }
            }
            return memo_lcs[idx] = res;
        }
    }

    // Shortest Common Supersequence 
    int scs(vector<int> idx) {
        int zeros = 0;
        for (int i = 0; i < k; i++) if (idx[i] == 0) zeros++;
        if (zeros == k) return 0;
        if (memo_scs.count(idx)) return memo_scs[idx];

        bool all_match = true;
        char c = ' ';
        for(int i=0; i<k; i++) if(idx[i] > 0) { c = s[i][idx[i]-1]; break; }
        for (int i = 0; i < k; i++) {
            if (idx[i] > 0 && s[i][idx[i] - 1] != c) { all_match = false; break; }
        }

        if (all_match) {
            vector<int> next_idx = idx;
            for (int& x : next_idx) if (x > 0) x--;
            return memo_scs[idx] = 1 + scs(next_idx);
        } else {
            int res = 1e9;
            // In SCS, if they don't all match, we try picking each unique character 
            // present at the current indices and advancing only strings with that char.
            set<char> options;
            for(int i=0; i<k; i++) if(idx[i] > 0) options.insert(s[i][idx[i]-1]);
            
            for(char opt : options) {
                vector<int> next_idx = idx;
                for(int i=0; i<k; i++) if(idx[i] > 0 && s[i][idx[i]-1] == opt) next_idx[i]--;
                res = min(res, 1 + scs(next_idx));
            }
            return memo_scs[idx] = res;
        }
    }
};

#include <bits/stdc++.h>
using namespace std;

struct SAM {
    struct Node {
        int len, link;
        map<char, int> next;
    };
    vector<Node> st;
    int sz, last;
    vector<int> min_match, cur_match;

    SAM(int n) {
        st.resize(n * 2);
        st[0] = {0, -1, {}};
        sz = 1; last = 0;
    }

    void extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    void match(const string& t) {
        cur_match.assign(sz, 0);
        int v = 0, l = 0;
        for (char c : t) {
            while (v != 0 && !st[v].next.count(c)) {
                v = st[v].link;
                l = st[v].len;
            }
            if (st[v].next.count(c)) {
                v = st[v].next[c];
                l++;
            }
            cur_match[v] = max(cur_match[v], l);
        }
        // Propagate matches to links (shorter suffixes)
        for (int i = sz - 1; i > 0; i--) {
            cur_match[st[i].link] = max(cur_match[st[i].link], min(st[st[i].link].len, cur_match[i]));
        }
        for (int i = 0; i < sz; i++) min_match[i] = min(min_match[i], cur_match[i]);
    }

    int solve(const vector<string>& strings) {
        for (char c : strings[0]) extend(c);
        min_match.assign(sz, 0);
        for (int i = 0; i < sz; i++) min_match[i] = st[i].len;

        for (int i = 1; i < strings.size(); i++) match(strings[i]);

        int ans = 0;
        for (int i = 0; i < sz; i++) ans = max(ans, min_match[i]);
        return ans;
    }
};

//TODO test
