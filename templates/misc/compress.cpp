#include <bits/stdc++.h> // Marzouk <3
#pragma GCC optimize("Ofast")
using namespace std;
typedef int64_t ll;

int compress(vector<int>& b, vector<int>& a) {
    int N = (int)a.size();
    b = vector<int>(N);
    vector<pair<int, int>> pairs;
    for (int i = 0; i < N; i++) pairs.emplace_back(a[i], i);
    sort(pairs.begin(), pairs.end());
    int nxt = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0 || pairs[i].first != pairs[i-1].first) nxt++;
        b[pairs[i].second] = nxt-1;
    }
    return nxt;
}
