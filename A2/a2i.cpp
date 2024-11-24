#include <iostream>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <complex>
#include <iomanip>
#include <random>
#include <fstream>
#include <set>
#include <bitset>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using ll = long long;
using ull = unsigned long long;
using ld = long double;

const ld eps = 1e-12;
const ll inf = 1e12;

//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

template<typename T>
using vc = std::vector<T>;

template<typename T>
using mt = vc<vc<T>>;

template<typename T>
using vit = typename std::vector<T>::iterator;

using ustring = std::basic_string<unsigned char>;

// [l; r)
vc<ll> combo_sort(vc<ll>& d, ll k, ll l, ll r) {
  if (r - l <= k) {
    ll m = std::min(k, r - l);
    vc<ll> b(m, 0);

    for (ll i = l; i < r; ++i) {
      b[i - l] = d[i];
    }

    for (ll i = 0; i < m; ++i) {
      ll j = i - 1;

      while (j >= 0 && b[j] > b[j + 1]) {
        std::swap(b[j], b[j + 1]);
        --j;
      }
    }

    return b;
  }

  ll m = (l + r) >> 1;
  auto dl = combo_sort(d, k, l, m);
  auto dr = combo_sort(d, k, m, r);

  ll i = 0, j = 0;
  vc<ll> res;

  while (i < dl.size() && j < dr.size()) {
    if (dl[i] <= dr[j]) {
      res.push_back(dl[i++]);
    } else {
      res.push_back(dr[j++]);
    }
  }

  while (i < dl.size()) {
    res.push_back(dl[i++]);
  }

  while (j < dr.size()) {
    res.push_back(dr[j++]);
  }

  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ll n;

  std::cin >> n;

  vc<ll> d(n, 0);

  for (ll i = 0; i < n; ++i) {
    std::cin >> d[i];
  }

  d = combo_sort(d, 15, 0, n);

  for (const auto& i : d) {
    std::cout << i << " ";
  }

  return 0;
}