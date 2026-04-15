#pragma once
#include <string>
#include <vector>
#include "Utils.h"

class Mersenne {
public:
    // 1. Проверява дали n е мерсеново число
    bool isMersenne(ull n);

    // 2. Проверява дали мерсеновото число n е просто
    bool isMersennePrime(ull n);

    // 3. Връща всички делители на n (без 1 и самото n)
    std::vector<ull> getDivisors(ull n);

    // 4. Връща простите делители на n
    std::vector<ull> getPrimeDivisors(ull n);

    // 5. Връща разликата A\B на съставните делители на a и b
    std::vector<ull> compositeDivisorsDiff(ull a, ull b);

    // 6. Връща всички мерсенови числа в [low, high]
    std::vector<ull> inRange(ull low, ull high);

    // 7. Връща първите n мерсенови числа
    std::vector<ull> first(int n);

    // 8. Връща първите n мерсенови прости числа
    std::vector<ull> firstPrimes(int n);

    // 9. Записва в масив първите n мерсенови прости числа (alias на firstPrimes)
    std::vector<ull> getNPrimes(int n);

    // 10. Връща представянето "2^(p-1).(2^p-1)" на първите n съвършени числа
    std::vector<std::string> perfectNumbersRepr(int n);

private:
    bool             lucasLehmer(int p);
    std::vector<ull> allDivisors(ull n);
    std::vector<ull> compositeDivisors(ull n);
};
