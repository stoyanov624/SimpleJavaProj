#include "Utils.h"
#include <algorithm>
#include <cstdlib>

ull gcd(ull a, ull b) {
    while (b) {
        ull t = b;
        b = a % b;
        a = t;
    }
    return a;
}

ull mulmod(ull a, ull b, ull m) {
    return (__uint128_t)a * b % m;
}

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

bool isPrime(ull n) {
    if (n < 2)      return false;
    if (n == 2)     return true;
    if (n % 2 == 0) return false;
    if (n < 9)      return true;
    if (n % 3 == 0) return false;

    ull witnesses[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (auto w : witnesses) {
        if (!millerRabinRound(n, w)) return false;
    }
    return true;
}

int getExponent(ull n) {
    if (n < 3) return -1;
    ull m = n + 1;
    if (m == 0) return -1;
    if (m & (m - 1)) return -1;
    int p = 0;
    while (m > 1) { m = m / 2; p++; }
    return (p > 1) ? p : -1;
}

void sortAndUnique(std::vector<ull>& v) {
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
}
