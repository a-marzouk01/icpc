#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

#define PI acos(-1)
#define C complex<double>

void FFT(vector<C>& f, bool flag) {
    ll n = (ll) f.size();
    if (n == 1) return;

    vector<C> fe, fo;
    for (ll i = 0; i < n; i+=2) {
        fe.push_back(f[i]);
        fo.push_back(f[i+1]);
    }

    FFT(fe, flag), FFT(fo, flag);

    double angle = 2*PI / (double) n;

    C w0(1);
    C w1(cos(angle), sin(angle) * (flag ? -1 : +1));
    for (ll i = 0; i < n/2; i++) {
        f[i] = fe[i] + w0 * fo[i];
        f[n/2 + i] = fe[i] - w0 * fo[i];

        w0 *= w1;
        if (flag) {
            f[i] /= 2;
            f[n/2 + i] /= 2;
        }
    }
}

vector<ll> multiply(vector<ll>& a, vector<ll>& b) {
    vector<C> fa(a.begin(), a.end());
    vector<C> fb(b.begin(), b.end());

    ll n = 1;
    while (n < (ll) a.size() + (ll) b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, 0), FFT(fb, 0);
    for (ll i = 0; i < n; i++) fa[i] *= fb[i];

    FFT(fa, 1);
    vector<ll> ret(n);
    for (ll i = 0; i < n; i++) ret[i] = (ll) round(fa[i].real());
    return ret;
}

