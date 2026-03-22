#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct HittingSet {
    int n, m;
    vector<ll> sets; // Each set represented as a bitmask of elements
    int min_size;
    ll best_h;

    HittingSet(int _n, int _m) : n(_n), m(_m), min_size(_n + 1), best_h(0) {}

    void add_set(const vector<int>& elements) {
        ll mask = 0;
        for (int x : elements) {
            mask |= (1LL << (x - 1)); // Assuming 1-indexed elements
        }
        // Optimization: If a set is a superset of another, it's redundant
        bool redundant = false;
        for (int i = 0; i < sets.size(); ) {
            if ((mask & sets[i]) == sets[i]) {
                redundant = true;
                break;
            }
            if ((mask & sets[i]) == mask) {
                sets.erase(sets.begin() + i);
            } else {
                i++;
            }
        }
        if (!redundant) sets.push_back(mask);
    }

    // idx: current element being considered
    // current_h: mask of elements chosen for hitting set
    // covered_mask: bitmask of which sets in 'sets' are currently hit
    void backtrack(int idx, int count, ll current_h, int covered_mask) {
        // Pruning: if current count already exceeds best found
        if (count >= min_size) return;

        // All sets hit? (covered_mask has all m bits set)
        if (covered_mask == (1 << sets.size()) - 1) {
            min_size = count;
            best_h = current_h;
            return;
        }

        if (idx == n) return;

        // Greedy Heuristic: Pick element that hits the most unhit sets (Optional)
        
        // Option 1: Include element idx
        int next_covered = covered_mask;
        for (int i = 0; i < sets.size(); i++) {
            if (sets[i] & (1LL << idx)) {
                next_covered |= (1 << i);
            }
        }
        
        // Only include if it actually hits a new set
        if (next_covered != covered_mask) {
            backtrack(idx + 1, count + 1, current_h | (1LL << idx), next_covered);
        }

        // Option 2: Skip element idx
        backtrack(idx + 1, count, current_h, covered_mask);
    }

    pair<int, vector<int>> solve() {
        m = sets.size();
        // Sort elements by frequency to improve pruning (Heuristic)
        backtrack(0, 0, 0, 0);

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (best_h & (1LL << i)) result.push_back(i + 1);
        }
        return {min_size, result};
    }
};
