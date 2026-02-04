#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll INF = -(1LL << 62);
struct line {
    ll m, b;
    mutable function<const line*() > succ;
    bool operator < (const line& rhs) const {
        if (rhs.b != INF) return m < rhs.m;
        const line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct CHT : public multiset<line> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y -> m == z -> m && y -> b <= z -> b;
        }
        auto x = prev(y);
        if (z == end()) return y -> m == x -> m && y -> b <= x -> b;
        return 1.0 * (x -> b - y -> b) * (z -> m - y -> m) >= 1.0 * (y -> b - z -> b) * (y -> m - x -> m);
    }
    void add(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=, this] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound((line) {
                x, INF
                });
        return l.m * x + l.b;
    }
};
