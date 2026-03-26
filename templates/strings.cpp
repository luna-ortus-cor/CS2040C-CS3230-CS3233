#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct RabinKarp {
    const ll BASE = 31;
    const ll MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
    vector<ll> p1, p2, h1, h2;

    RabinKarp(const string& s) {
        int n = s.size();
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);

        for (int i = 0; i < n; i++) {
            p1[i + 1] = (p1[i] * BASE) % MOD1;
            p2[i + 1] = (p2[i] * BASE) % MOD2;
            h1[i + 1] = (h1[i] * BASE + (s[i] - 'a' + 1)) % MOD1;
            h2[i + 1] = (h2[i] * BASE + (s[i] - 'a' + 1)) % MOD2;
        }
    }

    // Returns the double hash of substring s[l...r]
    pair<ll, ll> get_hash(int l, int r) {
        ll res1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
        ll res2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;
        return {res1, res2};
    }
};

struct AhoCorasick {
    struct Node {
        int next[26];
        int fail = 0, p = -1, p_char = -1;
        int end_count = 0; // Number of patterns ending here
        int dict_link = 0; // Link to the next 'end' node in the fail path
        
        Node(int _p = -1, int _ch = -1) : p(_p), p_char(_ch) {
            fill(begin(next), end(next), -1);
        }
    };

    vector<Node> trie;
    AhoCorasick() { trie.emplace_back(); }

    void insert(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = trie.size();
                trie.emplace_back(v, c);
            }
            v = trie[v].next[c];
        }
        trie[v].end_count++;
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int c = 0; c < 26; c++) {
                int u = trie[v].next[c];
                if (u != -1) {
                    trie[u].fail = (v == 0) ? 0 : trie[trie[v].fail].next[c];
                    // Dictionary link skips non-end nodes for faster counting
                    trie[u].dict_link = (trie[trie[u].fail].end_count > 0) ? 
                                         trie[u].fail : trie[trie[u].fail].dict_link;
                    q.push(u);
                } else {
                    trie[v].next[c] = (v == 0) ? 0 : trie[trie[v].fail].next[c];
                }
            }
        }
    }
};

struct ZAlgorithm {
    vector<int> z;
    ZAlgorithm(const string& s) {
        int n = s.size();
        z.assign(n, 0);
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r) z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
    }
};

struct KMP {
    vector<int> pi;
    KMP(const string& s) {
        int n = s.size();
        pi.assign(n, 0);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
    }
};

struct Manacher {
    vector<int> p; // p[i] = radius of palindrome centered at i
    Manacher(string s) {
        string t = "#";
        for (char c : s) { t += c; t += "#"; }
        int n = t.size();
        p.assign(n, 0);
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(p[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && t[i - k] == t[i + k]) k++;
            p[i] = --k;
            if (i + k > r) { l = i - k; r = i + k; }
        }
    }
};

int main() {
    // --- 1. Rabin-Karp Demonstration ---
    // Goal: Check if two substrings are identical without direct string comparison
    string s = "abracadabra";
    RabinKarp rk(s);
    auto h1 = rk.get_hash(0, 3); // "abra"
    auto h2 = rk.get_hash(7, 10); // "abra"
    cout << "Rabin-Karp: 'abra' == 'abra'? " << (h1 == h2 ? "Yes" : "No") << endl;

    // --- 2. Aho-Corasick Demonstration ---
    // Goal: Find multiple patterns in a text simultaneously
    AhoCorasick ac;
    vector<string> patterns = {"he", "she", "his", "hers"};
    for (auto& p : patterns) ac.insert(p);
    ac.build();

    string text = "ushers";
    int curr = 0;
    cout << "Aho-Corasick (searching 'ushers'): ";
    for (char c : text) {
        curr = ac.trie[curr].next[c - 'a'];
        int temp = curr;
        while (temp > 0) {
            if (ac.trie[temp].end_count > 0) cout << "[Found a match!] ";
            temp = ac.trie[temp].dict_link;
        }
    }
    cout << endl;

    // --- 3. Z-Algorithm Demonstration ---
    // Goal: Find all occurrences of "abc" in "abxabcabc"
    string pattern = "abc", source = "abxabcabc";
    string concat = pattern + "$" + source; 
    ZAlgorithm za(concat);
    cout << "Z-Algorithm (occurrences of 'abc'): ";
    for (int i = 0; i < concat.size(); i++) {
        if (za.z[i] == pattern.size()) {
            cout << "at index " << i - pattern.size() - 1 << " ";
        }
    }
    cout << endl;

    // --- 4. KMP Demonstration ---
    // Goal: Use the prefix function to understand the structure of "ababa"
    string kmp_str = "ababa";
    KMP kmp(kmp_str);
    cout << "KMP (Prefix Function for 'ababa'): ";
    for (int x : kmp.pi) cout << x << " ";
    cout << endl;

    // --- 5. Manacher's Demonstration ---
    // Goal: Find the longest palindromic substring in "abaaba"
    string pal = "abaaba";
    Manacher m(pal);
    int max_len = 0;
    for (int radius : m.p) max_len = max(max_len, radius);
    cout << "Manacher's: Longest palindrome in 'abaaba' has length " << max_len << endl;

    return 0;
}
