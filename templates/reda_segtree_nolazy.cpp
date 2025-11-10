// credit: https://github.com/cgmoreda/CP-Reference
#include <iostream>
#include <vector>
using namespace std;

template<class T>
class segment_tree {
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

    T merge(const T &left, const T &right) {
        return left + right;
    }

    inline void pushup(int idx) {
        tree[idx] = merge(tree[LEFT], tree[RIGHT]);
    }

    void build(para, const vector<T> &arr) {
        if (start == end) {
            tree[idx] = arr[start];
            return;
        }
        build(LEFT, start, MID, arr);
        build(RIGHT, MID + 1, end, arr);
        pushup(idx);
    }

    T query(para, int from, int to) {
        if (in)
            return tree[idx];
        if (out)
            return 0;  // Identity change for min/max
        return merge(query(lchild), query(rchild));
    }

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
    segment_tree(int n) : n(n) {
        tree.resize(n << 2);
    }

    segment_tree(const vector<T> &v) {
        n = v.size() - 1;
        tree.resize(n << 2);
        build(1, 1, n, v);
    }

    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }

    void update(int l, int r, const T &val) {
        update(1, 1, n, l, r, val);
    }
};

int main() {
    int n = 5;
    // must be 1-indexed
    vector<int> arr = {0, 1, 2, 3, 4, 5};

    segment_tree<int> st(arr);

    cout << "Initial sum of range [2, 4]: " << st.query(2, 4) << "\n";

    st.update(3, 3, 10);

    cout << "After update, sum of range [2, 4]: " << st.query(2, 4) << "\n";

    return 0;
}
