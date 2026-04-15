#pragma once

#include <cstdint>
#include <vector>

namespace utils {

    constexpr uint64_t MAX_VAL = 2305843009213693951ULL; // 2^61 - 1

    uint64_t gcd(uint64_t a, uint64_t b);
    uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m);
    uint64_t powmod(uint64_t base, uint64_t exp, uint64_t mod);
    bool     isPrime(uint64_t n);
    int      getExponent(uint64_t n); // p такова, че n = 2^p - 1; иначе -1

    void     sortAndUnique(std::vector<uint64_t>& v);

} // namespace utils
