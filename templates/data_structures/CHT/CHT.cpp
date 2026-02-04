#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Line {
    ll m, b;
    Line(){}
    Line(ll _m, ll _b) : m(_m), b(_b) {}
};

struct CHT {
    deque<Line> dq;

    ll useless(Line l1, Line l2, Line l3) {
        return 1.0L * (l3.b - l1.b) * (l1.m - l2.m)  
            <= 1.0L * (l2.b - l1.b) * (l1.m - l3.m); //(slope dec+query min),(slope inc+query max)
        // return 1.0L * (l3.b - l1.b) * (l1.m - l2.m)  >
        //     1.0L * (l2.b - l1.b) * (l1.m - l3.m); //(slope dec+query max), (slope inc+query min)
    }

    void add(ll m, ll b) {
        Line me = Line(m, b);
        while (dq.size() >= 2 && useless(dq[(ll)dq.size()-2], dq.back(), me)) {
            dq.pop_back();
        }
        dq.push_back(me);
    }

    ll f(Line l, ll x) {
        return l.m * x + l.b;
    }

    ll query(ll x) {
        while (dq.size() >= 2 && f(dq[0], x) <= f(dq[1],x)) { 
            dq.pop_front();
        }
        return f(dq[0], x);
    }
};
