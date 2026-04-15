#include "mersenne.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ */
/*  Вътрешни помощни функции                                           */
/* ------------------------------------------------------------------ */

/*
 * Тест на Lucas-Lehmer: проверява дали 2^p - 1 е просто.
 * Предварително условие: p е просто.
 *
 * Алгоритъм:
 *   s₀ = 4
 *   sᵢ = (sᵢ₋₁² - 2)  mod  Mₚ,  за i = 1..p-2
 *   Mₚ е просто ⟺ s_{p-2} = 0
 */
static bool lucas_lehmer(int p) {
    if (p == 2) return true;
    ull mp = (1ULL << p) - 1;
    ull s  = 4;
    for (int i = 0; i < p - 2; i++) {
        s = (__uint128_t)s * s % mp;
        s = (s >= 2) ? s - 2 : s + mp - 2;
    }
    return s == 0;
}

/*
 * Връща всички делители на n, без 1 и самото n.
 * Използва деление с пробване до sqrt(n) без риск от overflow.
 */
static int get_all_divisors(ull n, ull *arr) {
    int count = 0;
    for (ull i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            if (count < MAX_DIVISORS)     arr[count++] = i;
            if (i != n / i && count < MAX_DIVISORS) arr[count++] = n / i;
        }
    }
    sort_ull(arr, count);
    return count;
}

/* Връща само съставните делители (не прости, не 1, не n) */
static int get_composite_divisors(ull n, ull *arr) {
    ull all[MAX_DIVISORS];
    int total = get_all_divisors(n, all);
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (!is_prime(all[i])) arr[count++] = all[i];
    }
    return count;
}

/* ------------------------------------------------------------------ */
/*  Функции 1–10                                                       */
/* ------------------------------------------------------------------ */

/* 1 */
bool is_mersenne(ull n) {
    return get_exponent(n) != -1;
}

/* 2 */
bool is_mersenne_prime(ull n) {
    int p = get_exponent(n);
    if (p == -1)              return false;   /* не е мерсеново */
    if (!is_prime((ull)p))    return false;   /* необходимо: p е просто */
    return lucas_lehmer(p);
}

/* 3 */
void show_divisors(ull n) {
    if (n < 2) {
        printf("  Невалидно: n трябва да е >= 2.\n");
        return;
    }
    ull arr[MAX_DIVISORS];
    int count = get_all_divisors(n, arr);
    if (count == 0) {
        printf("  %llu е просто — няма делители освен 1 и себе си.\n", n);
        return;
    }
    printf("  Делители на %llu: ", n);
    for (int i = 0; i < count; i++) {
        printf("%llu", arr[i]);
        if (i < count - 1) printf(", ");
    }
    printf("\n");
}

/* 4 */
int get_prime_divisors(ull n, ull *arr) {
    ull all[MAX_DIVISORS];
    int total = get_all_divisors(n, all);
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (is_prime(all[i])) arr[count++] = all[i];
    }
    return count;
}

/* 5 — разлика на множествата: съставни_делители(a)  \  съставни_делители(b) */
int composite_divisors_diff(ull a, ull b, ull *arr) {
    ull ca[MAX_DIVISORS], cb[MAX_DIVISORS];
    int na = get_composite_divisors(a, ca);
    int nb = get_composite_divisors(b, cb);
    int count = 0;
    for (int i = 0; i < na; i++) {
        bool in_b = false;
        for (int j = 0; j < nb; j++) {
            if (ca[i] == cb[j]) { in_b = true; break; }
        }
        if (!in_b) arr[count++] = ca[i];
    }
    return count;
}

/* 6 */
void mersenne_in_range(ull low, ull high) {
    if (low > high) {
        printf("  Невалиден интервал: low > high.\n");
        return;
    }
    if (high > MAX_VAL) {
        printf("  Невалиден интервал: high > MAX_VAL (2^61-1).\n");
        return;
    }
    printf("  Мерсенови числа в [%llu, %llu]:\n  ", low, high);
    bool found = false;
    for (int p = 2; p <= 62; p++) {
        ull m = (1ULL << p) - 1;
        if (m > high) break;
        if (m >= low) { printf("%llu  ", m); found = true; }
    }
    if (!found) printf("(няма)");
    printf("\n");
}

/* 7 */
void first_n_mersenne(int n) {
    if (n <= 0) { printf("  n трябва да е > 0.\n"); return; }
    printf("  Първите %d мерсенови числа:\n  ", n);
    int count = 0;
    for (int p = 2; count < n && p <= 62; p++) {
        ull m = (1ULL << p) - 1;
        if (m > MAX_VAL) break;
        printf("%llu  ", m);
        count++;
    }
    printf("\n");
}

/* 8 */
void first_n_mersenne_primes(int n) {
    if (n <= 0 || n > 9) {
        printf("  n трябва да е между 1 и 9.\n");
        return;
    }
    printf("  Първите %d мерсенови прости числа:\n  ", n);
    int count = 0;
    for (int p = 2; count < n && p <= 61; p++) {
        if (!is_prime((ull)p)) continue;
        if (lucas_lehmer(p)) {
            printf("%llu  ", (1ULL << p) - 1);
            count++;
        }
    }
    printf("\n");
}

/* 9 */
int get_n_mersenne_primes(int n, ull *arr) {
    if (n <= 0 || n > 9) return 0;
    int count = 0;
    for (int p = 2; count < n && p <= 61; p++) {
        if (!is_prime((ull)p)) continue;
        if (lucas_lehmer(p)) arr[count++] = (1ULL << p) - 1;
    }
    return count;
}

/*
 * 10 — Представяне 2^(p-1).(2^p-1) на първите n четни съвършени числа.
 *      Използва връзката: четното съвършено число = 2^(p-1) * (2^p - 1),
 *      където p и 2^p-1 са прости.
 */
int perfect_numbers_repr(int n, char arr[][64]) {
    if (n <= 0 || n > 8) {
        printf("  n трябва да е между 1 и 8.\n");
        return 0;
    }
    /* Експонентите на първите 8 прости числа на Мерсен */
    static const int exponents[] = {2, 3, 5, 7, 13, 17, 19, 31};
    for (int i = 0; i < n; i++) {
        int p = exponents[i];
        snprintf(arr[i], 64, "2^(%d-1).(2^%d-1)", p, p);
    }
    return n;
}
