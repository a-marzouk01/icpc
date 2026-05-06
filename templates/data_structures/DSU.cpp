#include <bits/stdc++.h> // Marzouk <3
#pragma GCC optimize("Ofast")
using namespace std;
typedef int64_t ll;

struct DSU {
    int N;
    vector<int> par, sz;
    DSU(int n) {
        N = n;
        par = sz = vector<int>(N+1, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int u) {
        if (par[u] == u) return u;
        return par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
        return 1;
    }
};
