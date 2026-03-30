#include <bits/stdc++.h>
using namespace std;

typedef __int128_t int128;
typedef long long ll;

// O(n^1/4) algorithm for factorization of up to 1e18 (long long)

ll mul_mod(ll a, ll b, ll m) {
    return (ll)((int128)a * b % m);
}

ll power(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = mul_mod(res, a, m);
        a = mul_mod(a, a, m);
        b /= 2;
    }
    return res;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    
    static const vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (ll a : bases) {
        if (n <= a) break;
        ll x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    if (is_prime(n)) return n;
    
    static mt19937_64 rng(1337);
    uniform_int_distribution<ll> dist(2, n - 1);
    
    while (true) {
        ll x = dist(rng);
        ll y = x;
        ll c = dist(rng);
        ll g = 1;
        while (g == 1) {
            x = (mul_mod(x, x, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;
            ll diff = (x > y) ? (x - y) : (y - x);
            g = gcd(diff, n);
        }
        if (g != n) return g;
    }
}

void factorize(ll n, map<ll, int>& factors) {
    if (n == 1) return;
    if (is_prime(n)) {
        factors[n]++;
        return;
    }
    ll d = pollard_rho(n);
    factorize(d, factors);
    factorize(n / d, factors);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        
        map<ll, int> factors;
        factorize(n, factors);
        
        
        ll total_divisors = 1;
        for (auto const& [p, count] : factors) {
            total_divisors *= (count + 1);
        }
        
        cout << total_divisors << "\n";
    }
    return 0;
}
