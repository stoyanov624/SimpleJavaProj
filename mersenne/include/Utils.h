#pragma once
#include <vector>

const long long MAX_VAL = 2147483647LL;  // M_31 = 2^31 - 1 (8-мото просто число на Мерсен)

long long gcd(long long a, long long b);
long long powmod(long long base, long long exp, long long mod);
bool      isPrime(long long n);
int       getExponent(long long n);
void      sortAndUnique(std::vector<long long>& v);
