#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

struct ha4{
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const noexcept {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return (size_t) splitmix64(x + FIXED_RANDOM);
    }

    template<class T, class U>
    size_t operator()(const pair<T, U>& p) const noexcept {
        uint64_t h1 = operator()(uint64_t(p.first));
        uint64_t h2 = operator()(uint64_t(p.second) + 0x9e3779b97f4a7c15ULL);
        return (size_t)(h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1<<6) + (h1>>2)));
    }
};


// gp_hash_table<ll, ll, ha4> mp;
// gp_hash_table<pair<ll,ll>, ll, ha4> mpp;
