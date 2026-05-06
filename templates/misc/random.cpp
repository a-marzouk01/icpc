#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

mt19937 mt(time(NULL));
int rng(int mn, int mx) {
    return mn + (mt() % (mx - mn + 1));
}

