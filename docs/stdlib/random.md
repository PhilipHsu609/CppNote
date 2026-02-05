---
title: "Random Numbers"
since: "C++11"
---


Modern random number generation.

## Basic Pattern

```cpp
#include <random>

// 1. Seed source
std::random_device rd;

// 2. Random engine
std::mt19937 gen(rd());

// 3. Distribution
std::uniform_int_distribution<int> dist(1, 100);

// 4. Generate
int value = dist(gen);
```

## Seed Sources

```cpp
std::random_device rd;  // hardware entropy (best)

// Seed sequence for better initialization
std::seed_seq seq{rd(), rd(), rd(), rd()};
std::mt19937 gen(seq);
```

## Engines

```cpp
// Linear congruential (fast, lower quality)
std::minstd_rand gen1(rd());

// Mersenne Twister (good balance)
std::mt19937 gen2(rd());       // 32-bit
std::mt19937_64 gen3(rd());    // 64-bit

// Subtract with carry (highest quality, slowest)
std::ranlux24 gen4(rd());
std::ranlux48 gen5(rd());
```

## Distributions

```cpp
// Uniform
std::uniform_int_distribution<int> d1(0, 100);
std::uniform_real_distribution<double> d2(0.0, 1.0);

// Normal (Gaussian)
std::normal_distribution<double> d3(mean, stddev);

// Bernoulli (coin flip)
std::bernoulli_distribution d4(0.5);  // 50% true

// Poisson
std::poisson_distribution<int> d5(lambda);

// And many more...
```

## Common Patterns

```cpp
// Shuffle
std::vector<int> v{1, 2, 3, 4, 5};
std::shuffle(v.begin(), v.end(), gen);

// Random element
auto it = v.begin();
std::advance(it, dist(gen) % v.size());
```

## Key Points

- Don't use `rand()` / `srand()` (poor quality)
- `random_device` for seeding, not generation
- `mt19937` is the go-to engine
- Match distribution to your needs
- Create engine once, reuse

## See Also

- [chrono](chrono.md) - time-based seeds (avoid if possible)
