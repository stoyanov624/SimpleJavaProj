#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Mersenne {
public:
    // 1. Проверява дали n е мерсеново число
    static bool isMersenne(uint64_t n);

    // 2. Проверява дали мерсеновото число n е просто
    static bool isMersennePrime(uint64_t n);

    // 3. Връща всички делители на n (без 1 и самото n)
    static std::vector<uint64_t> getDivisors(uint64_t n);

    // 4. Връща простите делители на n
    static std::vector<uint64_t> getPrimeDivisors(uint64_t n);

    // 5. Връща разликата A\B на съставните делители на a и b
    static std::vector<uint64_t> compositeDivisorsDiff(uint64_t a, uint64_t b);

    // 6. Връща всички мерсенови числа в [low, high]
    static std::vector<uint64_t> inRange(uint64_t low, uint64_t high);

    // 7. Връща първите n мерсенови числа
    static std::vector<uint64_t> first(int n);

    // 8. Връща първите n мерсенови прости числа
    static std::vector<uint64_t> firstPrimes(int n);

    // 9. Същото като firstPrimes — запазва в контейнер (alias за яснота)
    static std::vector<uint64_t> getNPrimes(int n);

    // 10. Връща представянето "2^(p-1).(2^p-1)" на първите n съвършени числа
    static std::vector<std::string> perfectNumbersRepr(int n);

private:
    static bool                    lucasLehmer(int p);
    static std::vector<uint64_t>   allDivisors(uint64_t n);
    static std::vector<uint64_t>   getCompositeDivisors(uint64_t n);
};
