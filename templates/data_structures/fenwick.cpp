#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct BIT {
    vector<ll> tree;

    BIT(ll n) {tree = vector<ll>(n+1, 0);}

    void update(ll idx, ll val) {
        for (; idx < (ll)tree.size(); idx += idx & -idx) tree[idx] += val;
    }

    ll query(ll r) {
        ll ret = 0;
        for (; r > 0; r -= r & -r) ret += tree[r];
        return ret;
    }
};

