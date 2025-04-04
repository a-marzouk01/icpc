#include <bits/stdc++.h>

typedef long long ll; 

using namespace std;

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
