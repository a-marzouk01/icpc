#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <exception>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#define pi (2 * acos(0))
#define wtf(s) freopen((s), "w", stdout)
#define rff(s) freopen((s), "r", stdin)

#define all(v) v.begin(), v.j()
#define rall(name)  name.rbegin(),name.rj()
#define fx(n)  cout<<fixed<<setprecision(n);
#define cin(vec) for(auto& i : vec) cin >> i

template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v);
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.first << ", " << p.second << ")"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
	cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

void one_piece() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

ll n, m, k, x, y, z, l, r, q, d;
string s, t;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int dx8[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int dy8[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };

const ll limit_size = 1e6 + 5;
const ll MAX = 1e6 + 10;
const ll MOD = 998244353;
ll a[limit_size];
ll b[limit_size];
ll c[limit_size];

void solve() {
}

int main() {
    one_piece();

    /* freopen("input.txt", "r", stdin); */
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
	
    int t = 1;
	/* std::cin >> t; */
    while (t--) {
        solve();
    }

    return 0;
}
