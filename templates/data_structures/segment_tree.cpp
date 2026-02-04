#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

class segment_tree {
private:
    struct Node {
        ll x;
        Node() {}
        Node(ll _x) : x(_x) {}
    };
    Node merge(Node x, Node y) {
        return Node(x.x + y.x);
    };

    ll n;
    Node neutral = Node(0);
    vector<ll> lazy;
    vector<Node> tree;

    void build(ll node, ll l, ll r, vector<ll>& a) {
        if (l == r) tree[node] = a[l];
        else {
            ll m = (l + r) >> 1;
            build(node<<1, l, m, a);
            build(node<<1|1, m+1, r, a);
            tree[node] = merge(tree[node<<1], tree[node<<1|1]);
        }
    }

    void apply(ll node, ll len, ll val) {
        tree[node].x += val * len;
        lazy[node] += val;
    }

    void push(ll node, ll l, ll r) {
        if (lazy[node] == 0 || l == r) return;
        ll m = (l + r) >> 1;
        apply(node<<1, m-l+1, lazy[node]);
        apply(node<<1|1, r-m, lazy[node]);
        lazy[node] = 0;
    }

    void update(ll node, ll l, ll r, ll ql, ll qr, ll val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) apply(node, r-l+1, val);
        else {
            push(node, l, r);
            ll m = (l + r) >> 1;
            update(node<<1, l, m, ql, qr, val);
            update(node<<1|1, m+1, r, ql, qr, val);
            tree[node] = merge(tree[node<<1], tree[node<<1|1]);
        }
    }

    Node query(ll node, ll l, ll r, ll ql, ll qr) {
        if (qr < l || r < ql) return neutral;
        if (ql <= l && r <= qr) return tree[node];
        push(node, l, r);
        ll m = (l + r) >> 1;
        return merge(query(node<<1, l, m, ql, qr), query(node<<1|1, m+1, r, ql, qr));
    }
public:
    segment_tree(vector<ll>& a) {
        n = a.size();
        tree = vector<Node>(4*n, neutral);
        lazy = vector<ll>(4*n, 0);
        build(1, 0, n-1, a);
    }
    void update(ll l, ll r, ll val) {update(1, 0, n-1, l, r, val);}
    ll query(ll l, ll r) {return query(1, 0, n-1, l, r).x;}
};

