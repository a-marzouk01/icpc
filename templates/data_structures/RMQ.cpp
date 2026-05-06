#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct RMQ {
    ll n;
    vector<ll> LG;
    vector<vector<ll>> rmq;
 
    RMQ(vector<ll>& a) {
        n = (ll)a.size();
        LG = vector<ll>(n+1, 0);
 
        LG[1] = 0;
        for (ll i = 2; i <= n; i++) LG[i] = LG[i/2] + 1;
 
        rmq = vector<vector<ll>>(n, vector<ll>(LG[n]+1));
        for (ll i = 0; i < n; i++) rmq[i][0] = a[i];
        for (ll k = 1; k <= LG[n]; k++) {
            for (ll i = 0; i < n; i++) {
                if (i + (1 << (k-1)) >= n) break;
                rmq[i][k] = min(rmq[i][k-1], rmq[i + (1<<(k-1))][k-1]);
            }
        }
    }
 
    ll query(ll l, ll r) {
        ll sz = r - l + 1;
        ll LOG = LG[sz];
        return min(rmq[l][LOG], rmq[r - (1<<LOG)+1][LOG]);
    }
};
