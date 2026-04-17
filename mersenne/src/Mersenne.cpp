#include "Mersenne.h"
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

// ------------------------------------------------------------------ //
// Private помощни методи
// ------------------------------------------------------------------ //

bool Mersenne::lucasLehmer(int p) {
    if (p == 2) return true;
    ll mp = (1LL << p) - 1;
    ll s  = 4;
    for (int i = 0; i < p - 2; i++) {
        s = (s * s - 2) % mp;
    }
    return s == 0;
}

vector<ll> Mersenne::allDivisors(ll n) {
    vector<ll> divs;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }
    sortAndUnique(divs);
    return divs;
}

vector<ll> Mersenne::compositeDivisors(ll n) {
    vector<ll> result;
    for (auto d : allDivisors(n)) {
        if (!isPrime(d)) result.push_back(d);
    }
    return result;
}

// ------------------------------------------------------------------ //
// Публични методи
// ------------------------------------------------------------------ //

bool Mersenne::isMersenne(ll n) {
    return getExponent(n) != -1;
}

bool Mersenne::isMersennePrime(ll n) {
    int p = getExponent(n);
    if (p == -1)             return false;
    if (!isPrime((ll)p))     return false;
    return lucasLehmer(p);
}

vector<ll> Mersenne::getDivisors(ll n) {
    if (n < 2) {
        cout << "Грешка: n трябва да е >= 2" << endl;
        return {};
    }
    return allDivisors(n);
}

vector<ll> Mersenne::getPrimeDivisors(ll n) {
    vector<ll> result;
    for (auto d : allDivisors(n)) {
        if (isPrime(d)) result.push_back(d);
    }
    return result;
}

vector<ll> Mersenne::compositeDivisorsDiff(ll a, ll b) {
    auto ca = compositeDivisors(a);
    auto cb = compositeDivisors(b);
    vector<ll> diff;
    for (auto x : ca) {
        if (find(cb.begin(), cb.end(), x) == cb.end())
            diff.push_back(x);
    }
    return diff;
}

vector<ll> Mersenne::inRange(ll low, ll high) {
    if (low > high || high > MAX_VAL) {
        cout << "Грешка: невалиден интервал" << endl;
        return {};
    }
    vector<ll> result;
    for (int p = 2; p <= 31; p++) {
        ll m = (1LL << p) - 1;
        if (m > high) break;
        if (m >= low) result.push_back(m);
    }
    return result;
}

vector<ll> Mersenne::first(int n) {
    if (n <= 0) { cout << "Грешка: n > 0" << endl; return {}; }
    vector<ll> result;
    for (int p = 2; (int)result.size() < n && p <= 31; p++) {
        result.push_back((1LL << p) - 1);
    }
    return result;
}

vector<ll> Mersenne::firstPrimes(int n) {
    if (n <= 0 || n > 8) { cout << "Грешка: n между 1 и 8" << endl; return {}; }
    vector<ll> result;
    for (int p = 2; (int)result.size() < n && p <= 31; p++) {
        if (!isPrime((ll)p)) continue;
        if (lucasLehmer(p)) result.push_back((1LL << p) - 1);
    }
    return result;
}

vector<ll> Mersenne::getNPrimes(int n) {
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
