#include "Mersenne.h"
#include "Utils.h"

#include <algorithm>
#include <stdexcept>
#include <cstdio>

// ------------------------------------------------------------------ //
//  Вътрешни помощни методи                                            //
// ------------------------------------------------------------------ //

/*
 * Тест на Lucas-Lehmer: 2^p - 1 е просто ⟺ s_{p-2} = 0
 *   s₀ = 4
 *   sᵢ = (sᵢ₋₁² − 2) mod Mₚ
 */
bool Mersenne::lucasLehmer(int p) {
    if (p == 2) return true;
    const uint64_t mp = (1ULL << p) - 1;
    uint64_t s = 4;
    for (int i = 0; i < p - 2; i++) {
        s = static_cast<__uint128_t>(s) * s % mp;
        s = (s >= 2) ? s - 2 : s + mp - 2;
    }
    return s == 0;
}

// Всички делители на n без 1 и самото n, сортирани
std::vector<uint64_t> Mersenne::allDivisors(uint64_t n) {
    std::vector<uint64_t> divs;
    for (uint64_t i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    utils::sortAndUnique(divs);
    return divs;
}

// Съставните делители = делителите, които не са прости
std::vector<uint64_t> Mersenne::getCompositeDivisors(uint64_t n) {
    std::vector<uint64_t> result;
    for (uint64_t d : allDivisors(n)) {
        if (!utils::isPrime(d)) result.push_back(d);
    }
    return result;
}

// ------------------------------------------------------------------ //
//  Публични методи (10-те функции)                                    //
// ------------------------------------------------------------------ //

// 1
bool Mersenne::isMersenne(uint64_t n) {
    return utils::getExponent(n) != -1;
}

// 2
bool Mersenne::isMersennePrime(uint64_t n) {
    int p = utils::getExponent(n);
    if (p == -1)                    return false;
    if (!utils::isPrime(static_cast<uint64_t>(p))) return false;
    return lucasLehmer(p);
}

// 3
std::vector<uint64_t> Mersenne::getDivisors(uint64_t n) {
    if (n < 2) throw std::invalid_argument("n трябва да е >= 2");
    return allDivisors(n);
}

// 4
std::vector<uint64_t> Mersenne::getPrimeDivisors(uint64_t n) {
    std::vector<uint64_t> result;
    for (uint64_t d : allDivisors(n)) {
        if (utils::isPrime(d)) result.push_back(d);
    }
    return result;
}

// 5
std::vector<uint64_t> Mersenne::compositeDivisorsDiff(uint64_t a, uint64_t b) {
    auto ca = getCompositeDivisors(a);
    auto cb = getCompositeDivisors(b);

    std::vector<uint64_t> diff;
    for (uint64_t x : ca) {
        if (std::find(cb.begin(), cb.end(), x) == cb.end()) {
            diff.push_back(x);
        }
    }
    return diff;
}

// 6
std::vector<uint64_t> Mersenne::inRange(uint64_t low, uint64_t high) {
    if (low > high || high > utils::MAX_VAL)
        throw std::invalid_argument("Невалиден интервал");

    std::vector<uint64_t> result;
    for (int p = 2; p <= 62; p++) {
        uint64_t m = (1ULL << p) - 1;
        if (m > high) break;
        if (m >= low) result.push_back(m);
    }
    return result;
}

// 7
std::vector<uint64_t> Mersenne::first(int n) {
    if (n <= 0) throw std::invalid_argument("n трябва да е > 0");
    std::vector<uint64_t> result;
    for (int p = 2; static_cast<int>(result.size()) < n && p <= 62; p++) {
        uint64_t m = (1ULL << p) - 1;
        if (m > utils::MAX_VAL) break;
        result.push_back(m);
    }
    return result;
}

// 8
std::vector<uint64_t> Mersenne::firstPrimes(int n) {
    if (n <= 0 || n > 9)
        throw std::invalid_argument("n трябва да е между 1 и 9");

    std::vector<uint64_t> result;
    for (int p = 2; static_cast<int>(result.size()) < n && p <= 61; p++) {
        if (!utils::isPrime(static_cast<uint64_t>(p))) continue;
        if (lucasLehmer(p)) result.push_back((1ULL << p) - 1);
    }
    return result;
}

// 9
std::vector<uint64_t> Mersenne::getNPrimes(int n) {
    return firstPrimes(n);
}

// 10
std::vector<std::string> Mersenne::perfectNumbersRepr(int n) {
    if (n <= 0 || n > 8)
        throw std::invalid_argument("n трябва да е между 1 и 8");

    static const int exponents[] = {2, 3, 5, 7, 13, 17, 19, 31};
    std::vector<std::string> result;
    for (int i = 0; i < n; i++) {
        int p = exponents[i];
        char buf[64];
        std::snprintf(buf, sizeof(buf), "2^(%d-1).(2^%d-1)", p, p);
        result.emplace_back(buf);
    }
    return result;
}
