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

struct circ {
  ld cx, cy;
  ld rs;

  circ(ld _cx, ld _cy, ld _rs) : cx(_cx), cy(_cy), rs(_rs) {}

  bool in(ld x0, ld y0) {
    return rs - (cx - x0) * (cx - x0) - (cy - y0) * (cy - y0) >= eps;
  }
};

ld monte_carlo(std::mt19937& gen, circ& c1, circ& c2, circ& c3, ld px0, ld py0, ld a, ld b, ll n) {
  std::uniform_real_distribution<ld> dsx(px0, px0 + a);
  std::uniform_real_distribution<ld> dsy(py0, py0 + b);

  ll inside = 0;

  for (ll i = 0; i < n; ++i) {
    ld xi = dsx(gen);
    ld yi = dsy(gen);

    if (c1.in(xi, yi) && c2.in(xi, yi) && c3.in(xi, yi)) {
      ++inside;
    }
  }

  return (a * b * inside * 1.0) / n * 1.0;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  circ c1(1, 1, 1);
  circ c2(1.5, 2, 1.25);
  circ c3(2, 1.5, 1.25);

  std::mt19937 gen(102345);

  //std::cout << monte_carlo(gen, c1, c2, c3, 0.88, 0.88, 1.119, 1.112, 1e7);

  ld sx = 0, sy = 0;
  ld ex = 0.88, ey = 0.88;

  ld ss = 3.118;
  ld sa = 1.119, sb = 1.112;

  std::ofstream ofs("result.txt");
  std::ofstream ofs2("accur.txt");
  ofs << std::setprecision(7);
  ll steps = 6;

  ld pi = std::atan2(0, -2);
  ld ideal = pi / 4.0 + 1.25 * std::asin(0.8) - 1;

  std::cout << pi << " " << ideal;

  ld point_step = ex / steps;
  ld sa_step = (sa - ss) / steps;
  ld sb_step = (sb - ss) / steps;

  for (ll i = 0; i <= steps; ++i) {
    ld x0 = point_step * i, y0 = point_step * i;
    ld ai = ss + sa_step * i;
    ld bi = ss + sb_step * i;

    for (ll j = 100; j <= 1e5 + 100; j += 500) {
      ld res = monte_carlo(gen, c1, c2, c3, x0, y0, ai, bi, j);
      ofs << "(" << ai * bi << ", " << j << ", " << res << ") ";
      ofs2 << "(" << ai * bi << ", " << j << ", " << (res - ideal) / ideal << ") ";
    }

    ofs << "\n\n";
    ofs2 << "\n\n";
  }

  ofs.close();
  ofs2.close();

  return 0;
}