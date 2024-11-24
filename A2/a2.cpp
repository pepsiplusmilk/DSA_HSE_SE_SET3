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
#include "SortTester.h"

using ull = unsigned long long;
using ld = long double;

const ld eps = 1e-12;
const ll inf = 1e12;

//#pragma GCC optimize("O3")
//#pragma GCC target("avx2");

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

  SortTester tester(combo_sort);

  vc<ll> starts = {1, 5, 10, 20, 30, 50};
  ll n = 96;

  std::ofstream ofs;

  for (const auto& change_par : starts) {
    vc<ld> g1avg(n, 0);
    vc<ld> g2avg(n, 0);
    vc<ld> g3avg(n, 0);

    for (ll i = 0; i < 10; ++i) {
      tester.test(change_par, 500, 10000, 100, g1avg, g2avg, g3avg);
      tester.update_samples();
    }

    for (auto& i : g1avg) {
      i /= 10 * 1.0;
    }

    for (auto& i : g2avg) {
      i /= 10 * 1.0;
    }

    for (auto& i : g3avg) {
      i /= 10 * 1.0;
    }

    std::string out_path1 = "chaos_res" + std::to_string(change_par) + ".txt";
    std::string out_path2 = "reverse_res" + std::to_string(change_par) + ".txt";
    std::string out_path3 = "shuffle_res" + std::to_string(change_par) + ".txt";

    ofs.open(out_path1);
    for (ll i = 0; i < n; ++i) {
      ll x = 500 + i * 100;
      ofs << std::setprecision(5) << "(" << x << ", " << g1avg[i] << ") ";
    }
    ofs.close();

    ofs.open(out_path2);
    for (ll i = 0; i < n; ++i) {
      ll x = 500 + i * 100;
      ofs << std::setprecision(5) << "(" << x << ", " << g2avg[i] << ") ";
    }
    ofs.close();

    ofs.open(out_path3);
    for (ll i = 0; i < n; ++i) {
      ll x = 500 + i * 100;
      ofs << std::setprecision(5) << "(" << x << ", " << g3avg[i] << ") ";
    }
    ofs.close();
  }

  return 0;
}