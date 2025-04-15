#include <bits/stdc++.h>

typedef long long ll; 

const ll MAX = 1e6 + 10;
const ll MOD = 1e9 + 7;

using namespace std;

// returns the gcd of a and b
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// returns the lcm of a and b
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// a function for fast power, calculates bast to the power of exp mod by mod swiftly
ll modExp(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// a function that returns the inverse of a aka a^-1, note that mod must not be a multiple of a
ll modInv(ll a, ll mod) {
    return modExp(a, mod - 2, mod);
}

// a function that returns a vector stating wether a number is a prime or not, note max is limited to 1e6 or vector max
vector<bool> sieve(ll n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (ll j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }
    return isPrime;
}

// returns a vector containing the prime factors of x
vector<ll> primefactors(ll x) {
    vector<ll> factors;
    
    while (x % 2 == 0) {
        factors.push_back(2);
        x /= 2;
    }
    
    for (ll i = 3; i * i <= x; i += 2) {
        while (x % i == 0) {
            factors.push_back(i);
            x /= i;
        }
    }
    
    if (x > 2) {
        factors.push_back(x);
    }
    
    return factors;
}


vector<ll> fact(MAX), invFact(MAX);

// precompute the factorials with their inverses
void precomputeFactorials() {
    fact[0] = 1;
    for (ll i = 1; i < MAX; i++)
        fact[i] = (fact[i-1] * i) % MOD;
    
    invFact[MAX - 1] = modInv(fact[MAX - 1], MOD);
    for (ll i = MAX - 2; i >= 0; i--)
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
}

// calculates n choose k (how many ways we can get k from n)
ll nCk(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return ((fact[n] * invFact[k]) % MOD * invFact[n - k]) % MOD;
}

// calculates n permutation r (how many ways we can get r from n accouting for their permutations)
ll nPr(ll n, ll r){
    ll ans = 1;
    for (ll i = (n - r) + 1; i <= n; i++){
        ans *= i;
        ans %= MOD;
    }
    return ans;
}

//return sum of sequence a, a+x , a+2x .... b
ll sumSequence(ll a, ll b, ll x) {
    a = ((a + x - 1) / x) * x;
    b = (b / x) * x;
    return (b + a) * (b - a + x) / (2 * x);
}

// return a ^ 1 + a ^ 2 + a ^ 3 + .... a ^ k
// p = d * ((fast_power(d + 1, n) % MOD) - 1 - d);
// p /= d;
ll sumPower(ll a, ll k, int mod) {
    if (k == 1) return a % mod;
    ll half = sumPower(a, k / 2, mod);
    ll p = half * modExp(a, k / 2, mod) % mod;
    p = (p + half) % mod;
    if (k & 1) p = (p + modExp(a, k, mod)) % mod;
    return p;
}

// Returns minimum x for which a ^ x % m = b % m.
// a,m not not coprime
int getPower(int a, int b, int m) {
    a %= m, b %= m;
    int k = 1, add = 0, g;
    while ((g = __gcd(a, m)) > 1) {
        if (b == k)return add;
        if (b % g)return -1;
        b /= g, m /= g, ++add;
        k = (k * 1ll * a / g) % m;
    }
    int n = sqrt(m) + 1;
    int an = 1;
    for (int i = 0; i < n; ++i)
        an = (an * 1ll * a) % m;
    unordered_map<int, int> vals;
    for (int q = 0, cur = b; q <= n; ++q) {
        vals[cur] = q;
        cur = (cur * 1ll * a) % m;
    }
    for (int p = 1, cur = k; p <= n; ++p) {
        cur = (cur * 1ll * an) % m;
        if (vals.count(cur)) {
            int ans = n * p - vals[cur] + add;
            return ans;
        }
    }
    return -1;
}

int ceil(int n, int x) {
    return (n + x - 1)/x;
}

