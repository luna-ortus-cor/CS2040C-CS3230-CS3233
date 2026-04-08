#include <bits/stdc++.h>

// PBDS Headers
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// Define the trie type
// 1. Key type: string
// 2. Mapped type: null_type (acts like a set) or int (acts like a map)
// 3. trie_string_access_traits<>: Tells the trie how to access characters in the string
// 4. pat_trie_tag: The underlying Patricia Trie implementation
// 5. trie_prefix_search_node_update: Enables the powerful prefix_search feature
typedef trie<
    string,
    null_type,
    trie_string_access_traits<>,
    pat_trie_tag,
    trie_prefix_search_node_update
> pbds_trie;

int main() {
    pbds_trie tr;

    // 1. Insertion
    vector<string> words = {"apple", "apply", "app", "bat", "batch", "ball"};
    for (const string& s : words) {
        tr.insert(s);
    }

    // 2. Existence check (Standard find)
    cout << "Contains 'apple': " << (tr.find("apple") != tr.end() ? "Yes" : "No") << endl;
    cout << "Contains 'banana': " << (tr.find("banana") != tr.end() ? "Yes" : "No") << endl;

    // 3. Prefix Search (The "Killer Feature" of PBDS Trie)
    // prefix_range returns a pair of iterators [begin, end) covering all elements 
    // that start with the given prefix.
    string prefix = "app";
    auto range = tr.prefix_range(prefix);

    cout << "\nWords starting with '" << prefix << "':" << endl;
    for (auto it = range.first; it != range.second; ++it) {
        cout << "- " << *it << endl;
    }

    // 4. Erasure
    tr.erase("apple");
    cout << "\nAfter erasing 'apple', contains 'apple': " 
         << (tr.find("apple") != tr.end() ? "Yes" : "No") << endl;

    return 0;
}
// TODO test + add custom/generalized node update
