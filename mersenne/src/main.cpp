#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Mersenne.h"
#include "Utils.h"

static void sep(const std::string& title) {
    std::cout << "\n--- " << title << " ---\n";
}

static void printVec(const std::vector<uint64_t>& v) {
    if (v.empty()) { std::cout << "(празно)\n"; return; }
    for (uint64_t x : v) std::cout << x << "  ";
    std::cout << "\n";
}

int main() {
    std::cout << "================================================\n";
    std::cout << "   МЕРСЕНОВИ ЧИСЛА — C++ демонстрация\n";
    std::cout << "================================================\n";

    // 1. isMersenne
    sep("1. Проверка: число на Мерсен?");
    for (uint64_t n : {3ULL, 7ULL, 10ULL, 15ULL, 31ULL, 63ULL, 127ULL}) {
        std::cout << "  " << std::setw(4) << n
                  << " -> " << (Mersenne::isMersenne(n) ? "ДА" : "НЕ") << "\n";
    }

    // 2. isMersennePrime
    sep("2. Проверка: просто мерсеново число?");
    for (uint64_t n : {3ULL, 7ULL, 15ULL, 31ULL, 127ULL, 2047ULL, 8191ULL}) {
        if (Mersenne::isMersenne(n)) {
            std::cout << "  " << std::setw(5) << n
                      << " -> " << (Mersenne::isMersennePrime(n) ? "ПРОСТО" : "СЪСТАВНО") << "\n";
        }
    }

    // 3. getDivisors
    sep("3. Делители (без 1 и самото число)");
    for (uint64_t n : {12ULL, 28ULL, 31ULL, 60ULL}) {
        std::cout << "  Делители на " << n << ": ";
        try { printVec(Mersenne::getDivisors(n)); }
        catch (const std::exception& e) { std::cout << e.what() << "\n"; }
    }

    // 4. getPrimeDivisors
    sep("4. Прости делители");
    for (uint64_t n : {60ULL, 360ULL, 2310ULL}) {
        std::cout << "  Прости делители на " << n << ": ";
        printVec(Mersenne::getPrimeDivisors(n));
    }

    // 5. compositeDivisorsDiff
    sep("5. Разлика на съставни делители (A \\ B)");
    auto diff1 = Mersenne::compositeDivisorsDiff(120, 60);
    std::cout << "  Съставни(120) \\ Съставни(60)  : "; printVec(diff1);

    auto diff2 = Mersenne::compositeDivisorsDiff(60, 48);
    std::cout << "  Съставни(60)  \\ Съставни(48)  : "; printVec(diff2);

    // 6. inRange
    sep("6. Мерсенови числа в интервал");
    std::cout << "  [1, 10000]:     "; printVec(Mersenne::inRange(1, 10000));
    std::cout << "  [100, 1000000]: "; printVec(Mersenne::inRange(100, 1000000));

    // 7. first
    sep("7. Първите 10 мерсенови числа");
    printVec(Mersenne::first(10));

    // 8. firstPrimes
    sep("8. Първите 6 мерсенови прости числа");
    printVec(Mersenne::firstPrimes(6));

    // 9. getNPrimes — всичките 9
    sep("9. Всичките 9 мерсенови прости числа");
    auto all9 = Mersenne::getNPrimes(9);
    for (uint64_t mp : all9) {
        int p = utils::getExponent(mp);
        std::cout << "  M_" << std::setw(2) << p
                  << " = 2^" << p << " - 1 = " << mp << "\n";
    }

    // 10. perfectNumbersRepr
    sep("10. Представяне на съвършените числа");
    for (const auto& s : Mersenne::perfectNumbersRepr(8)) {
        std::cout << "  " << s << "\n";
    }

    std::cout << "\n================================================\n";
    return 0;
}
