#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

typedef long long ll;

using namespace std;
using namespace __gnu_pbds; 

template <typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename num_t>
struct ordered_multiset {
	ordered_set<pair<num_t, ll> > vals;
	set<pair<num_t, ll> > best;
	
	ll findbest(num_t val) {
		return (*best.upper_bound(make_pair(val - 1, 0))).second;
	}
	
	bool contains(num_t val) {
		return vals.find(make_pair(val, -1)) != vals.end();
	}
	
	void insert(num_t val) {
		if (contains(val)) {
			ll loc = findbest(val);
			best.erase(make_pair(val, loc));
			best.insert(make_pair(val, loc - 1));
			vals.insert(make_pair(val, loc - 1));
		} else {
			best.insert(make_pair(val, -1));
			vals.insert(make_pair(val, -1));
		}
	}
	
	void erase(num_t val) {
		if (!contains(val)) return;
		num_t loc = findbest(val);
		
		best.erase(make_pair(val, loc));
		vals.erase(make_pair(val, loc));
		if (loc != -1) best.insert(make_pair(val, loc + 1));
	}
	
	num_t find_by_order(ll k) { return (*vals.find_by_order(k)).first; }
	ll order_of_key(num_t k) { return vals.order_of_key(make_pair(k - 1, 0)); }
	auto begin() { return vals.begin(); }
	auto end() { return vals.end(); }
	auto rbegin() { return vals.rbegin(); }
	auto rend() { return vals.rend(); }
	ll size() { return vals.size(); }
	void clear() { vals.clear(); best.clear(); }
	ll count(num_t k) { return vals.order_of_key({k, 0}) - vals.order_of_key({k - 1, 0}); }
	auto lower_bound(num_t k) { return vals.lower_bound(make_pair(k - 1, 0)); }
	auto upper_bound(num_t k) { return vals.upper_bound(make_pair(k, 0)); }
};

int main()
{
	/*ordered_set<long long> os;
	os.insert(5);
	os.insert(23);
	os.insert(24);
	os.insert(25);
	os.insert(39);
	for(auto x:os)
	{
		cout<<x<<" ";
	}
	cout<<endl;*/

	ordered_multiset<long long> oms;
	// 5 23 23 24 24 24 25 39 39 100
	oms.insert(5);
	oms.insert(23);
	oms.insert(23);
	oms.insert(24);
	oms.insert(24);
	oms.insert(24);
	oms.insert(25);
	oms.insert(39);
	oms.insert(39);
	oms.insert(100);

	for(auto m:oms) // iterate over ordered multiset
	{
		cout<<m.first<<" ";
	}
	cout<<endl;
	cout<<oms.find_by_order(2)<<endl;
	cout<<oms.order_of_key(26)<<endl;
	cout<<oms.count(24)<<endl;
	cout<<oms.lower_bound(24)->first<<endl; // use in this way
	cout<<oms.upper_bound(23)->first<<endl;

	return 0;
}

/* ------------------------------------------------------------------------ COMMENTS ------------------------------------------------------------------------ */
/* supports things like k-th smallest element and find index of element in set */
/* all in pretty good O(lgn) */

/* example usage */
//ordered_set<ll> os;

/* extra functions (in addition to std::set operations):
	find_by_order(k) - returns a poller to the k-th smallest element in the set (zero-indexed)
	order_of_key(k) - returns the number of elements in the set less than k (if k is in the set, this is the index of it)
*/

/* gfg: https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/ 
	examples:
	set = {1, 5, 6, 17, 88}
	find_by_order(1) - same as set[1] -> poller to 5
	find_by_order(4) - same as set[4] -> poller to 88
	order_of_key(6) -> 2
	order_of_key(88) -> 4
	order_of_key(400) -> 5
	order_of_key(0) -> 0
*/ 
