#include "Utils.h"
#include <algorithm>

namespace utils {

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b) { uint64_t t = b; b = a % b; a = t; }
    return a;
}

// Умножение по модул без overflow — използва 128-битова аритметика на GCC
uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    return static_cast<__uint128_t>(a) * b % m;
}

// Бързо степенуване по модул — O(log exp)
uint64_t powmod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// Един кръг от Miller-Rabin с свидетел a
static bool millerRabinRound(uint64_t n, uint64_t a) {
    if (n % a == 0) return n == a;
    uint64_t d = n - 1;
    int r = 0;
    while (d % 2 == 0) { d >>= 1; r++; }
    uint64_t x = powmod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

// Детерминистичен тест за простота — коректен за всички n < 3.3 * 10^24
bool isPrime(uint64_t n) {
    if (n < 2)       return false;
    if (n == 2)      return true;
    if (n % 2 == 0)  return false;
    if (n < 9)       return true;
    if (n % 3 == 0)  return false;

    for (uint64_t w : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}) {
        if (!millerRabinRound(n, w)) return false;
    }
    return true;
}

// Връща p > 1 такова, че n = 2^p - 1; иначе -1
int getExponent(uint64_t n) {
    if (n < 3) return -1;
    uint64_t m = n + 1;
    if (m == 0) return -1;           // overflow: n == UINT64_MAX
    if (m & (m - 1)) return -1;      // m не е степен на 2
    int p = 0;
    while (m > 1) { m >>= 1; p++; }
    return (p > 1) ? p : -1;
}

void sortAndUnique(std::vector<uint64_t>& v) {
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
}

} // namespace utils
