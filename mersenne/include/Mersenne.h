#pragma once
#include "Utils.h"

class Mersenne {
public:
    // 1. Проверява дали n е мерсеново число
    bool isMersenne(ull n);

    // 2. Проверява дали мерсеновото число n е просто
    bool isMersennePrime(ull n);

    // 3. Показва всички делители на n (без 1 и самото n)
    void showDivisors(ull n);

    // 4. Записва простите делители на n в arr, връща броя им
    int getPrimeDivisors(ull n, ull arr[], int maxSize);

    // 5. Записва разликата A\B на съставните делители в arr, връща броя
    int compositeDivisorsDiff(ull a, ull b, ull arr[], int maxSize);

    // 6. Показва всички мерсенови числа в интервала [low, high]
    void showInRange(ull low, ull high);

    // 7. Показва първите n мерсенови числа
    void showFirst(int n);

    // 8. Показва първите n мерсенови прости числа
    void showFirstPrimes(int n);

    // 9. Записва първите n мерсенови прости числа в arr, връща броя
    int getNPrimes(int n, ull arr[], int maxSize);

    // 10. Записва представянето "2^(p-1).(2^p-1)" на съвършените числа
    int perfectNumbersRepr(int n, char arr[][64]);

private:
    bool lucasLehmer(int p);
    int  getAllDivisors(ull n, ull arr[], int maxSize);
    int  getCompositeDivisors(ull n, ull arr[], int maxSize);
};
