#pragma once

#include <random>

class RandomNumber
{
public:
  RandomNumber() : rng(rd()), dice(std::uniform_real_distribution<float>(0.0, 1.0)) { rng.seed(std::random_device()()); }

  float roll() const { return dice(rng); }

private:
  std::random_device rd;
  std::uniform_real_distribution<float> dice;

  mutable std::mt19937 rng;
};
