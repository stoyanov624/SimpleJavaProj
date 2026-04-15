#include "Utils.h"
#include <cstdlib>

ull gcd(ull a, ull b) {
    while (b) {
        ull t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Умножение по модул без overflow — използва 128-битова аритметика
ull mulmod(ull a, ull b, ull m) {
    return (__uint128_t)a * b % m;
}

// Бързо степенуване по модул
ull powmod(ull base, ull exp, ull mod) {
    ull result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp = exp / 2;
    }
    return result;
}

// Един кръг от теста на Miller-Rabin с свидетел a
static bool millerRabinRound(ull n, ull a) {
    if (n % a == 0) return n == a;
    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) { d = d / 2; r++; }
    ull x = powmod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

// Детерминистичен тест за простота — коректен за n < 3.3 * 10^24
bool isPrime(ull n) {
    if (n < 2)       return false;
    if (n == 2)      return true;
    if (n % 2 == 0)  return false;
    if (n < 9)       return true;
    if (n % 3 == 0)  return false;

    ull witnesses[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < 12; i++) {
        if (!millerRabinRound(n, witnesses[i]))
            return false;
    }
    return true;
}

// Връща p > 1 такова, че n = 2^p - 1; иначе -1
int getExponent(ull n) {
    if (n < 3) return -1;
    ull m = n + 1;
    if (m == 0) return -1;        // overflow
    if (m & (m - 1)) return -1;   // не е степен на 2
    int p = 0;
    while (m > 1) { m = m / 2; p++; }
    return (p > 1) ? p : -1;
}

static int cmpUll(const void* a, const void* b) {
    ull x = *(ull*)a;
    ull y = *(ull*)b;
    if (x < y) return -1;
    if (x > y) return  1;
    return 0;
}

void sortArr(ull* arr, int size) {
    qsort(arr, size, sizeof(ull), cmpUll);
}
