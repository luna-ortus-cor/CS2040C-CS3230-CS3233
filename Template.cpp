#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define rep2(i, s, n) for(ll i = ll(s); i < ll(n); i++)
#define rep(i, n) rep2(i, 0, n)
#define rrep2(i, n, t) for(ll i = ll(n) - 1; i >= ll(t); i--)
#define rrep(i, n) rrep2(i, n, 0)
#define SZ(a) ll(a.size())
#define eb emplace_back
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (ll) (x).size()
#define f first
#define s second
#define mp make_pair
#define endl '\n'
#define sp <<" "<<
#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) + (m) - 1) / (m))
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define pow_mod(a, b, m) ([&](long long base, long long exp, long long mod){long long res=1; base%=mod; while(exp>0){if(exp&1)res=(res*base)%mod; base=(base*base)%mod; exp>>=1;} return res;})(a, b, m)
#define debug(x) cout << #x << ": " << (x) << "\n";
#define abs(x) (x<0?(-x):x) 
#define IN(i,l,r) (l<i&&i<r) 
#define LINR(i,l,r) (l<=i&&i<=r)
#define LIN(i,l,r) (l<=i&&i<r)
#define INR(i,l,r) (l<i&&i<=r)
#define F(i,L,R) for (int i = L; i < R; i++) 
#define FE(i,L,R) for (int i = L; i <= R; i++)
#define FF(i,L,R) for (int i = L; i > R; i--)
#define FFE(i,L,R) for (int i = L; i >= R; i--)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using P = pair<ll, ll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<P>;
using vvp = vector<vp>;
using str = string;
using vc = vector<char>;
using vs = vector<str>;
using vit = vector<int>::iterator;
using sll = set<ll>;
using sc = set<char>;
using mll = map<ll, ll>;
const ll inf = LLONG_MAX / 4;
const double eps = 1e-9;
const double PI = 3.1415926535897932384626433832795
bool chmin(auto& a, auto b) { return a > b ? a = b, 1 : 0; }
bool chmax(auto& a, auto b) { return a < b ? a = b, 1 : 0; }
ll gcd(ll a, ll b) { if (b==0) return a; return gcd(b, a%b); }
ll lcm(ll a, ll b) { return a/gcd(a,b)*b; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
const int fx[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
const int fxx[8][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    // your code here...
    return 0;
}

//TODO: add more + optimizations + any other uses of common c++ builtins
