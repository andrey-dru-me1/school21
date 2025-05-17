#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

long long unsigned fact[] = {1UL,
                             1UL,
                             2UL,
                             6UL,
                             24UL,
                             120UL,
                             720UL,
                             5040UL,
                             40320UL,
                             362880UL,
                             3628800UL,
                             39916800UL,
                             479001600UL,
                             6227020800UL,
                             87178291200UL,
                             1307674368000UL,
                             20922789888000UL,
                             355687428096000UL,
                             6402373705728000UL,
                             121645100408832000UL};

#define ACC 0.5

long long unsigned factorial(unsigned n) {
  long long unsigned res = 1;
  for (unsigned i = 2; i <= n; i++) {
    res *= i;
  }
  return res;
}

long double mysin(long double x) {
  while (x > M_PI) {
    x -= 2 * M_PI;
  }
  while (x < -M_PI) {
    x += 2 * M_PI;
  }
  if (x > ACC || x < -ACC) {
    return 2 * mysin(x / 2) * cosl(x / 2);
  }
  long double res = 0;
  char sign = -1;
  for (long long int n = 19; n >= 1; n -= 2) {
    res += sign * powl(x, n) / factorial(n);
    sign = -sign;
  }
  return res;
}

long double improved_sin(long double x) {
  while (x > M_PI) {
    x -= 2 * M_PI;
  }
  while (x < -M_PI) {
    x += 2 * M_PI;
  }
  if (x > ACC || x < -ACC) {
    return 2 * improved_sin(x / 2) * cosl(x / 2);
  }
  long double res = 0;
  char sign = -1;
  const long double xx = x * x;
  for (long long int n = 19; n >= 3; n -= 2) {
    res = res * xx + (long double)sign / fact[n];
    sign = -sign;
  }
  return x + xx * x * res;
}

int main(void) {
  long double num = 3.14;
  clock_t lol = clock();
  long double lib_sin = sinl(num);

  clock_t st = clock();
  long double libsin = sinl(num);
  clock_t ts1 = clock();
  long double sin1 = mysin(num);
  clock_t ts2 = clock();
  long double sin2 = improved_sin(num);
  clock_t end = clock();
  printf("%2llu: %.50Lf\n%2llu: %.50Lf\n%2llu: %.50Lf\n", ts1 - st, libsin,
         ts2 - ts1, sin1, end - ts2, sin2);
}