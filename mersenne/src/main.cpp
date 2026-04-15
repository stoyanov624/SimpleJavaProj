#include <iostream>
#include "Mersenne.h"

using namespace std;

void sep(const string& title) {
    cout << "\n--- " << title << " ---" << endl;
}

void printVec(const vector<long long>& v) {
    if (v.empty()) { cout << "(празно)" << endl; return; }
    for (auto x : v) cout << x << "  ";
    cout << endl;
}

int main() {
    Mersenne m;

    cout << "================================================" << endl;
    cout << "   МЕРСЕНОВИ ЧИСЛА — C++ демонстрация"           << endl;
    cout << "================================================" << endl;

    sep("1. Проверка: число на Мерсен?");
    for (long long n : {3LL, 7LL, 10LL, 15LL, 31LL, 63LL, 127LL}) {
        cout << "  " << n << " -> " << (m.isMersenne(n) ? "ДА" : "НЕ") << endl;
    }

    sep("2. Проверка: просто мерсеново число?");
    for (long long n : {3LL, 7LL, 15LL, 31LL, 127LL, 2047LL, 8191LL}) {
        if (m.isMersenne(n)) {
            cout << "  " << n << " -> "
                 << (m.isMersennePrime(n) ? "ПРОСТО" : "СЪСТАВНО") << endl;
        }
    }

    sep("3. Делители (без 1 и самото число)");
    for (long long n : {12LL, 28LL, 31LL, 60LL}) {
        cout << "  Делители на " << n << ": ";
        printVec(m.getDivisors(n));
    }

    sep("4. Прости делители");
    for (long long n : {60LL, 360LL, 2310LL}) {
        cout << "  Прости делители на " << n << ": ";
        printVec(m.getPrimeDivisors(n));
    }

    sep("5. Разлика на съставни делители (A \\ B)");
    cout << "  Съставни(120) \\ Съставни(60): ";
    printVec(m.compositeDivisorsDiff(120, 60));
    cout << "  Съставни(60)  \\ Съставни(48): ";
    printVec(m.compositeDivisorsDiff(60, 48));

    sep("6. Мерсенови числа в интервал");
    cout << "  [1, 10000]:     "; printVec(m.inRange(1, 10000));
    cout << "  [100, 1000000]: "; printVec(m.inRange(100, 1000000));

    sep("7. Първите 10 мерсенови числа");
    printVec(m.first(10));

    sep("8. Първите 5 мерсенови прости числа");
    printVec(m.firstPrimes(5));

    sep("9. Всичките 8 мерсенови прости числа");
    for (auto mp : m.getNPrimes(8)) {
        int p = getExponent(mp);
        cout << "  M_" << p << " = 2^" << p << " - 1 = " << mp << endl;
    }

    sep("10. Представяне на съвършените числа");
    for (const auto& s : m.perfectNumbersRepr(8)) {
        cout << "  " << s << endl;
    }

    cout << "\n================================================" << endl;
    return 0;
}
