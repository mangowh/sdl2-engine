#pragma once

#include <cctype>
#include <iostream>
#include <random>

// TODO turn into namespace
class Random {
public:
  int genRandomInt(int min = 0, int max = 100) {
    std::random_device rseed;
    std::mt19937 rng(rseed());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
  }
};
