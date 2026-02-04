#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct presistent_lichao {
    static const int N = (ll)1e5 + 9;
    const int mod = (ll)1e9 + 7;

    struct Line {
        ll k, d;
        ll eval(ll x) {
            return k * x + d;
        }
    };

    struct LiChaoNode {
        Line line;
        int l, r;
        LiChaoNode() {
            line = Line({0, numeric_limits<long long>::max() / 2});
            l = 0, r = 0;
        }
        LiChaoNode(Line line) : line(line), l(0), r(0) {}
    };

    static LiChaoNode t[50*N];
    static int T;
    static int upd(int pre, Line nw, int l, int r) {
        int m = (l + r) / 2;
        int id = ++T;
        t[id].line = t[pre].line;
        bool lef = nw.eval(l) < t[id].line.eval(l);
        bool mid = nw.eval(m) < t[id].line.eval(m);
        if(mid) swap(t[id].line, nw);
        if(l == r) return id;
        if(lef != mid) {
            if(!t[pre].l) t[id].l = ++T, t[T] = LiChaoNode(nw);
            else t[id].l = upd(t[pre].l, nw, l, m);
            t[id].r = t[pre].r;
        } else {
            if(!t[pre].r) t[id].r = ++T, t[T] = LiChaoNode(nw);
            else t[id].r = upd(t[pre].r, nw, m + 1, r);
            t[id].l = t[pre].l;
        }
        return id;
    }

    static ll Query(int cur, int x, int l, int r) {
        ll val = t[cur].line.eval(x);
        int m = (l + r) / 2;
        if(l < r) {
            if(x <= m && t[cur].l) val = min(val, Query(t[cur].l, x, l, m));
            if(x > m && t[cur].r) val = min(val, Query(t[cur].r, x, m + 1, r));
        }
        return val;
    }

    struct PersistentLiChaoTree {
        int L, R;
        vector<int> roots;
        PersistentLiChaoTree() {
            roots = {1};
            T = 1;
            L = -1e9;
            R = 1e9;
        }
        PersistentLiChaoTree(int L, int R) : L(L), R(R) {
            T = 1;
            roots.push_back(1);
        }
        void add_line(Line line) {
            int root = upd(roots.back(), line, L, R);
            roots.push_back(root);
        }
        ll query(int i, int x) {
            return Query(roots[i], x, L, R);
        }
    } lt;
};
presistent_lichao::LiChaoNode presistent_lichao::t[50*presistent_lichao::N];
int presistent_lichao::T;

int main() {
    presistent_lichao li;

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        int m, b;
        cin >> m >> b;

        li.lt.add_line({m, b});
    }

    for (int i = 0; i < q; i++) {
        int v, x;
        cin >> v >> x;

        cout << li.lt.query(v, x) << '\n';
    }
}
