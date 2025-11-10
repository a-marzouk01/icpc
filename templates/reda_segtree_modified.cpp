// credit: https://github.com/cgmoreda/CP-Reference
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<typename T>
class segment_tree {
#define LEFT  (idx<<1)
#define RIGHT (idx<<1|1)
#define MID   ((start+end)>>1)

	int n;
	vector<T> tree, lazy;

	T merge(const T &L, const T &R) {
    	// <-- adapt here -->
    	return L + R;  // default: range-sum
    	// return min(L, R);  // range-min
    	// return max(L, R);  // range-max
    	// return __gcd(L, R);  // range-gcd
	}

	inline void pushdown(int idx, int start, int end) {
    	if (!lazy[idx]) return;

    	/*** Range-Add ***/
    	// tree[idx] += lazy[idx] * (end - start + 1);
    	// if (start != end) {
    	// 	lazy[LEFT]  += lazy[idx];
    	// 	lazy[RIGHT] += lazy[idx];
    	// }

    	/*** Range-Assign ***/
    	// tree[idx] = lazy[idx] * (end - start + 1);
    	// if (start != end) {
    	// 	lazy[LEFT]  = lazy[idx];
    	// 	lazy[RIGHT] = lazy[idx];
    	// }

    	/*** Range-Min-Assign (chmin) ***/
    	// tree[idx] = min(tree[idx], lazy[idx]);
    	// if (start != end) {
    	// 	lazy[LEFT]  = (lazy[LEFT] ? min(lazy[LEFT], lazy[idx]) : lazy[idx]);
    	// 	lazy[RIGHT] = (lazy[RIGHT] ? min(lazy[RIGHT], lazy[idx]) : lazy[idx]);
    	// }

    	/*** Range-Max-Assign (chmax) ***/
    	// tree[idx] = max(tree[idx], lazy[idx]);
    	// if (start != end) {
    	// 	lazy[LEFT]  = (lazy[LEFT] ? max(lazy[LEFT], lazy[idx]) : lazy[idx]);
    	// 	lazy[RIGHT] = (lazy[RIGHT] ? max(lazy[RIGHT], lazy[idx]) : lazy[idx]);
    	// }

    	// After applying, clear tag for range-add/assign
    	lazy[idx] = 0;
	}

	inline void pushup(int idx) {
    	tree[idx] = merge(tree[LEFT], tree[RIGHT]);
	}

	void build(int idx, int start, int end, const vector<T> &v) {
    	if (start == end) {
        	tree[idx] = v[start];
        	return;
    	}
    	build(LEFT, start, MID, v);
    	build(RIGHT, MID+1, end, v);
    	pushup(idx);
	}

	void update(int idx, int start, int end, int lq, int rq, const T &val) {
    	pushdown(idx, start, end);
    	if (rq < start || end < lq) return;
    	if (lq <= start && end <= rq) {
        	// For range-add: lazy[idx] += val;
        	// For range-assign: lazy[idx] = val;
        	lazy[idx] += val;
        	pushdown(idx, start, end);
        	return;
    	}
    	update(LEFT, start, MID, lq, rq, val);
    	update(RIGHT, MID+1, end, lq, rq, val);
    	pushup(idx);
	}

	T query(int idx, int start, int end, int lq, int rq) {
    	pushdown(idx, start, end);
    	if (rq < start || end < lq) return 0;  // change identity if using min/max
    	if (lq <= start && end <= rq)
        	return tree[idx];
    	T s1 = query(LEFT, start, MID, lq, rq);
    	T s2 = query(RIGHT, MID+1, end, lq, rq);
    	return merge(s1, s2);
	}

public:
	segment_tree(int _n) : n(_n), tree(4*_n,0), lazy(4*_n,0) {}
	segment_tree(const vector<T> &v) {
    	n = (int)v.size()-1;
    	tree.assign(4*n,0);
    	lazy.assign(4*n,0);
    	build(1,1,n,v);
	}

	void update(int l, int r, const T &val) { update(1,1,n,l,r,val); }
	T query(int l, int r) { return query(1,1,n,l,r); }

#undef LEFT
#undef RIGHT
#undef MID
};



int main() {
    vector<ll> arr = {0, 1, 2, 3, 4, 5}; // must be 1-indexed

    segment_tree<ll> seg(arr);

    cout << "Initial sum of indices 2 to 4: " << seg.query(2, 4) << "\n";

    seg.update(3, 5, 10);

    cout << "Sum of indices 2 to 4 after update: " << seg.query(2, 4) << "\n";

    return 0;
}
