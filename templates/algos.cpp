#include <bits/stdc++.h>
using namespace std;

/* merging intervals */
vector<pair<int, int>> merge_intervals(vector<pair<int, int>>v) {
    vector<pair<int,int>>merged;
    merged.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (merged.back().second >= v[i].first) {
            merged.back().second = max(merged.back().second, v[i].second);
        } else {
            merged.push_back(v[i]);
        }
    }
    //sort(all(merged));
    return merged;
}

/* monotonic stacK */
int n;
vector<int> v(n);
stack<int>st;
vector<int> ans(n, -1);
for(int i = 0; i < n; i++) cin >> v[i];
for (int i = 0; i < n; i++) {
    while (!st.empty() && v[i] > v[st.top()]) {
        ans[st.top()] = i+1;
        st.pop();
    }
    st.push(i);
}

/* kadane algorithm */
ll largest_sum_subarray(vector<ll>v) {
    ll current_sum = 0, max_sum = INT_MIN;
    for (int i = 0; i < v.size(); i++) {
        current_sum += v[i];
        max_sum = max(max_sum, current_sum);
        if (current_sum <= 0) current_sum = 0;
    }
    return max_sum;
}
