#include "Mersenne.h"
#include <iostream>
#include <cstdio>

using namespace std;

// ------------------------------------------------------------------ //
//  Вътрешни (private) методи                                          //
// ------------------------------------------------------------------ //

bool Mersenne::lucasLehmer(int p) {
    if (p == 2) return true;
    ull mp = (1ULL << p) - 1;
    ull s  = 4;
    for (int i = 0; i < p - 2; i++) {
        s = (__uint128_t)s * s % mp;
        if (s >= 2)
            s = s - 2;
        else
            s = s + mp - 2;
    }
    return s == 0;
}

int Mersenne::getAllDivisors(ull n, ull arr[], int maxSize) {
    int count = 0;
    for (ull i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            if (count < maxSize) arr[count++] = i;
            if (i != n / i && count < maxSize) arr[count++] = n / i;
        }
    }
    sortArr(arr, count);
    return count;
}

int Mersenne::getCompositeDivisors(ull n, ull arr[], int maxSize) {
    ull all[MAX_SIZE];
    int total = getAllDivisors(n, all, MAX_SIZE);
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (!isPrime(all[i]) && count < maxSize)
            arr[count++] = all[i];
    }
    return count;
}

// ------------------------------------------------------------------ //
//  Публични методи                                                     //
// ------------------------------------------------------------------ //

bool Mersenne::isMersenne(ull n) {
    return getExponent(n) != -1;
}

bool Mersenne::isMersennePrime(ull n) {
    int p = getExponent(n);
    if (p == -1) return false;
    if (!isPrime((ull)p)) return false;
    return lucasLehmer(p);
}

void Mersenne::showDivisors(ull n) {
    if (n < 2) {
        cout << "  Грешка: n трябва да е >= 2" << endl;
        return;
    }
    ull arr[MAX_SIZE];
    int count = getAllDivisors(n, arr, MAX_SIZE);
    if (count == 0) {
        cout << "  " << n << " е просто — няма делители освен 1 и себе си." << endl;
        return;
    }
    cout << "  Делители на " << n << ": ";
    for (int i = 0; i < count; i++) {
        cout << arr[i];
        if (i < count - 1) cout << ", ";
    }
    cout << endl;
}

int Mersenne::getPrimeDivisors(ull n, ull arr[], int maxSize) {
    ull all[MAX_SIZE];
    int total = getAllDivisors(n, all, MAX_SIZE);
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (isPrime(all[i]) && count < maxSize)
            arr[count++] = all[i];
    }
    return count;
}

int Mersenne::compositeDivisorsDiff(ull a, ull b, ull arr[], int maxSize) {
    ull ca[MAX_SIZE], cb[MAX_SIZE];
    int na = getCompositeDivisors(a, ca, MAX_SIZE);
    int nb = getCompositeDivisors(b, cb, MAX_SIZE);

    int count = 0;
    for (int i = 0; i < na; i++) {
        bool found = false;
        for (int j = 0; j < nb; j++) {
            if (ca[i] == cb[j]) { found = true; break; }
        }
        if (!found && count < maxSize)
            arr[count++] = ca[i];
    }
    return count;
}

void Mersenne::showInRange(ull low, ull high) {
    if (low > high || high > MAX_VAL) {
        cout << "  Грешка: невалиден интервал." << endl;
        return;
    }
    cout << "  Мерсенови числа в [" << low << ", " << high << "]: ";
    bool found = false;
    for (int p = 2; p <= 62; p++) {
        ull m = (1ULL << p) - 1;
        if (m > high) break;
        if (m >= low) { cout << m << "  "; found = true; }
    }
    if (!found) cout << "(няма)";
    cout << endl;
}

void Mersenne::showFirst(int n) {
    if (n <= 0) { cout << "  Грешка: n > 0" << endl; return; }
    cout << "  Първите " << n << " мерсенови числа: ";
    int count = 0;
    for (int p = 2; count < n && p <= 62; p++) {
        ull m = (1ULL << p) - 1;
        if (m > MAX_VAL) break;
        cout << m << "  ";
        count++;
    }
    cout << endl;
}

void Mersenne::showFirstPrimes(int n) {
    if (n <= 0 || n > 9) { cout << "  Грешка: n между 1 и 9" << endl; return; }
    cout << "  Първите " << n << " мерсенови прости числа: ";
    int count = 0;
    for (int p = 2; count < n && p <= 61; p++) {
        if (!isPrime((ull)p)) continue;
        if (lucasLehmer(p)) {
            cout << (1ULL << p) - 1 << "  ";
            count++;
        }
    }
    cout << endl;
}

int Mersenne::getNPrimes(int n, ull arr[], int maxSize) {
    if (n <= 0 || n > 9) return 0;
    int count = 0;
    for (int p = 2; count < n && p <= 61; p++) {
        if (!isPrime((ull)p)) continue;
        if (lucasLehmer(p) && count < maxSize)
            arr[count++] = (1ULL << p) - 1;
    }
    return count;
}

int Mersenne::perfectNumbersRepr(int n, char arr[][64]) {
    if (n <= 0 || n > 8) { cout << "  Грешка: n между 1 и 8" << endl; return 0; }
    int exponents[] = {2, 3, 5, 7, 13, 17, 19, 31};
    for (int i = 0; i < n; i++) {
        int p = exponents[i];
        sprintf(arr[i], "2^(%d-1).(2^%d-1)", p, p);
    }
    return n;
}
