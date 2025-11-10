#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }

string to_string(vector<bool> v) {
  string res = "[";
  for (int i = 0; i < (int)v.size(); i++) {
    if (i) res += ", ";
    res += to_string(v[i]);
  }
  res += "]";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]);
  return res;
}

template <typename A>
string to_string(A v) {
  string res = "[";
  bool first = true;
  for (auto &x : v) {
    if (!first) res += ", ";
    first = false;
    res += to_string(x);
  }
  res += "]";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", "
             + to_string(get<1>(p)) + ", "
             + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", "
             + to_string(get<1>(p)) + ", "
             + to_string(get<2>(p)) + ", "
             + to_string(get<3>(p)) + ")";
}

inline void debug_out_names(const char* /*names*/) {
  cerr << endl;
}

template <typename Head, typename... Tail>
void debug_out_names(const char* names, Head H, Tail... T) {
  const char* comma = strchr(names, ',');
  if (!comma) comma = names + strlen(names);
  string name(names, comma - names);
  
  while (!name.empty() && isspace(name.front())) name.erase(name.begin());
  while (!name.empty() && isspace(name.back())) name.pop_back();

  cerr << name << ": " << to_string(H);

  if (sizeof...(T) > 0) {
    cerr << " ";
    if (*comma == ',') ++comma;
    while (*comma == ' ') ++comma;
    debug_out_names(comma, T...);
  } else {
    cerr << endl;
  }
}

#ifdef LOCAL
#define debug(...) do { cerr << "  "; debug_out_names(#__VA_ARGS__, __VA_ARGS__); } while(0)
#else
#define debug(...) 42
#endif

