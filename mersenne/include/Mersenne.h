#pragma once
#include <string>
#include <vector>
#include "Utils.h"

class Mersenne {
public:
    bool isMersenne(long long n);
    bool isMersennePrime(long long n);

    std::vector<long long> getDivisors(long long n);
    std::vector<long long> getPrimeDivisors(long long n);
    std::vector<long long> compositeDivisorsDiff(long long a, long long b);
    std::vector<long long> inRange(long long low, long long high);
    std::vector<long long> first(int n);
    std::vector<long long> firstPrimes(int n);
    std::vector<long long> getNPrimes(int n);
    std::vector<std::string> perfectNumbersRepr(int n);

private:
    bool lucasLehmer(int p);
    std::vector<long long> allDivisors(long long n);
    std::vector<long long> compositeDivisors(long long n);
};
