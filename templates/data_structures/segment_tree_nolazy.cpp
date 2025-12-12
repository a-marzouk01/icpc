#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

template<typename T>
struct segment_tree { // 1-indexed
	ll n;
	vector<T> tree;
	function<T(const T&, const T&)> merge;
	T neut;
 
	segment_tree(ll sz, function<T(const T&, const T&)> mer, T nu) {
		n = 1;
		while (n < sz) n *= 2;
		merge = mer;
		neut = nu;
 
		tree.assign(2*n, neut);
	}
 
	segment_tree(const vector<T> &arr, function<T(const T&, const T&)> mer, T nu) {
		ll sz = (ll) arr.size() - 1;
		n = 1;
		while (n < sz) n *= 2;
		merge = mer;
		neut = nu;
 
		tree.assign(2*n, neut);
		for (ll i = 1; i <= sz; i++) tree[n+i-1] = arr[i]	;
		for (ll i = n-1; i >= 1; i--) 
			tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
	}
 
	void update(ll idx, T val) {
		idx += n - 1;
		tree[idx] = val;
 
		while (idx > 1) {
			idx >>= 1;
			tree[idx] = merge(tree[idx<<1], tree[idx<<1 | 1]);
		}
	}
 
	T query(ll l, ll r) {
		ll o1 = neut, o2 = neut;
		l += n - 1;
		r += n - 1;
 
		while (l < r) {
			if (l & 1) o1 = merge(o1, tree[l++]);
			if (r & 1) o2 = merge(o2, tree[r--]);
 
			l >>= 1;
			r >>= 1;
		}
 
		return merge(o1, o2);
	}
};
 
int main() {
    ll n;
	cin >> n;
 
	vector<ll> a(n+1);
	for (ll i = 1; i <= n; i++) cin >> a[i];
 
	auto func = [](ll x, ll y) {return x + y;};
	segment_tree<ll> seg(a, func, 0);
 
	for (ll i = 2; i <= 4; i++) cout << a[i] << ' ';
	cout << '\n';
	cout << "2 -> 4: " << seg.query(2, 4) << '\n';
}
