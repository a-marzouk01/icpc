#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Define the segment tree class template
template <typename T>
class segment_tree {
    // 1-indexed segment tree: using macros for left/right/mid indices
    #define LEFT (idx << 1)
    #define RIGHT (idx << 1 | 1)
    #define MID ((start + end) >> 1)

    int n;
    vector<T> tree;
    vector<T> lazy;

    // Function to merge two segments. 
    // For a sum segment tree, merge returns the sum.
    T merge(const T &left, const T &right) {
        return __gcd(left, right);  // change as needed for different operations
    }

    // Propagate lazy values down from current node.
    inline void pushdown(int idx, int start, int end) {
        if (lazy[idx] == 0)
            return;
        // Update the current node. For sum, we add lazy[idx] multiplied by the segment length.
        tree[idx] += lazy[idx] * (end - start + 1);
        if (start != end) {
            // Propagate the lazy value to children.
            lazy[LEFT]  += lazy[idx];
            lazy[RIGHT] += lazy[idx];
        }
        // Clear the lazy value for this node.
        lazy[idx] = 0;
    }

    // After updating children, update the current node.
    inline void pushup(int idx) {
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }

    // Build the segment tree without an initial array.
    void build(int idx, int start, int end) {
        if (start == end)
            return;
        build(LEFT, start, MID);
        build(RIGHT, MID + 1, end);
        pushup(idx);
    }

    // Build the tree using an input array. Assumes arr is 1-indexed.
    void build(int idx, int start, int end, const vector<T> &arr) {
        if (start == end) {
            tree[idx] = arr[start];
            return;
        }
        build(LEFT, start, MID, arr);
        build(RIGHT, MID + 1, end, arr);
        pushup(idx);
    }

    // Query the segment tree in the range [from, to].
    T query(int idx, int start, int end, int from, int to) {
        pushdown(idx, start, end);
        if (from <= start && end <= to)
            return tree[idx];
        if (to <= MID)
            return query(LEFT, start, MID, from, to);
        if (MID < from)
            return query(RIGHT, MID + 1, end, from, to);
        return merge(query(LEFT, start, MID, from, to),
                     query(RIGHT, MID + 1, end, from, to));
    }

    // Update the range [lq, rq] by adding val.
    void update(int idx, int start, int end, int lq, int rq, const T &val) {
        pushdown(idx, start, end);
        if (rq < start || end < lq)
            return;
        if (lq <= start && end <= rq) {
            lazy[idx] += val; // update lazy value
            pushdown(idx, start, end);
            return;
        }
        update(LEFT, start, MID, lq, rq, val);
        update(RIGHT, MID + 1, end, lq, rq, val);
        pushup(idx);
    }

public:
    // Constructor using the size of the array
    segment_tree(int n) : n(n), tree(n << 2), lazy(n << 2) { }

    // Constructor that builds the tree using an input array (1-indexed)
    segment_tree(const vector<T> &v) {
        n = v.size() - 1;  // v[0] is unused
        tree = vector<T>(n << 2);
        lazy = vector<T>(n << 2);
        build(1, 1, n, v);
    }

    // Public query function
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }

    // Public update function: add val to each element in range [l, r]
    void update(int l, int r, const T &val) {
        update(1, 1, n, l, r, val);
    }
    #undef LEFT
    #undef RIGHT
    #undef MID
};

int main() {
    // Create a 1-indexed array for the segment tree.
    // For instance, if we want to represent the array: [1, 2, 3, 4, 5]
    // we define it as:
    vector<ll> arr = {0, 1, 2, 3, 4, 5};  // arr[0] is unused

    // Instantiate the segment tree with the array.
    segment_tree<ll> seg(arr);

    // Example query: Sum of elements from index 2 to 4.
    cout << "Initial sum of indices 2 to 4: " << seg.query(2, 4) << "\n";  // Should output 2+3+4 = 9

    // Example update: Add 10 to elements from index 3 to 5.
    seg.update(3, 5, 10);

    // Query again after the update.
    cout << "Sum of indices 2 to 4 after update: " << seg.query(2, 4) << "\n";  // Should output 2 + (3+10) + (4+10) = 29

    return 0;
}
