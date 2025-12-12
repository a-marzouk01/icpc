#include <bits/stdc++.h>

typedef long long ll; 

using namespace std;

long long INF = 1e9 + 5;

void dfs(ll node, const vector<vector<ll>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (ll neighbor : adj[node])
        if (!visited[neighbor])
            dfs(neighbor, adj, visited);
}

vector<ll> bfs(ll source, const vector<vector<ll>>& adj) {
    ll n = adj.size();
    vector<ll> dist(n, -1);
    queue<ll> q;
    dist[source] = 0;
    q.push(source);
    while(!q.empty()){
        ll u = q.front(); q.pop();
        for (ll v : adj[u])
            if(dist[v] == -1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
    return dist;
}

vector<ll> dijkstra(ll source, const vector<vector<pair<ll, ll>>>& graph) {
    ll n = graph.size();
    vector<ll> dist(n, LLONG_MAX);
    priority_queue<pair<ll, ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    dist[source] = 0;
    pq.push({0, source});
    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : graph[u])
            if (dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }
    return dist;
}

// maximum biparitite matching 

// O(sqrt(V)·E) time, O(V+E) space
struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> dist, pairU, pairV;

    HopcroftKarp(int _n, int _m) : n(_n), m(_m), adj(n+1), dist(n+1), pairU(n+1, 0), pairV(m+1, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for(int u = 1; u <= n; ++u) {
            if(pairU[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        int distInf = INF;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if(dist[u] < distInf) {
                for(int v: adj[u]) {
                    if(pairV[v] == 0) {
                        distInf = dist[u] + 1;
                    } else if(dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return distInf != INF;
    }

    bool dfs(int u) {
        for(int v: adj[u]) {
            if(pairV[v] == 0 
               || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }

    int maxMatching() {
        int matching = 0;
        while(bfs()) {
            for(int u = 1; u <= n; ++u)
                if(pairU[u] == 0 && dfs(u))
                    matching++;
        }
        return matching;
    }
};
