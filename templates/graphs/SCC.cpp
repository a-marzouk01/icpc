#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct SCC {
    ll n;
    vector<vector<ll>> adj;

    vector<ll> disc, low, comp, stk;
    vector<bool> in_stk;

    ll timer = 0, ncomps = 0;

    SCC(ll n) : n(n) {
        adj.assign(n + 1, {});
        disc.assign(n + 1, 0);
        low.assign(n + 1, 0);
        comp.assign(n + 1, -1);
        in_stk.assign(n + 1, false);
    }

    void addEdge(ll u, ll v) {
        adj[u].push_back(v);
    }

    void dfs(ll u) {
        disc[u] = low[u] = ++timer;
        stk.push_back(u);
        in_stk[u] = true;

        for (ll v : adj[u]) {
            if (disc[v] == 0) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stk[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            while (true) {
                ll v = stk.back();
                stk.pop_back();
                in_stk[v] = false;
                comp[v] = ncomps;
                if (v == u) break;
            }
            ncomps++;
        }
    }

    vector<ll> build() {
        for (ll i = 1; i <= n; i++)
            if (disc[i] == 0)
                dfs(i);
        return comp;
    }
};

