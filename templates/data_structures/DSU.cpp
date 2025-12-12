#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct dsu {
    ll n, forests;
    vector<ll> sz, parent, rnk;

    dsu(ll nn) {
        n = nn;
        forests = nn;
        sz = rnk = parent = vector<ll>(n+1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    ll find(ll u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    ll same(ll u, ll v) {
        return find(u) == find(v);
    }

    void link(ll u, ll v) {
        parent[v] = u;
        sz[u] += sz[v];

        if (rnk[u] == rnk[v]) rnk[u]++;
        forests--;
    }

    bool merge(ll u, ll v) {
        u = find(u);
        v = find(v);

        if (u == v) return false;
        if (rnk[u] < rnk[v]) swap(u, v);
        link(u, v);

        return true;
    }
};
