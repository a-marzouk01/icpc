#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

class Hashed {
private:
    static const ll M = (1LL << 61) - 1;
    static const ll B;

    static vector<ll> pow;
    vector<ll> p_hash;

    __int128 mul(ll a, ll b) { return (__int128)a * b; }
    ll mmul(ll a, ll b) { return mul(a, b) % M; }

public:
    Hashed(const string &s) : p_hash(s.size() + 1) {
        while (pow.size() < s.size()) { pow.push_back(mmul(pow.back(), B)); }
        p_hash[0] = 0;
        for (ll i = 0; i < (ll)s.size(); i++) {
            p_hash[i + 1] = (mul(p_hash[i], B) + s[i]) % M;
        }
    }

    ll get(ll l, ll r) {
        ll val = p_hash[r + 1] - mmul(p_hash[l], pow[r - l + 1]);
        return (val + M) % M;
    }
};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
vector<ll> Hashed::pow = {1};
const ll Hashed::B = uniform_int_distribution<ll>(0, M - 1)(rng);

