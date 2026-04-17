#include "Utils.h"
#include <algorithm>

// Проверка за просто число с деление с пробване до корена
bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Връща p такова, че n = 2^p - 1; иначе -1
int getExponent(ll n) {
    for (int p = 2; p <= 31; p++) {
        if ((1LL << p) - 1 == n) return p;
    }
    return -1;
}

void sortAndUnique(std::vector<ll>& v) {
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
}
