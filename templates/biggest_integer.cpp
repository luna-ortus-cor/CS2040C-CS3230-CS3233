#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <complex>
#include <cmath>
#include <cstdint>
typedef std::complex<double> cd;
typedef long long ll;
const double PI = acos(-1.0);
using namespace std;

// To try implementing using NTT instead
void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) for (cd& x : a) x /= n;
}

class ArbitraryInteger {
private:
    static const int BASE = 1e9;
    vector<int> digits;
    bool is_negative;

    void trim() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        if (digits.empty()) {
            digits = {0};
            is_negative = false;
        }
        if (digits.size() == 1 && digits[0] == 0) is_negative = false;
    }

public:
    // Constructors
    ArbitraryInteger(long long v = 0) {
        if (v < 0) is_negative = true, v = -v;
        else is_negative = false;
        if (v == 0) digits.push_back(0);
        while (v > 0) {
            digits.push_back(v % BASE);
            v /= BASE;
        }
    }

    ArbitraryInteger(string s) {
        if (s.empty()) { digits = {0}; is_negative = false; return; }
        if (s[0] == '-') { is_negative = true; s = s.substr(1); }
        else is_negative = false;
        for (int i = s.size(); i > 0; i -= 9) {
            if (i < 9) digits.push_back(stoi(s.substr(0, i)));
            else digits.push_back(stoi(s.substr(i - 9, 9)));
        }
        trim();
    }

    ll to_long_long() const {
        ll res = 0, p = 1;
        for (int x : digits) {
            res += x * p;
            p *= BASE;
        }
        return is_negative ? -res : res;
    }

    ArbitraryInteger split_low(int n) const {
        if (n <= 0) return 0;
        if (n >= (int)digits.size()) return *this;
        ArbitraryInteger res;
        res.digits = vector<int>(digits.begin(), digits.begin() + n);
        res.is_negative = is_negative;
        res.trim();
        return res;
    }

    ArbitraryInteger split_high(int n) const {
        if (n <= 0) return *this;
        if (n >= (int)digits.size()) return 0;
        ArbitraryInteger res;
        res.digits = vector<int>(digits.begin() + n, digits.end());
        res.is_negative = is_negative;
        res.trim();
        return res;
    }

    // Comparison Operators
    bool operator<(const ArbitraryInteger& other) const {
        if (is_negative != other.is_negative) return is_negative;
        if (digits.size() != other.digits.size())
            return is_negative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i])
                return is_negative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator==(const ArbitraryInteger& other) const {
        return is_negative == other.is_negative && digits == other.digits;
    }

    bool operator<=(const ArbitraryInteger& other) const { return *this < other || *this == other; }
    bool operator>(const ArbitraryInteger& other) const { return !(*this <= other); }
    bool operator>=(const ArbitraryInteger& other) const { return !(*this < other); }

    // Parity
    bool is_even() const { return digits[0] % 2 == 0; }
    bool is_odd() const { return !is_even(); }

    // Addition & Subtraction
    ArbitraryInteger operator+(const ArbitraryInteger& other) const {
        if (is_negative == other.is_negative) {
            ArbitraryInteger res = *this;
            int carry = 0;
            for (size_t i = 0; i < max(res.digits.size(), other.digits.size()) || carry; ++i) {
                if (i == res.digits.size()) res.digits.push_back(0);
                long long cur = (long long)res.digits[i] + carry + (i < other.digits.size() ? other.digits[i] : 0);
                res.digits[i] = cur % BASE;
                carry = cur / BASE;
            }
            return res;
        }
        return *this - (-other);
    }

    ArbitraryInteger operator-() const {
        ArbitraryInteger res = *this;
        if (res != 0) res.is_negative = !res.is_negative;
        return res;
    }

    ArbitraryInteger operator-(const ArbitraryInteger& other) const {
        if (is_negative != other.is_negative) return *this + (-other);
        if (abs_less(other)) return -(other - *this);
        
        ArbitraryInteger res = *this;
        int carry = 0;
        for (size_t i = 0; i < other.digits.size() || carry; ++i) {
            long long cur = res.digits[i] - carry - (i < other.digits.size() ? other.digits[i] : 0);
            carry = cur < 0;
            if (carry) cur += BASE;
            res.digits[i] = cur;
        }
        res.trim();
        return res;
    }

    // Multiplication
    ArbitraryInteger operator*(const ArbitraryInteger& other) const {
        ArbitraryInteger res;
        res.digits.resize(digits.size() + other.digits.size(), 0);
        res.is_negative = is_negative != other.is_negative;
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                long long cur = res.digits[i + j] + digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                res.digits[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }
        res.trim();
        return res;
    }

    // Integer Division and Modulo
    friend pair<ArbitraryInteger, ArbitraryInteger> divmod(ArbitraryInteger a, ArbitraryInteger b) {
        if (b == 0) throw runtime_error("Division by zero");
        bool res_neg = a.is_negative != b.is_negative;
        bool rem_neg = a.is_negative;
        a.is_negative = b.is_negative = false;

        ArbitraryInteger q, r;
        for (int i = a.digits.size() - 1; i >= 0; i--) {
            r = r * BASE + a.digits[i];
            int low = 0, high = BASE - 1, best = 0;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (b * mid <= r) { best = mid; low = mid + 1; }
                else high = mid - 1;
            }
            q.digits.push_back(best);
            r = r - b * best;
        }
        reverse(q.digits.begin(), q.digits.end());
        q.is_negative = res_neg; q.trim();
        r.is_negative = rem_neg; r.trim();
        return {q, r};
    }

    ArbitraryInteger operator/(const ArbitraryInteger& b) const { return divmod(*this, b).first; }
    ArbitraryInteger operator%(const ArbitraryInteger& b) const { return divmod(*this, b).second; }

    // Floating point-like division (string result)
    string divide_to_decimal(ArbitraryInteger b, int precision) const {
        ArbitraryInteger a = *this;
        pair<ArbitraryInteger, ArbitraryInteger> dm = divmod(a, b);
        string res = dm.first.to_string() + ".";
        ArbitraryInteger rem = dm.second;
        rem.is_negative = false;
        b.is_negative = false;

        for (int i = 0; i < precision; i++) {
            rem = rem * 10;
            pair<ArbitraryInteger, ArbitraryInteger> next_dm = divmod(rem, b);
            res += std::to_string(next_dm.first.digits[0]);
            rem = next_dm.second;
        }
        return res;
    }

    // Fast Exponentiation
    ArbitraryInteger pow(ArbitraryInteger exp) const {
        ArbitraryInteger res = 1, base = *this;
        while (exp > 0) {
            if (exp.is_odd()) res = res * base;
            base = base * base;
            exp = exp / 2;
        }
        return res;
    }

    // Modular Exponentiation
    ArbitraryInteger powMod(ArbitraryInteger exp, const ArbitraryInteger& mod) const {
        ArbitraryInteger res = 1, base = *this % mod;
        while (exp > 0) {
            if (exp.is_odd()) res = (res * base) % mod;
            base = (base * base) % mod;
            exp = exp / 2;
        }
        return res;
    }

    // Exxtended Euclidean Algorithm
    static ArbitraryInteger extended_gcd(ArbitraryInteger a, ArbitraryInteger b, ArbitraryInteger &x, ArbitraryInteger &y) {
        if (a == 0) { x = 0; y = 1; return b; }
        ArbitraryInteger x1, y1;
        ArbitraryInteger d = extended_gcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }

    // Modular Inverse
    static ArbitraryInteger modInverse(ArbitraryInteger a, ArbitraryInteger m) {
        ArbitraryInteger x, y;
        ArbitraryInteger g = extended_gcd(a, m, x, y);
        if (g != 1) throw runtime_error("Inverse doesn't exist");
        return (x % m + m) % m;
    }

    // GCD & LCM
    static ArbitraryInteger gcd(ArbitraryInteger a, ArbitraryInteger b) {
        a.is_negative = b.is_negative = false;
        while (b != 0) { a = a % b; swap(a, b); }
        return a;
    }

    static ArbitraryInteger lcm(ArbitraryInteger a, ArbitraryInteger b) {
        if (a == 0 || b == 0) return 0;
        return (a * b) / gcd(a, b);
    }

    // String conversion
    string to_string() const {
        if (digits.empty()) return "0";
        string s = is_negative ? "-" : "";
        s += std::to_string(digits.back());
        for (int i = digits.size() - 2; i >= 0; i--) {
            string t = std::to_string(digits[i]);
            s += string(9 - t.size(), '0') + t;
        }
        return s;
    }

    // O(n^1.58) multiplication
    static ArbitraryInteger karatsuba(ArbitraryInteger x, ArbitraryInteger y) {
        int n = max(x.digits.size(), y.digits.size());
        if (n <= 32) return x * y; // Fallback to O(n^2) for small sizes
    
        n = (n + 1) / 2;
        ArbitraryInteger x_high = x.split_high(n);
        ArbitraryInteger x_low = x.split_low(n);
        ArbitraryInteger y_high = y.split_high(n);
        ArbitraryInteger y_low = y.split_low(n);
    
        ArbitraryInteger a = karatsuba(x_high, y_high);
        ArbitraryInteger b = karatsuba(x_low, y_low);
        ArbitraryInteger c = karatsuba(x_high + x_low, y_high + y_low);
    
        return a.shift(2 * n) + (c - a - b).shift(n) + b;
    }
    
    // Helper: shifts by 'n' digits in BASE 10^9
    ArbitraryInteger shift(int n) const {
        if (n <= 0 || (digits.size() == 1 && digits[0] == 0)) return *this;
        ArbitraryInteger res = *this;
        res.digits.insert(res.digits.begin(), n, 0);
        return res;
    }

    // O(nlogn) multiplication (Strassen Algorithm)
    static ArbitraryInteger fft_multiply(const ArbitraryInteger& a, const ArbitraryInteger& b) {
        vector<cd> fa(a.digits.begin(), a.digits.end()), fb(b.digits.begin(), b.digits.end());
        int n = 1;
        while (n < a.digits.size() + b.digits.size()) n <<= 1;
        fa.resize(n); fb.resize(n);
    
        fft(fa, false); fft(fb, false);
        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        fft(fa, true);
    
        ArbitraryInteger res; res.digits.resize(n);
        ll carry = 0;
        for (int i = 0; i < n; i++) {
            ll val = (ll)(fa[i].real() + 0.5) + carry;
            res.digits[i] = val % BASE;
            carry = val / BASE;
        }
        res.trim();
        return res;
    }

    // Convert Base 10^9 -> Base 2 (vector<uint32_t>)
    vector<uint32_t> to_binary() const {
        vector<uint32_t> binary;
        ArbitraryInteger temp = *this;
        temp.is_negative = false;
        while (temp > 0) {
            // Repeatedly divide by 2^32 and take remainder
            pair<ArbitraryInteger, ArbitraryInteger> dm = divmod(temp, 4294967296LL);
            binary.push_back((uint32_t)dm.second.to_long_long());
            temp = dm.first;
        }
        return binary;
    }
    
    // Convert Base 2 -> Base 10^9
    static ArbitraryInteger from_binary(const vector<uint32_t>& binary) {
        ArbitraryInteger res = 0, power = 1;
        ArbitraryInteger two_32 = 4294967296LL;
        for (uint32_t val : binary) {
            res = res + (power * (long long)val);
            power = power * two_32;
        }
        return res;
    }

    // Bitwise AND
    ArbitraryInteger operator&(const ArbitraryInteger& other) const {
        vector<uint32_t> a = this->to_binary();
        vector<uint32_t> b = other.to_binary();
        vector<uint32_t> res_bin(min(a.size(), b.size()));
        for (size_t i = 0; i < res_bin.size(); i++) {
            res_bin[i] = a[i] & b[i];
        }
        return from_binary(res_bin);
    }

    // Bitwise OR
    ArbitraryInteger operator|(const ArbitraryInteger& other) const {
        vector<uint32_t> a = this->to_binary();
        vector<uint32_t> b = other.to_binary();
        size_t n = max(a.size(), b.size());
        vector<uint32_t> res_bin(n);
        for (size_t i = 0; i < n; i++) {
            uint32_t va = (i < a.size()) ? a[i] : 0;
            uint32_t vb = (i < b.size()) ? b[i] : 0;
            res_bin[i] = va | vb;
        }
        ArbitraryInteger res = from_binary(res_bin);
        res.is_negative = (this->is_negative || other.is_negative); // Logical simplification
        return res;
    }
    
    // Bitwise XOR
    ArbitraryInteger operator^(const ArbitraryInteger& other) const {
        vector<uint32_t> a = this->to_binary();
        vector<uint32_t> b = other.to_binary();
        size_t n = max(a.size(), b.size());
        vector<uint32_t> res_bin(n);
        for (size_t i = 0; i < n; i++) {
            uint32_t va = (i < a.size()) ? a[i] : 0;
            uint32_t vb = (i < b.size()) ? b[i] : 0;
            res_bin[i] = va ^ vb;
        }
        return from_binary(res_bin);
    }
    
    // Bitwise NOT (Python Style)
    ArbitraryInteger operator~() const {
        return -(*this + 1);
    }

    // Helper for shifting (Power of 2)
    static ArbitraryInteger powerOfTwo(int n) {
        ArbitraryInteger res = 1, base = 2;
        while (n > 0) {
            if (n & 1) res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
    
    // Left Shift (x << n  =>  x * 2^n)
    ArbitraryInteger operator<<(int n) const {
        if (n < 0) return *this >> (-n);
        if (n == 0) return *this;
        return (*this) * powerOfTwo(n);
    }
    
    // Right Shift (x >> n  =>  x / 2^n)
    ArbitraryInteger operator>>(int n) const {
        if (n < 0) return *this << (-n);
        if (n == 0) return *this;
        ArbitraryInteger res = (*this) / powerOfTwo(n);
        // Python handles right shifts of negative numbers by rounding toward negative infinity
        // TODO: Implement one following C++ standard?
        if (this->is_negative && (*this % powerOfTwo(n)) != 0) {
            res = res - 1;
        }
        return res;
    }

private:
    bool abs_less(const ArbitraryInteger& other) const {
        if (digits.size() != other.digits.size()) return digits.size() < other.digits.size();
        for (int i = digits.size() - 1; i >= 0; i--)
            if (digits[i] != other.digits[i]) return digits[i] < other.digits[i];
        return false;
    }
};

int main() {
    // Enable fast I/O for large number printing
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. Initialize two large numbers
    ArbitraryInteger a("123456789012345678901234567890");
    ArbitraryInteger b("98765432109876543210987654321");

    cout << "--- Basic Arithmetic ---" << endl;
    cout << "A: " << a.to_string() << endl;
    cout << "B: " << b.to_string() << endl;
    cout << "A + B: " << (a + b).to_string() << endl;
    cout << "A - B: " << (a - b).to_string() << endl;
    cout << "A * B: " << (a * b).to_string() << endl; // Tests O(N^2) or Karatsuba
    
    auto dm = divmod(a, b);
    cout << "A / B: " << dm.first.to_string() << endl;
    cout << "A % B: " << dm.second.to_string() << endl;

    cout << "\n--- Precision Division ---" << endl;
    // Calculate A / B up to 20 decimal places
    cout << "A / B (20 decimal places): " << a.divide_to_decimal(b, 20) << endl;

    cout << "\n--- Bitwise Operations (Python Style) ---" << endl;
    ArbitraryInteger c("123456789012345678901234567890");
    ArbitraryInteger d("98765432109876543210987654321");
    cout << "C: " << c.to_string() << endl;
    cout << "D: " << d.to_string() << endl;
    cout << "C & D: " << (c & d).to_string() << endl;
    cout << "C | D: " << (c | d).to_string() << endl;
    cout << "C ^ D: " << (c ^ d).to_string() << endl;
    cout << "~C:    " << (~c).to_string() << endl;

    cout << "\n--- Shifts and Powers ---" << endl;
    ArbitraryInteger e(2);
    ArbitraryInteger f("6666666666667777777777");
    cout << "E: " << e.to_string() << endl;
    cout << "F: " << f.to_string() << endl;
    cout << "E << 1000: " << (e << 1000).to_string() << endl;
    cout << "F >> 5:    " << (f >> 5).to_string() << endl;
    cout << endl;
    
    ArbitraryInteger g(7);
    ArbitraryInteger h(100);
    ArbitraryInteger i("100000000000000000000007");
    cout << "G: " << g.to_string() << endl;
    cout << "H: " << h.to_string() << endl;
    cout << "I: " << i.to_string() << endl;
    cout << "G^H mod I: " << g.powMod(h, i).to_string() << endl;

    cout << "\n--- Number Theory & Relational ---" << endl;
    ArbitraryInteger j("420420420420420420420420420420");
    ArbitraryInteger k("69696969696969696969");
    cout << "J: " << j.to_string() << endl;
    cout << "K: " << k.to_string() << endl;
    cout << "GCD(J, K): " << ArbitraryInteger::gcd(j, k).to_string() << endl;
    cout << "Is J > K? " << (j > k ? "Yes" : "No") << endl;
    cout << "Is J even? " << (j.is_even() ? "Yes" : "No") << endl;

    return 0;
}
