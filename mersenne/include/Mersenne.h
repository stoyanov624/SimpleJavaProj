#pragma once
#include <string>
#include <vector>
#include "Utils.h"

class Mersenne {
public:
    bool isMersenne(ll n);
    bool isMersennePrime(ll n);

    std::vector<ll>          getDivisors(ll n);
    std::vector<ll>          getPrimeDivisors(ll n);
    std::vector<ll>          compositeDivisorsDiff(ll a, ll b);
    std::vector<ll>          inRange(ll low, ll high);
    std::vector<ll>          first(int n);
    std::vector<ll>          firstPrimes(int n);
    std::vector<ll>          getNPrimes(int n);
    std::vector<std::string> perfectNumbersRepr(int n);

private:
    bool         lucasLehmer(int p);
    std::vector<ll> allDivisors(ll n);
    std::vector<ll> compositeDivisors(ll n);
};
