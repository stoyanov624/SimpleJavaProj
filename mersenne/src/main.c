#include <stdio.h>
#include "mersenne.h"
#include "utils.h"

static void sep(const char *title) {
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║  %s\n", title);
    printf("╚══════════════════════════════════════╝\n");
}

int main(void) {
    printf("=================================================\n");
    printf("   МЕРСЕНОВИ ЧИСЛА — демонстрация на функциите  \n");
    printf("=================================================\n");

    /* --- 1. is_mersenne --- */
    sep("1. Проверка: число на Мерсен?");
    ull test1[] = {2, 3, 7, 10, 15, 31, 63, 127, 8191};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    for (int i = 0; i < n1; i++) {
        printf("  %6llu -> %s\n", test1[i],
               is_mersenne(test1[i]) ? "ДА (мерсеново)" : "НЕ");
    }

    /* --- 2. is_mersenne_prime --- */
    sep("2. Проверка: просто число на Мерсен?");
    ull test2[] = {3, 7, 15, 31, 63, 127, 2047, 8191};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    for (int i = 0; i < n2; i++) {
        if (is_mersenne(test2[i])) {
            printf("  %6llu -> %s\n", test2[i],
                   is_mersenne_prime(test2[i]) ? "ПРОСТО" : "СЪСТАВНО");
        }
    }

    /* --- 3. show_divisors --- */
    sep("3. Делители (без 1 и самото число)");
    ull test3[] = {12, 28, 31, 60, 100};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    for (int i = 0; i < n3; i++) show_divisors(test3[i]);

    /* --- 4. get_prime_divisors --- */
    sep("4. Прости делители");
    ull pd[MAX_DIVISORS];
    int pc;

    pc = get_prime_divisors(60, pd);
    printf("  Прости делители на 60: ");
    for (int i = 0; i < pc; i++) printf("%llu ", pd[i]);
    printf("\n");

    pc = get_prime_divisors(360, pd);
    printf("  Прости делители на 360: ");
    for (int i = 0; i < pc; i++) printf("%llu ", pd[i]);
    printf("\n");

    /* --- 5. composite_divisors_diff --- */
    sep("5. Разлика на съставни делители (A \\ B)");
    ull diff[MAX_DIVISORS];
    int dc;

    dc = composite_divisors_diff(120, 60, diff);
    printf("  Съставни_делители(120) \\ Съставни_делители(60): ");
    if (dc == 0) printf("(празно множество)");
    for (int i = 0; i < dc; i++) printf("%llu ", diff[i]);
    printf("\n");

    dc = composite_divisors_diff(60, 48, diff);
    printf("  Съставни_делители(60)  \\ Съставни_делители(48): ");
    if (dc == 0) printf("(празно множество)");
    for (int i = 0; i < dc; i++) printf("%llu ", diff[i]);
    printf("\n");

    /* --- 6. mersenne_in_range --- */
    sep("6. Мерсенови числа в интервал");
    mersenne_in_range(1, 10000);
    mersenne_in_range(100, 1000000);

    /* --- 7. first_n_mersenne --- */
    sep("7. Първите n мерсенови числа");
    first_n_mersenne(10);

    /* --- 8. first_n_mersenne_primes --- */
    sep("8. Първите n мерсенови прости числа");
    first_n_mersenne_primes(6);

    /* --- 9. get_n_mersenne_primes (всичките 9) --- */
    sep("9. Всичките 9 мерсенови прости числа в масив");
    ull primes[9];
    int cnt = get_n_mersenne_primes(9, primes);
    for (int i = 0; i < cnt; i++) {
        int p = get_exponent(primes[i]);
        printf("  M_%d  = 2^%d - 1 = %llu\n", p, p, primes[i]);
    }

    /* --- 10. perfect_numbers_repr --- */
    sep("10. Представяне на съвършените числа");
    char repr[8][64];
    int nr = perfect_numbers_repr(8, repr);
    for (int i = 0; i < nr; i++) {
        printf("  %s\n", repr[i]);
    }

    printf("\n=================================================\n");
    return 0;
}
