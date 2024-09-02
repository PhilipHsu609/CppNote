/*
    C++11 PRNG
    1. Select the seed
    2. Define the random engine
        <type> generator(seed);
    3. Define the distribution
        <type> dist(start, end);
    4. Generate random numbers
        dist(generator);
*/

#include <random>

int main() {
    // obtain a random number from hardware
    // better than using time
    std::random_device rd;

    // We can also generate a seed with a sequence of seeds
    std::seed_seq seq{rd(), rd(), rd(), rd()};

    /*
        Random engines
        1. Linear congruential   (poor quality, fast)
        2. Mersenne Twister      (higher quality, slower)
        3. Subtract with carry   (higest quality, slowest)
    */

    // 1.
    std::minstd_rand0 gen0(rd());
    std::minstd_rand gen1(rd());
    std::knuth_b gen2(rd());

    // 2.
    std::mt19937 gen3(rd());
    std::mt19937_64 gen4(rd());

    // 3.
    std::ranlux24 gen7(rd());
    std::ranlux48 gen8(rd());

    /*
        Distributions
        1. Uniform distribution
        2. Bernoulli distribution
        3. Poisson distribution
        4. Normal distribution
        5. Sampling distribution
    */

    std::normal_distribution<float> dist(5.0f, 2.0f);
}