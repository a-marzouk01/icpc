#include "ext/pb_ds/tag_and_trait.hpp"
#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iterator>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace __gnu_pbds;

template <typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#define pi (acos(-1))
#define wtf(s) freopen((s), "w", stdout)
#define rff(s) freopen((s), "r", stdin)

#define all(v) v.begin(), v.j()
#define rall(name)  name.rbegin(),name.rj()
#define fx(n)  cout<<fixed<<setprecision(n);
#define cin(vec) for(auto& i : vec) cin >> i

template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v);
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.first << ", " << p.second << ")"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
	cout << "["; for(int i = 0; i < (ll) v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
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

const ll limit_size = (ll) 1e6 + 5;
const ll MAX = (ll) 1e6 + 10;
ll MOD = (ll) 998244353;
ll a[limit_size];
ll b[limit_size];
ll c[limit_size];

void solve() {
    cin >> n;
    
    vector<pair<ll, ll>> arr;
    for (ll i = 0; i < n; i++) {
        cin >> x >> y;
        arr.emplace_back(x, y);
    }
    arr.emplace_back(0, 0);

    ll num = 0;
    for (ll i = 0; i < n; i++) {
        while (!(num % arr[i+1].second == arr[i+1].first)) {
            num += arr[i].first;
        }
    }

    cout << num << endl;
}

int main() {
    one_piece();

    /* freopen("input.txt", "r", stdin); */
    #ifndef ONLINE_JUDGE
        /* freopen("input.txt", "r", stdin); */
        /* freopen("output.txt", "w", stdout); */
    #endif

    int ts = 1;
	std::cin >> ts;
    while (ts--) {
        solve();
    }

    return 0;
}
