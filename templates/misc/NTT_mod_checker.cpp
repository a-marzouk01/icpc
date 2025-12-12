#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

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

bool isPrime(ll x) {
    if (x == 2) return true;
    if (x % 2 == 0 || x % 3 == 0 || x < 2) return false;

    for (ll i = 3; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

set<ll> primefactors(ll x) {
    set<ll> factors;
    while (x % 2 == 0) {
        factors.insert(2);
        x /= 2;
    }
    
    for (ll i = 3; i * i <= x; i += 2) {
        while (x % i == 0) {
            factors.insert(i);
            x /= i;
        }
    }
    
    if (x > 2) {
        factors.insert(x);
    }
    return factors;
}

void solve() {
    ll p;
    cin >> p;
    
    if (p < 3 || !isPrime(p)) {
        cout << "NO" << '\n';
        return;
    }
    
    ll me = p - 1;
    ll k = 0;
    while (me % 2 == 0) {me >>= 1; k++;}
    if (k == 0) {
        cout << "NO" << '\n';
    }

    cout << "YES" << '\n';
    ll ph = p - 1;
    auto thing = primefactors(ph); 
    ll g = 0;
    for (ll c = 2; c < p; c++) {
        ll val = 1;
        for (ll q : thing) {
            if (modExp(c, ph/q, p) == 1) {
                val = false;
                break;
            }
        }
        if (val) {
            g = c;
            break;
        }
    }

    cout << g << '\n';
}

