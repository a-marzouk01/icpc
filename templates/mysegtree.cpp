#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;
typedef long long ll;


// ────────────────────────────────────────────────────────────────────────────────
// 1) MergeOp policies:
// ────────────────────────────────────────────────────────────────────────────────

template<typename T>
struct Min {
    static T merge(T a, T b)       { return std::min(a,b); }
    static T identity()            { return std::numeric_limits<T>::max(); }
};

template<typename T>
struct Max {
    static T merge(T a, T b)       { return std::max(a,b); }
    static T identity()            { return std::numeric_limits<T>::min(); }
};

template<typename T>
struct Sum {
    static T merge(T a, T b)       { return a + b; }
    static T identity()            { return T(0); }
};

template<typename T>
struct Prod {
    static T merge(T a, T b)       { return a * b; }
    static T identity()            { return T(1); }
};

template<typename T>
struct GCD {
    static T merge(T a, T b)       { return __gcd(a,b); }
    static T identity()            { return T(0); }
};

template<typename T>
struct BitAnd {
    static T merge(T a, T b)       { return a & b; }
    static T identity()            { return ~T(0); }
};

template<typename T>
struct BitOr {
    static T merge(T a, T b)       { return a | b; }
    static T identity()            { return T(0); }
};

template<typename T>
struct BitXor {
    static T merge(T a, T b)       { return a ^ b; }
    static T identity()            { return T(0); }
};


// ────────────────────────────────────────────────────────────────────────────────
// 2) UpdateOp policies:
// ────────────────────────────────────────────────────────────────────────────────

template<typename T>
struct NoOp {
    using U = T;
    static void apply(T&, U, int, int)       { /* nothing */ }
    static void compose(U&, U)               { /* nothing */ }
    static U identity()                      { return U(); }
};

template<typename T>
struct Add {
    using U = T;
    // range‐add v over [L..R]:
    static void apply(T& node, U v, int L, int R) {
        node += v * (R - L + 1);
    }
    static void compose(U& oldTag, U v) {
        oldTag += v;
    }
    static U identity() { return U(0); }
};

template<typename T>
struct Assign {
    using U = T;
    // range‐assign v over [L..R]:
    static void apply(T& node, U v, int L, int R) {
        node = v * (R - L + 1);
    }
    static void compose(U& oldTag, U v) {
        oldTag = v;
    }
    static U identity() { return std::numeric_limits<T>::min(); }
};

template<typename T>
struct Affine {
    // U = pair<a,b>: x ↦ a*x + b
    using U = pair<T,T>;
    static void apply(T& node, U v, int L, int R) {
        node = v.first * node + v.second * (R - L + 1);
    }
    static void compose(U& oldTag, U v) {
        // newTag = v ∘ oldTag: first oldTag, then v
        // (a2,b2)∘(a1,b1) = (a2*a1, a2*b1 + b2)
        oldTag = { v.first * oldTag.first,
                   v.first * oldTag.second + v.second };
    }
    static U identity() { return {T(1), T(0)}; }
};

template<typename T>
struct PointMin {
    using U = T;
    // point assign: at L==R do node = min(node, v)
    static void apply(T& node, U v, int L, int R) {
        if (L==R) node = std::min(node, v);
    }
    static void compose(U& oldTag, U v) {
        oldTag = std::min(oldTag, v);
    }
    static U identity() { return std::numeric_limits<T>::max(); }
};


// ────────────────────────────────────────────────────────────────────────────────
// 3) The generic, lazy segment-tree itself:
// ────────────────────────────────────────────────────────────────────────────────

template<
    typename T,
    template<typename> class MergeOp,
    template<typename> class UpdateOp
>
struct segment_tree {
    int n;
    vector<T>    st;
    vector<typename UpdateOp<T>::U> lz;

    // build empty
    segment_tree(int _n):
      n(_n),
      st(4*n+4, MergeOp<T>::identity()),
      lz(4*n+4, UpdateOp<T>::identity())
    {}

    // build from a[1..n]
    segment_tree(const vector<T>& a):
      segment_tree((int)a.size()-1)
    {
        build(1,1,n,a);
    }

    // public API
    void update(int l, int r, typename UpdateOp<T>::U v) {
        update(1,1,n,l,r,v);
    }
    T query(int l, int r) {
        return query(1,1,n,l,r);
    }

  private:
    void apply_node(int p, int L, int R, typename UpdateOp<T>::U v) {
        UpdateOp<T>::apply(st[p], v, L, R);
        UpdateOp<T>::compose(lz[p], v);
    }

