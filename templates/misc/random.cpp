#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

ll rng() {
    static mt19937 gen(
            chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<long long>(0, INT64_MAX)(gen);
}

ll rng(ll mn, ll mx) {
    static mt19937 gen(
            chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<long long>(mn, mx)(gen);
}

