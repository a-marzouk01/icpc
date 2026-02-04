#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

struct LCA {
    vector<vector<ll>> adj;

    ll n, LG;
    vector<ll> depth;
    vector<vector<ll>> up;

    LCA(vector<vector<ll>>& x) {
        adj = x;
        n = adj.size()-1;

        LG = __lg(n) + 1;
        depth = vector<ll>(n+1);
        up = vector<vector<ll>>(n+1, vector<ll>(LG+1));

        dfs(1, 0);

        for (ll k = 1; k <= LG; k++) {
            for (ll u = 1; u <= n; u++) {
                up[u][k] = up[up[u][k-1]][k-1];
            }
        }
    }

    void dfs(ll u, ll p){
        depth[u] = 0;
        up[u][0] = p;

        queue<ll> q;
        q.push(u);

        vector<ll> vis(n+1, 0);
        vis[u] = 1;
        while (q.size()) {
            ll v = q.front();
            q.pop(); 
            
            for (ll w : adj[v]) {
                if (!vis[w]) {
                    vis[w] = true;
                    depth[w] = depth[v] + 1;
                    up[w][0] = v;
                    q.push(w);
                }
            }
        }
    }

    ll kth(ll u, ll p) {
        for (ll k = LG; k >= 0; k--) if (p & (1 << k)) u = up[u][k];
        return u;
    }

    ll query(ll u, ll v) {
        if (depth[u] < depth[v]) swap(u, v);

        ll diff = depth[u] - depth[v];
        for (ll k = LG; k >= 0; k--) if (diff & (1 << k)) u = up[u][k];

        if (u == v) return u;
        for (ll k = LG; k >= 0; k--) {
            if (up[u][k] != up[v][k]) {
                u = up[u][k];
                v = up[v][k];
            }
        }
        return up[u][0];
    }

    ll dist(ll u, ll v) {
        return depth[u] + depth[v] - 2 * depth[query(u, v)];
    }
};

