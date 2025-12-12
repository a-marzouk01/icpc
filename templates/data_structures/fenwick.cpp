#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

template<typename T>
struct FenwickTree {
    ll n;
    vector<T> fenw;

    FenwickTree(ll n) : n(n), fenw(n + 1, T(0)) {}

    void update(ll i, T delta) {
        for (; i <= n; i += i & -i)
            fenw[i] += delta;
    }

    T query(ll i) {
        T sum = T(0);
        for (; i > 0; i -= i & -i)
            sum += fenw[i];
        return sum;
    }

    T rangeQuery(ll l, ll r) {
        return query(r) - query(l - 1);
    }

    ll lower_bound(T value) const { // first index with prefix sum >= value
        ll idx = 0;

        ll bitMask = 1;
        while ((bitMask << 1) <= n) bitMask <<= 1;
        
        for (; bitMask > 0; bitMask >>= 1) {
            ll next = idx + bitMask;
            if (next <= n && fenw[next] < value) {
                value -= fenw[next];
                idx = next;
            }
        }
        return idx + 1;
    }
};

int main() {
    ll n, q;
    cin >> n >> q;
    
    vector<ll> arr(n + 1);
    FenwickTree<ll> fenwick(n);

    // Read array and build Fenwick Tree
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        fenwick.update(i, arr[i]); // Initialize Fenwick Tree
    }

    while (q--) {
        ll type;
        cin >> type;

        if (type == 1) {
            // Update: Add x to arr[i]
            ll i, x;
            cin >> i >> x;
            fenwick.update(i, x);
        } 
        else if (type == 2) {
            // Range Query: Sum from l to r
            ll l, r;
            cin >> l >> r;
            cout << fenwick.rangeQuery(l, r) << "\n";
        }
    }

}
