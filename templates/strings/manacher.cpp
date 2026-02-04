#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

vector<ll> manacher(string &s) {
    string t;
    for (char c : s) t += string("#") + c;
    t += "#";

    ll n = (ll)t.size();
    t = "$" + t + "^";

    vector<ll> p(n+2);
    ll l = 0, r = 1;
    for (ll i = 1; i <= n; i++) {
        if (i < r) p[i] = min(r-i, p[l + (r-i)]);
        while (t[i-p[i]-1] == t[i+p[i]+1]) p[i]++;
        if (i+p[i] > r) l = i-p[i], r = i+p[i];
    }

    return vector<ll>(p.begin()+2, p.end()-2);
}

