#ifndef SORTTESTER_H
#define SORTTESTER_H

#include <chrono>
#include "ArrayGenerator.h"
#include <functional>

using ld = long double;

class SortTester {
private:
  std::function<vc<ll>(vc<ll>& d, ll k, ll l, ll r)> sorter;
  ArrayGenerator gen;
  const ll k = 10000;
  vc<ll> group1;
  vc<ll> group2;
  vc<ll> group3;

public:

  explicit SortTester(std::function<vc<ll>(vc<ll>&, ll, ll, ll)> sort_algo)
  : sorter(sort_algo), gen(), group1(k, 0), group2(k, 0), group3(k, 0) {
    update_samples();
  }

  void update_samples();

 void test(ll k, ll min_size, ll max_size, ll step, vc<ld>& avg1, vc<ld>& avg2, vc<ld>& avg);
};

#endif //SORTTESTER_H
