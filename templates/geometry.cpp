#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const double EPS = 1e-9;

// pick's theorm
// area = points_inside + points_boundry/2 - 1 

struct P {
    ll x, y;
    
    P operator -(const P& he) const {
        return P{x - he.x, y - he.y};
    }
    void operator-=(const P& he) {
        x -= he.x;
        y -= he.y;
    }
    
    P operator +(const P& he) const {
        return P{x + he.x, y + he.y};
    }
    void operator+=(const P& he) {
        x += he.x;
        y += he.y;
    }
 
    // cross product
    // if *he* on the right -ve, otherwise +ve
    ll operator*(const P& he) const {
        return (x * he.y) - (y * he.x);
    }
    ll tri(const P& he, const P& she) const {
        return (he - *this) * (she - *this);
    }
 
    // for convex hull
    // bool operator<(const P& he) const {
    //     return make_pair(x, y) < make_pair(he.x, he.y);
    // }
};

bool collinear(const P& he, const P& she) {
    return he * she == 0;
}

ll dot(const P &a, const P &b) {
    return a.x * b.x + a.y * b.y;
}
ll distSquared(const P &a, const P &b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
double distance(const P &a, const P &b) {
    return sqrt(distSquared(a, b));
}

bool pollInPolygon(const vector<P>& poly, const P &p) {
    ll n = poly.size();
    bool inside = false;
    for (ll i = 0, j = n - 1; i < n; j = i++) {
        P p1 = poly[i] - p, p2 = poly[j] - p;
        if (fabs(p1 * p2) < EPS && 
            min(poly[i].x, poly[j].x) <= p.x && p.x <= max(poly[i].x, poly[j].x) &&
            min(poly[i].y, poly[j].y) <= p.y && p.y <= max(poly[i].y, poly[j].y))
            return true;
 
        bool cond1 = (poly[i].y > p.y) != (poly[j].y > p.y);
        if (cond1) {
            ll x_llersect = poly[i].x + (p.y - poly[i].y) * (poly[j].x - poly[i].x) / (poly[j].y - poly[i].y);
            if (p.x < x_llersect)
                inside = !inside;
        }
    }
    return inside;
}

vector<P> convex_hull(vector<P>& pol) {
    // assume points are already sorted
    // if not the sort(pol.begin(), pol.end());

    vector<P> hull;
    for (ll rep = 0; rep < 2; rep++) {
        ll s = hull.size();
        for (P c: pol) {
            while ((ll) hull.size()-s >= 2) {
                P a = hull.end()[-2];
                P b = hull.end()[-1];
                
                if (a.tri(b, c) <= 0) {
                    break;
                }
                hull.pop_back();
            }
            hull.push_back(c);
        }
        hull.pop_back();
        reverse(pol.begin(), pol.end());
    }

    return hull;
}


