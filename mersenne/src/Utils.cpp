#include "Utils.h"
#include <algorithm>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long powmod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = result * base % mod;
        base = base * base % mod;
        exp = exp / 2;
    }
    return result;
}

static bool millerRabinRound(long long n, long long a) {
    if (n % a == 0) return n == a;
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) { d = d / 2; r++; }
    long long x = powmod(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {
        x = x * x % n;
        if (x == n - 1) return true;
    }
    return false;
}

bool isPrime(long long n) {
    if (n < 2)      return false;
    if (n == 2)     return true;
    if (n % 2 == 0) return false;
    if (n < 9)      return true;
    if (n % 3 == 0) return false;

    long long witnesses[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (auto w : witnesses) {
        if (!millerRabinRound(n, w)) return false;
    }
    return true;
}

int getExponent(long long n) {
    if (n < 3) return -1;
    long long m = n + 1;
    if (m & (m - 1)) return -1;  // не е степен на 2
    int p = 0;
    while (m > 1) { m = m / 2; p++; }
    return (p > 1) ? p : -1;
}

void sortAndUnique(std::vector<long long>& v) {
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
}
