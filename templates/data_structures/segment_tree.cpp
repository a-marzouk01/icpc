#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
template<typename T>
struct segment_tree { // 1-indexed
	ll n;
	vector<T> tree;
	vector<ll> lazy;
	function<T(const T&, const T&)> merge;
	T neut;
 
	segment_tree(ll sz, function<T(const T&, const T&)> mer, T nu) {
		n = 1;
		while (n < sz) n *= 2;
		merge = mer;
		neut = nu;
 
		tree.assign(2*n, neut);
		lazy.assign(2*n, 0);
	}
 
	segment_tree(const vector<T> &arr, function<T(const T&, const T&)> mer, T nu) {
		ll sz = (ll) (arr.size()) - 1;
		n = 1;
		while (n < sz) n *= 2;
		merge = mer;
		neut = nu;
 
		tree.assign(2*n, neut);
		lazy.assign(2*n, 0);
 
		for (ll i = 1; i <= sz; i++) tree[n+i-1] = arr[i];
		for (ll i = n-1; i >= 1; i--) tree[i] = merge(tree[i<<1], tree[i<<1 | 1]);
	}
 
	inline void apply(ll p, ll len, T val) {
		tree[p] += val * len;
		if (p < n) lazy[p] += val;
	}
 
	inline void push(ll p, ll len) {
		if (!lazy[p]) return;
 
		ll m = len >> 1;
		apply(p<<1    , m, lazy[p]);
		apply(p<<1 | 1, m, lazy[p]);
 
		lazy[p] = 0;
	}
 
	void update(ll l, ll r, ll val, ll p, ll tl, ll tr) {
		if (l >= tr || r <= tl) return;
		if (l <= tl && tr <= r) {
			apply(p, tr - tl, val);
			return;
		}
 
		push(p, tr - tl);
 
		ll m = (tr + tl) >> 1;
		update(l, r, val, p<<1    , tl, m);
		update(l, r, val, p<<1 | 1, m, tr);
 
		tree[p] = merge(tree[p<<1], tree[p<<1 | 1]);
	}
 
	T query(ll l, ll r, ll p, ll tl, ll tr) {
		if (l >= tr || r <= tl) return neut;
		if (l <= tl && tr <= r) return tree[p];
 
		push(p, tr-tl);
 
		ll m = (tr + tl) >> 1;
		return merge(query(l, r, p<<1, tl, m), query(l, r, p<<1 | 1, m, tr));
	}
 
	void update(ll l, ll r, T val) {
		if (l > r) return;
		update(l-1, r, val, 1, 0, n);
	}
 
	T query(ll l, ll r) {
		if (l > r) return neut;
		return 	query(l-1, r, 1, 0, n);
	}
};
 
 
// NOTES:-
// - for range assign just remove the 2 pluses in apply()
// 		tree[p] = val * len;
//		if (p < n) lazy[p] = val;
//
// - for any merge operation other than sum remove the * len in apply()
// 		tree[p] += val;
//		if (p < n) lazy[p] += val;
