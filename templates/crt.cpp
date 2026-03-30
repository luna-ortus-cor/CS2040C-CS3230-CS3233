struct Congruence {
    long long a, m;
};

long long chinese_remainder_theorem(vector<Congruence> const& congruences) {
    long long M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    long long solution = 0;
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a;
        long long M_i = M / congruence.m;
        long long N_i = mod_inv(M_i, congruence.m);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}





#include <iostream>
#include <vector>
#include <numeric>

typedef long long vlong;

// Extended Euclidean Algorithm to find x, y such that ax + by = gcd(a, b)
vlong ext_gcd(vlong a, vlong b, vlong &x, vlong &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    vlong x1, y1;
    vlong gcd = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return gcd;
}

// Modular inverse
vlong modInverse(vlong a, vlong m) {
    vlong x, y;
    vlong g = ext_gcd(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

// Function to solve CRT: x = r_i (mod m_i)
// Returns {solution, LCM_of_moduli}
std::pair<vlong, vlong> solveCRT(const std::vector<vlong>& r, const std::vector<vlong>& m) {
    if (r.empty()) return {0, 1};
    vlong r1 = r[0];
    vlong m1 = m[0];

    for (size_t i = 1; i < r.size(); i++) {
        vlong r2 = r[i];
        vlong m2 = m[i];
        
        vlong p, q;
        vlong g = ext_gcd(m1, m2, p, q);

        // Check solvability: r1 = r2 (mod gcd(m1, m2))
        if ((r1 - r2) % g != 0) return {-1, -1};

        // Merge equations
        vlong lcm = (m1 / g) * m2;
        // Using __int128 to prevent overflow during intermediate steps
        __int128 temp_r = (__int128)r1 + (__int128)m1 * (( (__int128)(r2 - r1) / g * p ) % (m2 / g));
        r1 = (long long)((temp_r % lcm + lcm) % lcm);
        m1 = lcm;
    }
    return {r1, m1};
}

int main() {
    // Example: 
    // x = 2 (mod 3)
    // x = 3 (mod 5)
    // x = 2 (mod 7)
    std::vector<vlong> rem = {2, 3, 2};
    std::vector<vlong> mod = {3, 5, 7};
    
    std::pair<vlong, vlong> result = solveCRT(rem, mod);
    
    if (result.first == -1) std::cout << "No Solution" << std::endl;
    else std::cout << "x = " << result.first << " (mod " << result.second << ")" << std::endl;
    // Output: x = 23 (mod 105)

    return 0;
}
