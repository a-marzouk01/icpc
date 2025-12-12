#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

const ll MOD = 998244353;
const ll G = 3;

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

ll modInv(ll a, ll mod) {
    return modExp(a, mod - 2, mod);
}

void NTT(vector<ll>& f, bool flag) {
    ll n = (ll) f.size();

    for (ll i = 0, j = 0; i < n; i++) {
        if (i < j) swap(f[i], f[j]);
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
    }


    for (ll len = 2; len <= n; len <<= 1) { // current level
        ll w1 = modExp(G, (MOD-1) / len, MOD);
        if (flag) w1 = modInv(w1, MOD);

        for (ll p = 0; p < n; p += len) { // current polynomial
            ll w0 = 1;
            for (ll i = 0; i < len/2; i++) { // current element in the polynomial
                ll tmp = f[p + i];
                f[p + i] = f[p + i] + (w0 * f[len/2 + p + i]) % MOD;
                if (f[p + i] >= MOD) f[p + i] -= MOD;
                f[len/2 + p + i] = tmp - (w0 * f[len/2 + p + i]) % MOD;
                if (f[len/2 + p + i] < 0) f[len/2 + p + i] += MOD;

                w0 = w0 * w1 % MOD;
            }
        }
    }

    if (flag) {
        ll inv = modInv(n, MOD);
        for (ll i = 0; i < n; i++) f[i] = f[i] * inv % MOD;
    }
}

vector<ll> multiply(vector<ll>& a, vector<ll>& b) {
    ll n = 1;
    while (n < (ll) a.size() + (ll) b.size()) n <<= 1;

    vector<ll> fa(n);
    vector<ll> fb(n);
    for (ll i = 0; i < (ll)a.size(); i++) {
        fa[i] = a[i] % MOD;
        if (fa[i] < 0) fa[i] += MOD;
    }
    for (ll i = 0; i < (ll)b.size(); i++) {
        fb[i] = b[i] % MOD;
        if (fb[i] < 0) fb[i] += MOD;
    }

    NTT(fa, 0), NTT(fb, 0);
    for (ll i = 0; i < n; i++) fa[i] = (fa[i] * fb[i]) % MOD;
    NTT(fa, 1);

    vector<ll> ret(n);
    for (ll i = 0; i < n; i++) ret[i] = fa[i];
    return ret;
}