    void push(int p, int L, int R) {
        auto tag = lz[p];
        if (tag != UpdateOp<T>::identity()) {
            int M = (L+R)/2;
            apply_node(p<<1,   L,   M, tag);
            apply_node(p<<1|1, M+1, R, tag);
            lz[p] = UpdateOp<T>::identity();
        }
    }

    void build(int p, int L, int R, const vector<T>& a) {
        if (L == R) {
            st[p] = a[L];
        } else {
            int M = (L+R)/2;
            build(p<<1,   L,   M, a);
            build(p<<1|1, M+1, R, a);
            st[p] = MergeOp<T>::merge(st[p<<1], st[p<<1|1]);
        }
    }

    void update(int p, int L, int R, int i, int j, typename UpdateOp<T>::U v) {
        if (j < L || R < i) return;
        if (i <= L && R <= j) {
            apply_node(p, L, R, v);
            return;
        }
        push(p,L,R);
        int M = (L+R)/2;
        update(p<<1,   L,   M, i,j,v);
        update(p<<1|1, M+1, R, i,j,v);
        st[p] = MergeOp<T>::merge(st[p<<1], st[p<<1|1]);
    }

    T query(int p, int L, int R, int i, int j) {
        if (j < L || R < i) return MergeOp<T>::identity();
        if (i <= L && R <= j) return st[p];
        push(p,L,R);
        int M = (L+R)/2;
        return MergeOp<T>::merge(
            query(p<<1,   L,   M, i,j),
            query(p<<1|1, M+1, R, i,j)
        );
    }
};

int main() {
    // -------------------------
    // Example 1: Range add + Range sum
    // -------------------------
    {
        vector<ll> a = {0, 1, 2, 3, 4, 5}; // 1-indexed: a[1]=1 ... a[5]=5
        segment_tree<ll, Sum, Add> seg(a);

        // initial sum(1..5) = 1+2+3+4+5 = 15
        cout << "initial sum(1..5) = " << seg.query(1,5) << "\n";

        // add +10 to range [2..4]
        seg.update(2, 4, 10LL);

        // new array: [1, 12, 13, 14, 5]
        // query sum(1..3) -> 1 + 12 + 13 = 26
        cout << "after add 10 to [2,4], sum(1..3) = " << seg.query(1,3) << "  (expected 26)\n\n";
    }

    // -------------------------
    // Example 2: Range assign + Range sum
    // -------------------------
    {
        cout << "Example 2 — Range assign + Range sum\n";
        vector<ll> a = {0, 1, 2, 3, 4, 5};
        segment_tree<ll, Sum, Assign> seg(a);

        // assign value 7 to range [1..3]
        seg.update(1, 3, 7LL);

        // new array: [7,7,7,4,5]
        // sum(1..5) = 7+7+7+4+5 = 30
        cout << "after assign 7 to [1,3], sum(1..5) = " << seg.query(1,5) << "  (expected 30)\n\n";
    }

    // -------------------------
    // Example 3: Range affine (x -> a*x + b) + Range sum
    // -------------------------
    {
        cout << "Example 3 — Range affine (scale+shift) + Range sum\n";
        vector<ll> a = {0, 2, 3, 4, 5}; // indices 1..4
        segment_tree<ll, Sum, Affine> seg(a);

        // apply f(x) = 2*x + 1 to range [2..4]
        seg.update(2, 4, make_pair<ll,ll>(2, 1)); // (a=2, b=1)

        // new array: [2, 5, 7, 9]  (index 1..4)
        // sum(2..4) = 5 + 7 + 9 = 21
        cout << "after applying x->2*x+1 on [2,4], sum(2..4) = " << seg.query(2,4)
             << "  (expected 21)\n\n";
    }

    // -------------------------
    // Example 4: Range minimum (MergeOp=Min) + PointMin update
    // (PointMin::apply only changes when L==R — useful for operations on single elements)
    // -------------------------
    {
        cout << "Example 4 — Range minimum + point-min updates\n";
        vector<ll> a = {0, 5, 3, 8, 2}; // indices 1..4
        segment_tree<ll, Min, PointMin> seg(a);

        // point: set a[2] = min(a[2], 1)
        seg.update(2, 2, 1LL); // now a[2] becomes min(3,1) = 1

        // point: set a[4] = min(a[4], 6)
        seg.update(4, 4, 6LL); // now a[4] becomes min(8,6) = 6

        // query minimum over full range [1..4] -> min(5,1,8->3?,6,2) careful: a[3] unchanged =3
        // final array should be [5,1,3,6,2] (if index range is up to 4)
        cout << "min(1..4) after two point-mins = " << seg.query(1,4) << "  (expected 1)\n\n";
    }

    return 0;
}

