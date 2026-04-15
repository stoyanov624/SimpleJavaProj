#include "Mersenne.h"
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

bool Mersenne::lucasLehmer(int p) {
    if (p == 2) return true;
    ull mp = (1ULL << p) - 1;
    ull s  = 4;
    for (int i = 0; i < p - 2; i++) {
        s = (__uint128_t)s * s % mp;
        s = (s >= 2) ? s - 2 : s + mp - 2;
    }
    return s == 0;
}

vector<ull> Mersenne::allDivisors(ull n) {
    vector<ull> divs;
    for (ull i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    sortAndUnique(divs);
    return divs;
}

vector<ull> Mersenne::compositeDivisors(ull n) {
    vector<ull> result;
    for (auto d : allDivisors(n)) {
        if (!isPrime(d)) result.push_back(d);
    }
    return result;
}

// ------------------------------------------------------------------ //

bool Mersenne::isMersenne(ull n) {
    return getExponent(n) != -1;
}

bool Mersenne::isMersennePrime(ull n) {
    int p = getExponent(n);
    if (p == -1)         return false;
    if (!isPrime((ull)p)) return false;
    return lucasLehmer(p);
}

vector<ull> Mersenne::getDivisors(ull n) {
    if (n < 2) {
        cout << "Грешка: n трябва да е >= 2" << endl;
        return {};
    }
    return allDivisors(n);
}

vector<ull> Mersenne::getPrimeDivisors(ull n) {
    vector<ull> result;
    for (auto d : allDivisors(n)) {
        if (isPrime(d)) result.push_back(d);
    }
    return result;
}

vector<ull> Mersenne::compositeDivisorsDiff(ull a, ull b) {
    auto ca = compositeDivisors(a);
    auto cb = compositeDivisors(b);

    vector<ull> diff;
    for (auto x : ca) {
        if (find(cb.begin(), cb.end(), x) == cb.end())
            diff.push_back(x);
    }
    return diff;
}

vector<ull> Mersenne::inRange(ull low, ull high) {
    if (low > high || high > MAX_VAL) {
        cout << "Грешка: невалиден интервал" << endl;
        return {};
    }
    vector<ull> result;
    for (int p = 2; p <= 62; p++) {
        ull m = (1ULL << p) - 1;
        if (m > high) break;
        if (m >= low) result.push_back(m);
    }
    return result;
}

vector<ull> Mersenne::first(int n) {
    if (n <= 0) { cout << "Грешка: n > 0" << endl; return {}; }
    vector<ull> result;
    for (int p = 2; (int)result.size() < n && p <= 62; p++) {
        ull m = (1ULL << p) - 1;
        if (m > MAX_VAL) break;
        result.push_back(m);
    }
    return result;
}

vector<ull> Mersenne::firstPrimes(int n) {
    if (n <= 0 || n > 9) { cout << "Грешка: n между 1 и 9" << endl; return {}; }
    vector<ull> result;
    for (int p = 2; (int)result.size() < n && p <= 61; p++) {
        if (!isPrime((ull)p)) continue;
        if (lucasLehmer(p)) result.push_back((1ULL << p) - 1);
    }
    return result;
}

vector<ull> Mersenne::getNPrimes(int n) {
    return firstPrimes(n);
}

vector<string> Mersenne::perfectNumbersRepr(int n) {
    if (n <= 0 || n > 8) { cout << "Грешка: n между 1 и 8" << endl; return {}; }
    int exponents[] = {2, 3, 5, 7, 13, 17, 19, 31};
    vector<string> result;
    for (int i = 0; i < n; i++) {
        int p = exponents[i];
        char buf[64];
        sprintf(buf, "2^(%d-1).(2^%d-1)", p, p);
        result.push_back(buf);
    }
    return result;
}
