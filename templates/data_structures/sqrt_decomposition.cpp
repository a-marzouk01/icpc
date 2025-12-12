#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

class sqrt_decomposition {
private:
    ll n;
    ll sq;
    vector<ll> arr, blk;
    vector<vector<ll>> blocks;

public:
    void build(vector<ll>& a) {
        n = (ll) a.size();
        sq = sqrtl((ld)(n))+1;

        arr = a;
        blk.assign((n+sq-1)/sq, 0);
        blocks.assign((n+sq-1)/sq, vector<ll>());

        for (ll i = 0; i < n; i++) {
            blk[i/sq] += a[i];
            blocks[i/sq].push_back(a[i]);
        }
    }

    void update(ll idx, ll val) {
        ll bi = idx/sq;
        ll pos = idx - bi * sq;
        auto &v = blocks[bi];

        blk[bi] -= arr[idx];
        arr[idx] = val;
        v[pos] = val;
        blk[bi] += arr[idx];
    }

    ll query(ll l, ll r) {
        ll ans = 0;

        for (ll i = l; i <= r;) {
            if (i % sq == 0 && i + sq - 1 <= r) {
                ans += blk[i/sq];
                i += sq;
            } else {
                ans += arr[i];
                i++;
            }
        }

        return ans;
    }
};

int main() {
    ll n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for (ll &i : a) cin >> i;

    sqrt_decomposition sd;
    sd.build(a);

    while (q--) {
        ll cmd;
        cin >> cmd;

        if (cmd == 1) {
            ll idx, val;
            cin >> idx >> val;

            sd.update(idx-1, val);
        } else {
            ll l, r;
            cin >> l >> r;

            cout << sd.query(l-1, r-1) << '\n';
        }
    }
    return 0;
}
