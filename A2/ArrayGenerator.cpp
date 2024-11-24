#include "ArrayGenerator.h"
#include <algorithm>

ArrayGenerator::ArrayGenerator() {
   gen = std::mt19937(42); // used constant to show that results are repeatable
   ds = std::uniform_int_distribution<ll>(0, 6000);
}


vc<ll> ArrayGenerator::getChaotic(const ll of_size) {
  vc<ll> new_vec(of_size, 0);

  for (auto& i : new_vec) {
    i = ds(gen);
  }

  return new_vec;
}

vc<ll> ArrayGenerator::getReverseSorted(const ll of_size) {
  vc<ll> new_vec = getChaotic(of_size);
  std::sort(new_vec.rbegin(), new_vec.rend());
  return new_vec;
}

vc<ll> ArrayGenerator::getShuffled(const ll of_size) {
  vc<ll> new_vec = getChaotic(of_size);
  std::sort(new_vec.begin(), new_vec.end());

  ll onep = of_size / 10;

  std::uniform_int_distribution<ll> coord_ds(0, of_size - 1);

  while (onep--) {
    ll a = coord_ds(gen), b = coord_ds(gen);
    std::swap(a, b);
  }

  return new_vec;
}


