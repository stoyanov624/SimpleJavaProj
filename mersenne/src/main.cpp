#include <iostream>
#include "Mersenne.h"

using namespace std;

void sep(const char* title) {
    cout << "\n--- " << title << " ---" << endl;
}

int main() {
    Mersenne m;

    cout << "================================================" << endl;
    cout << "   МЕРСЕНОВИ ЧИСЛА — C++ демонстрация"           << endl;
    cout << "================================================" << endl;

    // 1
    sep("1. Проверка: число на Мерсен?");
    ull test1[] = {3, 7, 10, 15, 31, 63, 127};
    for (int i = 0; i < 7; i++) {
        cout << "  " << test1[i] << " -> "
             << (m.isMersenne(test1[i]) ? "ДА" : "НЕ") << endl;
    }

    // 2
    sep("2. Проверка: просто мерсеново число?");
    ull test2[] = {3, 7, 15, 31, 127, 2047, 8191};
    for (int i = 0; i < 7; i++) {
        if (m.isMersenne(test2[i])) {
            cout << "  " << test2[i] << " -> "
                 << (m.isMersennePrime(test2[i]) ? "ПРОСТО" : "СЪСТАВНО") << endl;
        }
    }

    // 3
    sep("3. Делители (без 1 и самото число)");
    ull test3[] = {12, 28, 31, 60};
    for (int i = 0; i < 4; i++) {
        m.showDivisors(test3[i]);
    }

    // 4
    sep("4. Прости делители");
    ull pd[MAX_SIZE];
    int pc;
    ull test4[] = {60, 360, 2310};
    for (int i = 0; i < 3; i++) {
        pc = m.getPrimeDivisors(test4[i], pd, MAX_SIZE);
        cout << "  Прости делители на " << test4[i] << ": ";
        for (int j = 0; j < pc; j++) cout << pd[j] << " ";
        cout << endl;
    }

    // 5
    sep("5. Разлика на съставни делители (A \\ B)");
    ull diff[MAX_SIZE];
    int dc;

    dc = m.compositeDivisorsDiff(120, 60, diff, MAX_SIZE);
    cout << "  Съставни(120) \\ Съставни(60): ";
    for (int i = 0; i < dc; i++) cout << diff[i] << " ";
    cout << endl;

    dc = m.compositeDivisorsDiff(60, 48, diff, MAX_SIZE);
    cout << "  Съставни(60)  \\ Съставни(48): ";
    for (int i = 0; i < dc; i++) cout << diff[i] << " ";
    cout << endl;

    // 6
    sep("6. Мерсенови числа в интервал");
    m.showInRange(1, 10000);
    m.showInRange(100, 1000000);

    // 7
    sep("7. Първите 10 мерсенови числа");
    m.showFirst(10);

    // 8
    sep("8. Първите 6 мерсенови прости числа");
    m.showFirstPrimes(6);

    // 9
    sep("9. Всичките 9 мерсенови прости числа");
    ull primes[9];
    int cnt = m.getNPrimes(9, primes, 9);
    for (int i = 0; i < cnt; i++) {
        int p = getExponent(primes[i]);
        cout << "  M_" << p << " = 2^" << p << " - 1 = " << primes[i] << endl;
    }

    // 10
    sep("10. Представяне на съвършените числа");
    char repr[8][64];
    int nr = m.perfectNumbersRepr(8, repr);
    for (int i = 0; i < nr; i++) {
        cout << "  " << repr[i] << endl;
    }

    cout << "\n================================================" << endl;
    return 0;
}
