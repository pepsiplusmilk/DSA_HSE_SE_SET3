#include "SortTester.h"
#include <fstream>
#include <iomanip>

void SortTester::update_samples() {
  group1 = gen.getChaotic(k);
  group3 = gen.getShuffled(k);
  group2 = gen.getReverseSorted(k);
}

void SortTester::test(ll k, ll min_size, ll max_size, ll step, vc<ld>& avg1, vc<ld>& avg2, vc<ld>& avg3) {
  for (ll i = min_size, j = 0; i <= max_size; i += step, ++j) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter(group1, k, 0, i);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    avg1[j] += msec;
  }

  for (ll i = min_size, j = 0; i <= max_size; i += step, ++j) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter(group2, k, 0, i);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    avg2[j] += msec;
  }

  for (ll i = min_size, j = 0; i <= max_size; i += step, ++j) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter(group3, k, 0, i);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    avg3[j] += msec;
  }
}
