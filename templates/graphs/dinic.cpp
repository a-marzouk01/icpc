// credit: https://github.com/cgmoreda/CP-Reference
#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

struct Dinic
{
	struct edge
	{
		ll to, rev;
		ll flow, w;
		ll id;
	};
	ll n, s, t, mxid;
	vector<ll> d, flow_through, done;
	vector<vector<edge>> g;

	Dinic()
	{
	}

	Dinic(ll _n)
	{
		n = _n + 10;
		mxid = 0;
		g.resize(n);
	}

	void add_edge(ll u, ll v, ll w, ll id = -1)
	{
		edge a = { v, (ll)g[v].size(), 0, w, id };
		edge b = { u, (ll)g[u].size(), 0, 0, -2 };//for bidirectional edges cap(b) = w  
		g[u].emplace_back(a);
		g[v].emplace_back(b);
		mxid = max(mxid, id);
	}

	bool bfs()
	{
		d.assign(n, -1);
		d[s] = 0;
		queue<ll> q;
		q.push(s);
		while (!q.empty())
		{
			ll u = q.front();
			q.pop();
			for (auto& e : g[u])
			{
				ll v = e.to;
				if (d[v] == -1 && e.flow < e.w) d[v] = d[u] + 1, q.push(v);
			}
		}
		return d[t] != -1;
	}

	ll dfs(ll u, ll flow)
	{
		if (u == t) return flow;
		for (ll& i = done[u]; i < (ll)g[u].size(); i++)
		{
			edge& e = g[u][i];
			if (e.w <= e.flow) continue;
			ll v = e.to;
			if (d[v] == d[u] + 1)
			{
				ll nw = dfs(v, min(flow, e.w - e.flow));
				if (nw > 0)
				{
					e.flow += nw;
					g[v][e.rev].flow -= nw;
					return nw;
				}
			}
		}
		return 0;
	}

	ll max_flow(ll _s, ll _t)
	{
		s = _s;
		t = _t;
		ll flow = 0;
		while (bfs())
		{
			done.assign(n, 0);
			while (ll nw = dfs(s, LLONG_MAX)) flow += nw;
		}
		flow_through.assign(mxid + 10, 0);
		for (ll i = 0; i < n; i++) for (auto e : g[i]) if (e.id >= 0) flow_through[e.id] = e.flow;
		return flow;
	}
};

