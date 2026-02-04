#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

vector<ll> KMP(string& s) {
    ll n = s.size();
    vector<ll> pi(n);
    for (ll i = 1; i < n; i++) {
        ll j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<vector<ll>> automaton(string s) {
    s += '#';
    ll n = s.size();
    vector<ll> k = KMP(s);
    vector<vector<ll>> aut(n, vector<ll>(26));
    for (ll i = 0; i < n; i++) {
        for (ll c = 0; c < 26; c++) {
            if (i > 0 && c+'a' != s[i]) aut[i][c] = aut[k[i-1]][c];
            else aut[i][c] = i + ('a' + c == s[i]);
        }
    }
    return aut;
}

