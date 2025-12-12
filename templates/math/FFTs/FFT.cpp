#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

#define PI acos(-1)
#define C complex<double>

void FFT(vector<C>& f, bool flag) {
    ll n = (ll) f.size();

    for (ll i = 0, j = 0; i < n; i++) {
        if (i < j) swap(f[i], f[j]);
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
    }


    for (ll len = 1; len <= n; len <<= 1) { // current level
        for (ll p = 0; p < n; p += len) { // current polynomial
            double angle = 2*PI / (double) len;

            C w0(1);
            C w1(cos(angle), sin(angle) * (flag ? -1 : +1));
            for (ll i = 0; i < len/2; i++) { // current element in the polynomial
                C tmp = f[p + i];
                f[p + i] = f[p + i] + w0 * f[len/2 + p + i];
                f[len/2 + p + i] = tmp - w0 * f[len/2 + p + i];

                w0 *= w1;
                if (flag) {
                    f[p + i] /= 2;
                    f[len/2 + p + i] /= 2;
                }
            }
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

