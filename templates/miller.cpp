#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
using u128 = __uint128_t;

// deterministic miller rabin with O(log(n)) to O(log(n)^3) 

u64 mul_mod(u64 a, u64 b, u64 mod) {
    return (u64)((u128)a * b % mod);
}

u64 pow_mod(u64 a, u64 e, u64 mod) {
    u64 res = 1 % mod;
    while (e) {
        if (e & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return res;
}

bool isPrime64(u64 n) {
    if (n < 2) return false;

    for (u64 p : {2ull,3ull,5ull,7ull,11ull,13ull,17ull,19ull,23ull,29ull}) {
        if (n % p == 0) return n == p;
    }

    // write n-1 = d * 2^s
    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) { d >>= 1; ++s; }

    // deterministic bases for 64-bit integers
    u64 bases[] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
    for (u64 a : bases) {
        if (a % n == 0) continue;
        u64 x = pow_mod(a % n, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long x;
    cin >> x;

    if (isPrime64(x)) {
        cout << "PRIME" << endl;
    } else cout << "NOT PRIME" << endl;
    return 0;
}

