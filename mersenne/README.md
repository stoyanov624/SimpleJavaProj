# Мерсенови числа — C++ проект

> Проект по Лабораторни упражнения по Програмиране и Дискретна Математика

---

## Структура на проекта

```
mersenne/
├── Makefile
├── include/
│   ├── Utils.h      ← namespace utils: помощни функции
│   └── Mersenne.h   ← клас Mersenne: 10-те функции
└── src/
    ├── Utils.cpp
    ├── Mersenne.cpp
    └── main.cpp
```

**Разделното компилиране** — всеки `.cpp` файл се компилира поотделно до `.o` обектен файл, после линкерът ги свързва.

---

## Как се компилира

```bash
cd mersenne
make          # компилира
./mersenne    # пуска демото
make clean    # изчиства
```

---

## Архитектура

### `namespace utils` — помощни функции

| Функция | Описание |
|---------|----------|
| `gcd(a, b)` | Най-голям общ делител |
| `mulmod(a, b, m)` | `(a × b) mod m` без overflow (`__uint128_t`) |
| `powmod(base, exp, mod)` | Бързо степенуване по модул |
| `isPrime(n)` | Детерминистичен Miller-Rabin (коректен за n < 3.3×10²⁴) |
| `getExponent(n)` | Ако n = 2ᵖ−1 връща p, иначе −1 |
| `sortAndUnique(v)` | Сортира и премахва дублиращи се елементи |

---

### `class Mersenne` — 10-те функции

Всички методи са `static` — не е нужна инстанция.
Всички връщат `std::vector` или `std::string` вместо C масиви.
При невалидни аргументи се хвърля `std::invalid_argument`.

| # | Метод | Връща |
|---|-------|-------|
| 1 | `isMersenne(n)` | `bool` |
| 2 | `isMersennePrime(n)` | `bool` |
| 3 | `getDivisors(n)` | `vector<uint64_t>` |
| 4 | `getPrimeDivisors(n)` | `vector<uint64_t>` |
| 5 | `compositeDivisorsDiff(a, b)` | `vector<uint64_t>` |
| 6 | `inRange(low, high)` | `vector<uint64_t>` |
| 7 | `first(n)` | `vector<uint64_t>` |
| 8 | `firstPrimes(n)` | `vector<uint64_t>` |
| 9 | `getNPrimes(n)` | `vector<uint64_t>` |
| 10 | `perfectNumbersRepr(n)` | `vector<string>` |

---

## Алгоритми

### Lucas-Lehmer
Специализиран тест за мерсенови прости числа:
- s₀ = 4
- sᵢ = (sᵢ₋₁² − 2) mod Mₚ, за i = 1..p-2
- Mₚ е просто ⟺ s_{p-2} = 0

### Miller-Rabin
Детерминистичен тест за простота с 12 свидетеля. Покрива диапазона [0, 2⁶¹−1].

### Overflow защита
- `__uint128_t` за умножение по модул
- `i <= n/i` вместо `i*i <= n` при деление с пробване
- `1ULL << p` вместо `1 << p` за p ≥ 32

---

## Диапазон

Програмата работи с числа в **[0, 2⁶¹−1]** = [0, 2305843009213693951].

```cpp
constexpr uint64_t MAX_VAL = 2305843009213693951ULL; // utils::MAX_VAL
```

---

*Разработено за Лабораторни упражнения по Програмиране и Дискретна Математика*
