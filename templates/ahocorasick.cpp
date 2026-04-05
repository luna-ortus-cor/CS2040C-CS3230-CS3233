#include <bits/stdc++.h>
using namespace std;

/**
 * Aho-Corasick Automaton
 * Alphabet size is assumed to be 26 (lowercase English letters).
 */
struct AhoCorasick {
    static const int ALPHABET_SIZE = 26;

    struct Node {
        // Transitions in the trie
        int next[ALPHABET_SIZE];
        // Failure link: longest proper suffix that is also a prefix in the trie
        int link = -1;
        // Dictionary link (Exit link): nearest ancestor in the failure path that is a pattern end
        int exit_link = -1;
        // Index of the pattern ending at this node (-1 if none)
        int pattern_index = -1;
        // Cumulative count of patterns ending at this node or reachable via exit links
        int count = 0;

        Node() {
            fill(begin(next), end(next), -1);
        }
    };

    vector<Node> nodes;

    AhoCorasick() {
        nodes.emplace_back(); // Root node
    }

    // Insert a pattern into the Trie
    void insert(const string& s, int idx) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nodes[v].next[c] == -1) {
                nodes[v].next[c] = nodes.size();
                nodes.emplace_back();
            }
            v = nodes[v].next[c];
        }
        nodes[v].pattern_index = idx;
        nodes[v].count++; // This specific pattern ends here
    }

    // Build failure links and exit links using BFS
    void build() {
        queue<int> q;
        nodes[0].link = 0;
        nodes[0].exit_link = -1;

        for (int c = 0; c < ALPHABET_SIZE; c++) {
            if (nodes[0].next[c] != -1) {
                nodes[nodes[0].next[c]].link = 0;
                q.push(nodes[0].next[c]);
            } else {
                nodes[0].next[c] = 0; // Point to root for missing transitions
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            // Propagate 'count' to include patterns that are suffixes of this node
            nodes[v].count += nodes[nodes[v].link].count;

            // Set exit_link to the nearest suffix that is a pattern end
            int f = nodes[v].link;
            if (nodes[f].pattern_index != -1) {
                nodes[v].exit_link = f;
            } else {
                nodes[v].exit_link = nodes[f].exit_link;
            }

            for (int c = 0; c < ALPHABET_SIZE; c++) {
                if (nodes[v].next[c] != -1) {
                    nodes[nodes[v].next[c]].link = nodes[nodes[v].link].next[c];
                    q.push(nodes[v].next[c]);
                } else {
                    // Precompute transitions to avoid following links during search
                    nodes[v].next[c] = nodes[nodes[v].link].next[c];
                }
            }
        }
    }

    // Move from state v with character c
    int transition(int v, char ch) {
        return nodes[v].next[ch - 'a'];
    }

    // Example utility: Count total pattern occurrences in a text
    long long countTotalOccurrences(const string& text) {
        long long total = 0;
        int v = 0;
        for (char ch : text) {
            v = transition(v, ch);
            total += nodes[v].count;
        }
        return total;
    }
};

int main() {
    AhoCorasick ac;
    vector<string> patterns = {"he", "she", "his", "hers"};

    // 1. Insert patterns
    for (int i = 0; i < patterns.size(); i++) {
        ac.insert(patterns[i], i);
    }

    // 2. Build the automaton
    ac.build();

    // 3. Process text
    string text = "ushershe";
    cout << "Text: " << text << endl;

    int current_state = 0;
    for (int i = 0; i < text.size(); i++) {
        current_state = ac.transition(current_state, text[i]);
        
        // Follow exit links to find all patterns ending at current position
        int temp = current_state;
        while (temp != -1) {
            if (ac.nodes[temp].pattern_index != -1) {
                cout << "Pattern '" << patterns[ac.nodes[temp].pattern_index] 
                     << "' found ending at index " << i << endl;
            }
            temp = ac.nodes[temp].exit_link;
        }
    }

    cout << "Total overlapping pattern matches: " << ac.countTotalOccurrences(text) << endl;

    return 0;
}
