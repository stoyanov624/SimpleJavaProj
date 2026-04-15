#ifndef MERSENNE_H
#define MERSENNE_H

#include <stdbool.h>
#include "utils.h"

/* 1. Проверява дали n е мерсеново число (n = 2^p - 1, p > 1) */
bool is_mersenne(ull n);

/* 2. Проверява дали мерсеновото число n е просто (Lucas-Lehmer) */
bool is_mersenne_prime(ull n);

/* 3. Показва всички делители на n, без 1 и самото n */
void show_divisors(ull n);

/* 4. Записва в arr простите делители на n, връща броя им */
int  get_prime_divisors(ull n, ull *arr);

/* 5. Записва в arr разликата A\B на съставните делители на a и b */
int  composite_divisors_diff(ull a, ull b, ull *arr);

/* 6. Показва всички мерсенови числа в интервала [low, high] */
void mersenne_in_range(ull low, ull high);

/* 7. Показва първите n мерсенови числа */
void first_n_mersenne(int n);

/* 8. Показва първите n мерсенови прости числа */
void first_n_mersenne_primes(int n);

/* 9. Записва в arr първите n мерсенови прости числа, връща броя им */
int  get_n_mersenne_primes(int n, ull *arr);

/* 10. Записва представянето 2^(p-1).(2^p-1) на първите n съвършени числа */
/*     n <= 8; връща броя записани низове                                  */
int  perfect_numbers_repr(int n, char arr[][64]);

#endif
