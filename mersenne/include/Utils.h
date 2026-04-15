#pragma once
#include <cstdint>

typedef unsigned long long ull;

const ull MAX_VAL  = 2305843009213693951ULL;  // 2^61 - 1
const int MAX_SIZE = 1024;

ull  gcd(ull a, ull b);
ull  mulmod(ull a, ull b, ull m);
ull  powmod(ull base, ull exp, ull mod);
bool isPrime(ull n);
int  getExponent(ull n);  // p такова, че n = 2^p - 1; иначе -1
void sortArr(ull* arr, int size);
