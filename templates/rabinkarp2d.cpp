#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Hash2D {
    int N, M;
    const ll P1 = 31, P2 = 37, MOD = 1e9 + 7;
    vector<vector<ll>> grid_hash;
    vector<ll> pow1, pow2;

    Hash2D(const vector<string>& grid) : N(grid.size()), M(grid[0].size()) {
        grid_hash.assign(N + 1, vector<ll>(M + 1, 0));
        pow1.assign(N + 1, 1); pow2.assign(M + 1, 1);

        for (int i = 1; i <= N; i++) pow1[i] = (pow1[i - 1] * P1) % MOD;
        for (int i = 1; i <= M; i++) pow2[i] = (pow2[i - 1] * P2) % MOD;

        // 2D Prefix Hash: H[i][j] = hash of rectangle from (0,0) to (i,j)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ll val = (grid[i][j] - 'a' + 1);
                grid_hash[i + 1][j + 1] = (grid_hash[i][j + 1] * P1 + 
                                           grid_hash[i + 1][j] * P2 - 
                                           grid_hash[i][j] * P1 % MOD * P2 % MOD + 
                                           val + MOD + MOD) % MOD;
            }
        }
    }

    // Get hash of rectangle with top-left (r1, c1) and bottom-right (r2, c2)
    ll get_hash(int r1, int c1, int r2, int c2) {
        r2++; c2++;
        ll res = (grid_hash[r2][c2] - 
                  grid_hash[r1][c2] * pow1[r2 - r1] % MOD - 
                  grid_hash[r2][c1] * pow2[c2 - c1] % MOD + 
                  grid_hash[r1][c1] * pow1[r2 - r1] % MOD * pow2[c2 - c1] % MOD + 
                  MOD + MOD) % MOD;
        return res;
    }
};
