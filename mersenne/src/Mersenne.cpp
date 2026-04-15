#include "Mersenne.h"
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

bool Mersenne::lucasLehmer(int p) {
    if (p == 2) return true;
    long long mp = (1LL << p) - 1;
    long long s  = 4;
    for (int i = 0; i < p - 2; i++) {
        s = (s * s - 2) % mp;
    }
    return s == 0;
}

vector<long long> Mersenne::allDivisors(long long n) {
    vector<long long> divs;
    for (long long i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    sortAndUnique(divs);
    return divs;
}

vector<long long> Mersenne::compositeDivisors(long long n) {
    vector<long long> result;
    for (auto d : allDivisors(n)) {
        if (!isPrime(d)) result.push_back(d);
    }
    return result;
}

bool Mersenne::isMersenne(long long n) {
    return getExponent(n) != -1;
}

bool Mersenne::isMersennePrime(long long n) {
    int p = getExponent(n);
    if (p == -1)         return false;
    if (!isPrime((long long)p)) return false;
    return lucasLehmer(p);
}

vector<long long> Mersenne::getDivisors(long long n) {
    if (n < 2) {
        cout << "Грешка: n трябва да е >= 2" << endl;
        return {};
    }
    return allDivisors(n);
}

vector<long long> Mersenne::getPrimeDivisors(long long n) {
    vector<long long> result;
    for (auto d : allDivisors(n)) {
        if (isPrime(d)) result.push_back(d);
    }
    return result;
}

vector<long long> Mersenne::compositeDivisorsDiff(long long a, long long b) {
    auto ca = compositeDivisors(a);
    auto cb = compositeDivisors(b);
    vector<long long> diff;
    for (auto x : ca) {
        if (find(cb.begin(), cb.end(), x) == cb.end())
            diff.push_back(x);
    }
    return diff;
}

vector<long long> Mersenne::inRange(long long low, long long high) {
    if (low > high || high > MAX_VAL) {
        cout << "Грешка: невалиден интервал" << endl;
        return {};
    }
    vector<long long> result;
    for (int p = 2; p <= 31; p++) {
        long long m = (1LL << p) - 1;
        if (m > high) break;
        if (m >= low) result.push_back(m);
    }
    return result;
}

vector<long long> Mersenne::first(int n) {
    if (n <= 0) { cout << "Грешка: n > 0" << endl; return {}; }
    vector<long long> result;
    for (int p = 2; (int)result.size() < n && p <= 31; p++) {
        result.push_back((1LL << p) - 1);
    }
    return result;
}

vector<long long> Mersenne::firstPrimes(int n) {
    if (n <= 0 || n > 8) { cout << "Грешка: n между 1 и 8" << endl; return {}; }
    vector<long long> result;
    for (int p = 2; (int)result.size() < n && p <= 31; p++) {
        if (!isPrime((long long)p)) continue;
        if (lucasLehmer(p)) result.push_back((1LL << p) - 1);
    }
    return result;
}

vector<long long> Mersenne::getNPrimes(int n) {
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
