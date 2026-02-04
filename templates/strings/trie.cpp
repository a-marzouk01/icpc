#include <bits/stdc++.h>

typedef long long ll; 
using namespace std;

struct Trie {
    struct Node {
        vector<ll> nxt;
        ll fin = 0;
        Node() { nxt=vector<ll>(31, -1); }
    };

    vector<Node> trie;
    Trie() { trie.push_back(Node()); }

    void insert(string &s) {
        ll curr = 0;
        for (char c : s) {
            ll &me = trie[curr].nxt[c-'a'];
            if (me == -1) {
                me = trie.size();
                trie.push_back(Node());
            }
            curr = me;
        }
        trie[curr].fin = 1;
    }

    ll exist(string& s) {
        ll curr = 0;
        for (char c : s) {
            ll &me = trie[curr].nxt[c-'a'];
            if (me == -1) return false;
            curr = me;
        }
        return trie[curr].fin;
    }
};

