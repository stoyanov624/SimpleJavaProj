#include "utils.h"
#include <stdlib.h>
#include <string.h>

ull gcd(ull a, ull b) {
    while (b) { ull t = b; b = a % b; a = t; }
    return a;
}

/* Безопасно умножение по модул — използва 128-битова аритметика */
ull mulmod(ull a, ull b, ull m) {
    return (__uint128_t)a * b % m;
}

/* Бързо степенуване по модул */
ull powmod(ull base, ull exp, ull mod) {
    ull result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

/* Един кръг от теста на Miller-Rabin с свидетел a */
static bool miller_rabin_round(ull n, ull a) {
    if (n % a == 0) return n == a;
    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) { d >>= 1; r++; }
    ull x = powmod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

/*
 * Детерминистичен тест за простота (Miller-Rabin).
 * Коректен за всички n < 3.3 * 10^24 — покрива целия диапазон [0, 2^61-1].
 */
bool is_prime(ull n) {
    if (n < 2)        return false;
    if (n == 2)       return true;
    if (n % 2 == 0)   return false;
    if (n < 9)        return true;
    if (n % 3 == 0)   return false;

    static const ull witnesses[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < 12; i++) {
        if (!miller_rabin_round(n, witnesses[i])) return false;
    }
    return true;
}

/*
 * Връща p (p > 1) такова, че n = 2^p - 1.
 * Ако такова p не съществува, връща -1.
 */
int get_exponent(ull n) {
    if (n < 3) return -1;
    ull m = n + 1;
    if (m == 0) return -1;          /* overflow: n = ULLONG_MAX */
    if (m & (m - 1)) return -1;     /* m не е степен на 2 */
    int p = 0;
    while (m > 1) { m >>= 1; p++; }
    return (p > 1) ? p : -1;
}

static int cmp_ull(const void *a, const void *b) {
    ull x = *(const ull *)a;
    ull y = *(const ull *)b;
    return (x > y) - (x < y);
}

void sort_ull(ull *arr, int n) {
    qsort(arr, (size_t)n, sizeof(ull), cmp_ull);
}

/* Премахва дублиращи се елементи от сортиран масив; връща новия размер */
int unique_ull(ull *arr, int n) {
    if (n <= 0) return 0;
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) arr[k++] = arr[i];
    }
    return k;
}
