#include <iostream>
#include "Mersenne.h"

using namespace std;

void sep(const string& title) {
    cout << "\n--- " << title << " ---" << endl;
}

void printVec(const vector<ull>& v) {
    if (v.empty()) { cout << "(празно)" << endl; return; }
    for (auto x : v) cout << x << "  ";
    cout << endl;
}

int main() {
    Mersenne m;

    cout << "================================================" << endl;
    cout << "   МЕРСЕНОВИ ЧИСЛА — C++ демонстрация"           << endl;
    cout << "================================================" << endl;

    // 1
    sep("1. Проверка: число на Мерсен?");
    for (ull n : {3ULL, 7ULL, 10ULL, 15ULL, 31ULL, 63ULL, 127ULL}) {
        cout << "  " << n << " -> " << (m.isMersenne(n) ? "ДА" : "НЕ") << endl;
    }

    // 2
    sep("2. Проверка: просто мерсеново число?");
    for (ull n : {3ULL, 7ULL, 15ULL, 31ULL, 127ULL, 2047ULL, 8191ULL}) {
        if (m.isMersenne(n)) {
            cout << "  " << n << " -> "
                 << (m.isMersennePrime(n) ? "ПРОСТО" : "СЪСТАВНО") << endl;
        }
    }

    // 3
    sep("3. Делители (без 1 и самото число)");
    for (ull n : {12ULL, 28ULL, 31ULL, 60ULL}) {
        cout << "  Делители на " << n << ": ";
        printVec(m.getDivisors(n));
    }

    // 4
    sep("4. Прости делители");
    for (ull n : {60ULL, 360ULL, 2310ULL}) {
        cout << "  Прости делители на " << n << ": ";
        printVec(m.getPrimeDivisors(n));
    }

    // 5
    sep("5. Разлика на съставни делители (A \\ B)");
    cout << "  Съставни(120) \\ Съставни(60): ";
    printVec(m.compositeDivisorsDiff(120, 60));
    cout << "  Съставни(60)  \\ Съставни(48): ";
    printVec(m.compositeDivisorsDiff(60, 48));

    // 6
    sep("6. Мерсенови числа в интервал");
    cout << "  [1, 10000]:     "; printVec(m.inRange(1, 10000));
    cout << "  [100, 1000000]: "; printVec(m.inRange(100, 1000000));

    // 7
    sep("7. Първите 10 мерсенови числа");
    printVec(m.first(10));

    // 8
    sep("8. Първите 6 мерсенови прости числа");
    printVec(m.firstPrimes(6));

    // 9
    sep("9. Всичките 9 мерсенови прости числа");
    for (auto mp : m.getNPrimes(9)) {
        int p = getExponent(mp);
        cout << "  M_" << p << " = 2^" << p << " - 1 = " << mp << endl;
    }

    // 10
    sep("10. Представяне на съвършените числа");
    for (const auto& s : m.perfectNumbersRepr(8)) {
        cout << "  " << s << endl;
    }

    cout << "\n================================================" << endl;
    return 0;
}
