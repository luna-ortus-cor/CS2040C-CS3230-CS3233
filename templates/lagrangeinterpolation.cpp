// Example: f(x) = x^2
// Terms (x=0 to 4): 0, 1, 4, 9, 16
long long lagrange(const vector<long long>& y, long long V, int mod) {
    int k = y.size() - 1;
    if (V <= k) return y[V];

    vector<long long> pref(k + 1), suff(k + 1);
    pref[0] = suff[k] = 1;
    for (int i = 0; i < k; i++) pref[i + 1] = pref[i] * (V - i) % mod;
    for (int i = k; i > 0; i--) suff[i - 1] = suff[i] * (V - i) % mod;

    long long ans = 0;
    for (int i = 0; i <= k; i++) {
        long long num = pref[i] * suff[i] % mod;
        long long den = invFact[i] * invFact[k - i] % mod;
        long long term = y[i] * num % mod * den % mod;
        if ((k - i) % 2) ans = (ans - term + mod) % mod;
        else ans = (ans + term) % mod;
    }
    return ans;
}
