#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const double EPS = 1e-9;

struct Poll {
    double x, y;
    Poll(double x = 0, double y = 0) : x(x), y(y) {}
};

double dot(const Poll &a, const Poll &b) {
    return a.x * b.x + a.y * b.y;
}

double cross(const Poll &a, const Poll &b) {
    return a.x * b.y - a.y * b.x;
}

double distSquared(const Poll &a, const Poll &b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
 
double distance(const Poll &a, const Poll &b) {
    return sqrt(distSquared(a, b));
}

ll orientation(const Poll &a, const Poll &b, const Poll &c) {
    double val = cross(Poll(b.x - a.x, b.y - a.y), Poll(c.x - a.x, c.y - a.y));
    if (fabs(val) < EPS)
        return 0;
    return (val > 0) ? 2 : 1;
}

bool pollInPolygon(const vector<Poll>& poly, const Poll &p) {
    ll n = poly.size();
    bool inside = false;
    for (ll i = 0, j = n - 1; i < n; j = i++) {
        if (fabs(cross(Poll(poly[i].x - p.x, poly[i].y - p.y),
                       Poll(poly[j].x - p.x, poly[j].y - p.y))) < EPS &&
            min(poly[i].x, poly[j].x) <= p.x && p.x <= max(poly[i].x, poly[j].x) &&
            min(poly[i].y, poly[j].y) <= p.y && p.y <= max(poly[i].y, poly[j].y))
            return true;
 
        bool cond1 = (poly[i].y > p.y) != (poly[j].y > p.y);
        if (cond1) {
            double x_llersect = poly[i].x + (p.y - poly[i].y) * (poly[j].x - poly[i].x) / (poly[j].y - poly[i].y);
            if (p.x < x_llersect)
                inside = !inside;
        }
    }
    return inside;
}