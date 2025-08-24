struct Median {
    multiset<int> lo, hi;

    void rebalance() {
        if (lo.size() > hi.size()) {
            auto it = prev(lo.end());
            hi.insert(*it);
            lo.erase(it);
        }
        if (hi.size() > lo.size() + 1) {
            auto it = hi.begin();
            lo.insert(*it);
            hi.erase(it);
        }
    }

    void insert(int x) {
        if (hi.empty() || x >= *hi.begin()) {
            hi.insert(x);
        } else {
            lo.insert(x);
        }
        rebalance();
    }

    bool erase(int x) {
        auto it = lo.find(x);
        if (it != lo.end()) {
            lo.erase(it);
            rebalance();
            return true;
        }
        it = hi.find(x);
        if (it != hi.end()) {
            hi.erase(it);
            rebalance();
            return true;
        }
        return false;
    }

    void clear() {
        lo.clear();
        hi.clear();
    }

    int median() const {
        return *hi.begin();
    }
};

