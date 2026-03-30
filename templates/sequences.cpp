#include <bits/stdc++.h>
using namespace std;

// nCk = nC(n-k)
// nCk = n/k * (n-1)C(k-1)
// sum_{k=0}^{n} nCk = 2^n
// sum_{k=0}^m (n+k)Ck = (n+m+1)Cm
// sum_{k=0}^n (nCk)^2 = (2n)Cn
// sum_{k=0}^n k(nCk) = n2^(n-1)
// sum_{k=0}^n (n-k)Ck = F_{n+1}

// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
vector<long long> genFib(int n, int mod) {
    vector<long long> f(n + 1);
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= n; i++) 
        f[i] = (f[i-1] + f[i-2]) % mod;
    return f; 
}

// C(n) = sum_{i=0}^{n-1} C(i) * C(n-1-i)
// 1, 1, 2, 5, 14, 42, 132, 429, 1430
vector<long long> genCatalan(int n, int mod) {
    vector<long long> c(n + 1, 0);
    c[0] = 1;
    C[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j < i; j++)
            c[i] = (c[i] + (c[j] * c[i - 1 - j]) % mod) % mod;
    return c;
}
// or calculate with 1/(n+1) 2nCn

// Stirling numbers of second kind, number of ways to split n objects into k nonempty sets
long long S[1001][1001];
void genStirling(int n, int mod) {
    for (int i = 0; i <= n; i++) {
        S[i][i] = 1; S[i][0] = 0;
        for (int j = 1; j < i; j++)
            S[i][j] = (j * S[i-1][j] + S[i-1][j-1]) % mod;
    }
}

// Bell numbers, total number of ways to split n objects into nonempty sets]
vector<long long> genBell(int n, int mod) {
    // Stirling sum approach is usually easier if you already have the Stirling DP
    vector<long long> b(n + 1, 0);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            b[i] = (b[i] + S[i][j]) % mod; // Using S[i][j] from method #3
    return b;
}

// 1, 0, 1, 2, 9, 44, 265, 1854, 14833
// The number of permutations of n elements with no fixed point
vector<long long> genDerange(int n, int mod) {
    vector<long long> d(n + 1);
    d[0] = 1; d[1] = 0;
    for (int i = 2; i <= n; i++)
        d[i] = (i - 1) * (d[i-1] + d[i-2]) % mod;
    return d;
}

// The number of permutations of 1 to n in which exactly k elements are greater than the previous element
long long E[1001][1001];
void genEulerian(int n, int mod) {
    for (int i = 1; i <= n; i++) {
        E[i][0] = 1; 
        for (int j = 1; j < i; j++)
            E[i][j] = ((j + 1) * E[i-1][j] + (i - j) * E[i-1][j-1]) % mod;
    }
}

// The number of different ways of drawing non-intersecting chords between n point on a circle
// 1, 1, 2, 4, 9, 21, 51, 127, 323, 835
vector<long long> genMotzkin(int n, int mod) {
    vector<long long> M(n + 1, 0);
    M[0] = 1; if(n > 0) M[1] = 1;
    for (int i = 2; i <= n; i++) {
        M[i] = M[i-1]; // (1,0) step case
        for (int j = 0; j <= i - 2; j++) // (1,1) and (1,-1) cases
            M[i] = (M[i] + (M[j] * M[i - 2 - j]) % mod) % mod;
    }
    return M;
}

// 2, 1, 3, 4, 7, 11, 18, 29, 47, 76
vector<long long> genLucas(int n, int mod) {
    vector<long long> L(n + 1);
    L[0] = 2; L[1] = 1;
    for (int i = 2; i <= n; i++)
        L[i] = (L[i-1] + L[i-2]) % mod;
    return L;
}

// Binomical Coeff nCk
long long C[5001][5001];
void precomputePascal(int n, int mod) {
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
    }
}

long long fact[1000001], invFact[1000001];

long long power(long long base, long long exp) {
    long long res = 1;
    base %= 1000000007;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % 1000000007;
        base = (base * base) % 1000000007;
        exp /= 2;
    }
    return res;
}

void precomputeNCR(int n, int mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (fact[i-1] * i) % mod;
    invFact[n] = power(fact[n], mod - 2); // Fermat's Little Theorem
    for (int i = n - 1; i >= 0; i--) invFact[i] = (invFact[i+1] * (i + 1)) % mod;
}

long long nCr(int n, int r, int mod) {
    if (r < 0 || r > n) return 0;
    return (((fact[n] * invFact[r]) % mod) * invFact[n-r]) % mod;
}

factorial[0] = 1;
for (int i = 1; i <= MAXN; i++) {
    factorial[i] = factorial[i - 1] * i % m;
}

// 1, 2, 4, 8, 16, 31, 57, 99, 163, 256
long long genMoser(int n) {
    if (n < 1) return 0;
    // Formula: nC4 + nC2 + 1
    return nCr(n, 4) + nCr(n, 2) + 1;
}

long long genNarayana(int n, int k, int mod) {
    if (k < 1 || k > n) return 0;
    long long res = (nCr(n, k, mod) * nCr(n, k - 1, mod)) % mod;
    return (res * power(n, mod - 2)) % mod; // Modular inverse of n
}

// The number of paths from (0,0) to (n,n) using only single steps and never crossing the line y=x
// 1, 2, 6, 22, 90, 394, 1806, 8558
vector<long long> genSchroder(int n, int mod) {
    vector<long long> s(n + 1, 0);
    s[0] = 1;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1]; // Diagonal step case
        for (int j = 0; j < i; j++) {
            s[i] = (s[i] + (s[j] * s[i - 1 - j]) % mod) % mod;
        }
    }
    return s;
}

// number of paths from (0,0) to (n,n) using only up and right is (2n)Cn
// other cases described by catalan, schroder, motzkin

// The number of permutations of 1 to n with k inversions
long long T[501][501];
void genInversions(int n, int k, int mod) {
    T[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        long long window_sum = 0;
        for (int j = 0; j <= k; j++) {
            window_sum = (window_sum + T[i-1][j]) % mod;
            if (j >= i) 
                window_sum = (window_sum - T[i-1][j-i] + mod) % mod;
            T[i][j] = window_sum;
        }
    }
}

// The number of paths from (0,0) to (n,m) using up, down or diagonal
long long D[1001][1001];
void genDelannoy(int n, int m, int mod) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) D[i][j] = 1;
            else D[i][j] = (D[i-1][j] + D[i][j-1] + D[i-1][j-1]) % mod;
        }
    }
}

// more fibonacci
struct matrix {
    long long mat[2][2];
    matrix friend operator *(const matrix &a, const matrix &b){
        matrix c;
        for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 2; j++) {
              c.mat[i][j] = 0;
              for (int k = 0; k < 2; k++) {
                  c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
              }
          }
        }
        return c;
    }
};

matrix matpow(matrix base, long long n) {
    matrix ans{ {
      {1, 0},
      {0, 1}
    } };
    while (n) {
        if(n&1)
            ans = ans*base;
        base = base*base;
        n >>= 1;
    }
    return ans;
}

long long fib(int n) {
    matrix base{ {
      {1, 1},
      {1, 0}
    } };
    return matpow(base, n).mat[0][1];
}

pair<int, int> fib (int n) {
    if (n == 0)
        return {0, 1};

    auto p = fib(n >> 1);
    int c = p.first * (2 * p.second - p.first);
    int d = p.first * p.first + p.second * p.second;
    if (n & 1)
        return {d, c + d};
    else
        return {c, d};
}

//TODO test and add more
