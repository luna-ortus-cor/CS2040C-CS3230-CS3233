#include <bits/stdc++.h>
using namespace std;

class Trie {
private:
    struct Node {
        int children[26];
        int words_here;    // count of words ending exactly here
        int prefix_count;  // count of words passing through this node
        
        Node() {
            memset(children, -1, sizeof(children));
            words_here = 0;
            prefix_count = 0;
        }
    };

    vector<Node> trie;

public:
    Trie() {
        trie.emplace_back(); // Root at index 0
    }

    void insert(const string &s) {
        int cur = 0;
        for (char c : s) {
            int alpha = c - 'A';
            if (trie[cur].children[alpha] == -1) {
                trie[cur].children[alpha] = trie.size();
                trie.emplace_back();
            }
            cur = trie[cur].children[alpha];
            trie[cur].prefix_count++; // Useful for "count startsWith"
        }
        trie[cur].words_here++;
    }

    // Returns how many times 's' exists in the Trie
    int countWord(const string &s) {
        int cur = 0;
        for (char c : s) {
            int alpha = c - 'A';
            if (trie[cur].children[alpha] == -1) return 0;
            cur = trie[cur].children[alpha];
        }
        return trie[cur].words_here;
    }

    // Returns how many words start with prefix 'p'
    int countPrefix(const string &p) {
        int cur = 0;
        for (char c : p) {
            int alpha = c - 'A';
            if (trie[cur].children[alpha] == -1) return 0;
            cur = trie[cur].children[alpha];
        }
        return trie[cur].prefix_count;
    }

    // Useful for deleting one instance of a word
    bool erase(const string &s) {
        if (countWord(s) == 0) return false;
        int cur = 0;
        for (char c : s) {
            int alpha = c - 'A';
            cur = trie[cur].children[alpha];
            trie[cur].prefix_count--;
        }
        trie[cur].words_here--;
        return true;
    }
};
