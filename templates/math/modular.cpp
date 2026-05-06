#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <int MOD_> struct modnum {
    static constexpr int MOD = MOD_;
private:
    using ll = long long;
    int v;

    static int minv(int a, int m) {
        a %= m;
        assert(a);
        return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
    }

public:
    modnum() : v(0) {}
    modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
    explicit operator int() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }

    friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
    friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

    modnum inv() const {
        modnum res;
        res.v = minv(v, MOD);
        return res;
    }
    friend modnum inv(const modnum& m) { return m.inv(); }
    modnum neg() const {
        modnum res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend modnum neg(const modnum& m) { return m.neg(); }

    modnum operator- () const { return neg(); }
    modnum operator+ () const { return modnum(*this); }

    modnum& operator ++ () {
        v ++;
        if (v == MOD) v = 0;
        return *this;
    }
    modnum& operator -- () {
        if (v == 0) v = MOD;
        v --;
        return *this;
    }
    modnum& operator += (const modnum& o) {
        v += o.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    modnum& operator -= (const modnum& o) {
        v -= o.v;
        if (v < 0) v += MOD;
        return *this;
    }
    modnum& operator *= (const modnum& o) { v = int(ll(v) * ll(o.v) % MOD); return *this; }
    modnum& operator /= (const modnum& o) { return *this *= o.inv(); }

    friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
    friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
    friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};
using mint = modnum<998244353>; // set the mod here
// using mint = modnum<(int)1e9 + 7>;

mint power(mint b, ll e) {
    mint ret = 1;
    while (e) {
        if (e & 1) ret *= b;
        b *= b;
        e >>= 1;
    }
    return ret;
}

const int MAX = 1e6;
vector<mint> fact(MAX+1), ifact(MAX+1);;
void precomp() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= MAX; i++) fact[i] = fact[i-1] * i;

    ifact[MAX] = inv(fact[MAX]);
    for (int i = MAX-1; i >= 0; i--) ifact[i] = ifact[i+1] * (i+1);
}

mint C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * ifact[r] * ifact[n-r];
}

mint P(int n, int r) {
    if (r < 0 || n < r) return 0;
    return fact[n] * ifact[n-r];
}
