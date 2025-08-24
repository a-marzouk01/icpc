// credit: https://github.com/cgmoreda/CP-Reference
#include <iostream>
#include <vector>
using namespace std;

template<class T>
class segment_tree {
    // Macros for easy access and checks
    #define LEFT (idx << 1)
    #define RIGHT ((idx << 1) | 1)
    #define MID ((start + end) >> 1)
    #define lchild LEFT, start, MID, from, to
    #define rchild RIGHT, MID + 1, end, from, to
    #define in (from <= start && end <= to)
    #define out (to < start || end < from)
    #define para int idx, int start, int end

    int n;
    vector<T> tree;

    // Merge operation for sum query
    T merge(const T &left, const T &right) {
        return left + right;
    }

    // Update the current node using its children
    inline void pushup(int idx) {
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }

    // Build the segment tree from the input array (1-indexed)
    void build(para, const vector<T> &arr) {
        if (start == end) {
            tree[idx] = arr[start];
            return;
        }
        build(LEFT, start, MID, arr);
        build(RIGHT, MID + 1, end, arr);
        pushup(idx);
    }

    // Query the range [from, to]
    T query(para, int from, int to) {
        if (in)
            return tree[idx];
        if (out)
            return 0;  // Identity value for sum queries
        return merge(query(lchild), query(rchild));
    }

    // Update the range [from, to] by adding val to each element in that range
    void update(para, int from, int to, const T &val) {
        if (out)
            return;
        if (start == end) {
            tree[idx] += val;
            return;
        }
        update(lchild, val);
        update(rchild, val);
        pushup(idx);
    }
public:
    // Constructor for building an empty tree with n elements
    segment_tree(int n) : n(n) {
        tree.resize(n << 2);
    }

    // Constructor that builds the tree from an initial vector
    // Assumes the vector is 1-indexed (i.e. arr[1] to arr[n] are used)
    segment_tree(const vector<T> &v) {
        n = v.size() - 1;
        tree.resize(n << 2);
        build(1, 1, n, v);
    }

    // Public query interface
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }

    // Public update interface
    void update(int l, int r, const T &val) {
        update(1, 1, n, l, r, val);
    }
};

int main() {
    // Example usage of the segment_tree for sum queries.
    // Array size is 5, using 1-indexed array (index 0 is unused).
    int n = 5;
    vector<int> arr = {0, 1, 2, 3, 4, 5}; // arr[1]=1, arr[2]=2, ..., arr[5]=5

    // Build the segment tree from the initial array
    segment_tree<int> st(arr);

    // Query the sum over the range [2, 4]: expected sum = 2 + 3 + 4 = 9
    cout << "Initial sum of range [2, 4]: " << st.query(2, 4) << "\n";

    // Update the value at index 3 by adding 10 (range update on [3, 3])
    st.update(3, 3, 10);

    // Now the element at index 3 becomes 13.
    // Query the sum over the range [2, 4] again: expected sum = 2 + 13 + 4 = 19
    cout << "After update, sum of range [2, 4]: " << st.query(2, 4) << "\n";

    return 0;
}
