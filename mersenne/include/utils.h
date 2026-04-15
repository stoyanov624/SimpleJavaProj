#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>

typedef unsigned long long ull;

#define MAX_VAL      2305843009213693951ULL  /* 2^61 - 1 */
#define MAX_DIVISORS 2048

ull  gcd(ull a, ull b);
ull  mulmod(ull a, ull b, ull m);
ull  powmod(ull base, ull exp, ull mod);
bool is_prime(ull n);
int  get_exponent(ull n);
void sort_ull(ull *arr, int n);
int  unique_ull(ull *arr, int n);

#endif
