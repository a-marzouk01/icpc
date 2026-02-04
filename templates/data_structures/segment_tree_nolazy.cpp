#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct segment_tree {
    struct Node {
        ll x;
        Node() {}
        Node(ll _x) : x(_x) {}
    };
    Node merge(Node x, Node y) {
        return x.x + y.x;
    }

    ll n;
    Node neutral = Node(0);
    vector<Node> tree;

    segment_tree(vector<ll>& a) {
        n = 1;
        while (n < (ll)a.size()) n <<= 1;
        tree = vector<Node>(2*n, neutral);

        for (ll i = 0; i < (ll)a.size(); i++) tree[n+i] = Node(a[i]);
        for (ll i = n-1; i > 0; i--) 
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]); 
    }

    void update(ll idx, ll val) {
        idx += n;
        tree[idx] = Node(val);

        for (idx >>= 1; idx > 0; idx >>= 1)
            tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
    }

    ll query(ll l, ll r) {
        l += n, r += n;

        Node r1, r2;
        r1 = r2 = neutral;
        while (l <= r) {
            if (l & 1) r1 = merge(r1, tree[l++]);
            if (!(r & 1)) r2 = merge(tree[r--], r2);

            l >>= 1, r >>= 1;
        }
        Node ret = merge(r1, r2);
        return ret.x;
    }
};

