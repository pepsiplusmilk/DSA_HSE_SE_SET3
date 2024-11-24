
#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

#include <vector>
#include <random>

using ll = long long;

template<typename T>
using vc = std::vector<T>;

class ArrayGenerator {
private:
  std::mt19937 gen;
  std::uniform_int_distribution<ll> ds;

public:

  ArrayGenerator();

  vc<ll> getChaotic(ll of_size);

  vc<ll> getReverseSorted(ll of_size);

  vc<ll> getShuffled( ll of_size);
};

#endif //ARRAYGENERATOR_H
