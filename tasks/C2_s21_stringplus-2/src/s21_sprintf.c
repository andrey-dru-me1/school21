#include <stdarg.h>
#include <stdbool.h>

#include "s21_string.h"

#define ABS(N) ((N) < 0) ? -(N) : (N)

#define MAX(A, B) ((A) > (B) ? (A) : (B))

struct flags {
  bool left_align, print_plus, zeros, sign_place;
};

enum status { out = 0, flags, width, precision, length, conversion };

enum length { standard = 0, h, l, L, ll };

struct state {
  struct flags flags;
  enum status status;
  enum length length;
  int width, precision, radix;
  bool upper, precision_changed;
};

static char DIGITS[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                          '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static bool contains(char *set, char c) {
  while (*set)
    if (*set++ == c) return true;
  return false;
}

static char to_upper(char c) {
  if (c >= 'a' && c <= 'z') return c + ('A' - 'a');
  return c;
}

static double ten_pow(double num, int pow) {
  for (int i = 0; i < pow; i++) num *= 10;
  return num;
}

static int align_output(char *str, int actual_len, struct state state) {
  int chars_appended = 0;
  char placeholder = state.flags.zeros ? '0' : ' ';
  if (actual_len < state.width) {
    if (!state.flags.left_align) {
      for (int i = 1; i <= actual_len; i++)
        str[state.width - i] = str[actual_len - i];
    } else
      str += actual_len;
    for (int i = 0; i < state.width - actual_len; i++) str[i] = placeholder;
    chars_appended = state.width - actual_len;
  }
  return chars_appended;
}

int unsigned_to_str(char *str, long long unsigned num, struct state state) {
  int num_len = 0;
  if (num == 0) str[num_len++] = '0';
  while (num) {
    int digit = num % state.radix;
    str[num_len++] = state.upper ? to_upper(DIGITS[digit]) : DIGITS[digit];
    num /= state.radix;
  }
  for (int i = 0; i * 2 < num_len; i++) {
    char c = str[num_len - 1 - i];
    str[num_len - 1 - i] = str[i];
    str[i] = c;
  }

  struct state ustate = state;
  ustate.width = MAX(state.width, state.precision);
  if (state.precision_changed) ustate.flags.zeros = true;
  num_len += align_output(str, num_len, ustate);
  return num_len;
}

int signed_to_str(char *str, long long num, struct state state) {
  int istr = 0;
  if (num < 0) {
    str[istr++] = '-';
    num = -num;
  } else if (state.flags.print_plus)
    str[istr++] = '+';
  else if (state.flags.sign_place)
    str[istr++] = ' ';

  struct state ustate = state;
  ustate.width = state.flags.zeros ? (state.width - istr) : 0;
  istr += unsigned_to_str(str + istr, num, ustate);

  if (!state.flags.zeros) istr += align_output(str, istr, state);

  return istr;
}

static int add_double(char *str, double num, struct state state) {
  if (!state.precision_changed) state.precision = 6;

  int istr = 0;
  long long int_part =
      num + (state.precision == 0 ? (num < 0 ? -0.5 : 0.5) : 0);
  long long fraction = ten_pow(ABS(num - int_part), state.precision) + 0.5;

  struct state istate = state;
  istate.width -= state.precision + (state.precision ? 1 : 0);
  istate.precision = 0;
  istr += signed_to_str(str + istr, int_part, istate);
  if (state.precision) str[istr++] = '.';

  if (state.precision)
    istr +=
        unsigned_to_str(str + istr, fraction,
                        (struct state){.radix = 10,
                                       .width = state.precision,
                                       .flags = (struct flags){.zeros = true},
                                       .upper = false});

  istr += align_output(str, istr, state);
  return istr;
}

static int s21_strcpy(char *dst, char *src) {
  char *p = dst;
  while (*src) *p++ = *src++;
  *p = 0;
  return p - dst;
}

static bool is_digit(char n) { return n >= '0' && n <= '9'; }

static inline int s21_vsprintf(char *restrict str, const char *restrict format,
                               va_list ap) {
  struct state state = {0};

  int istr, iformat;
  for (istr = iformat = 0; format[iformat]; iformat++) {
    char c = format[iformat];
    if (state.status != out) {
      if (contains("Xxou%cidfeEs", c)) {
        state.radix = 10;
        switch (c) {
          case 'X':
          case 'x':
            state.radix = 16;
            break;
          case 'o':
            state.radix = 8;
            break;
          case '%':
            str[istr++] = '%';
            break;
          case 'c':
            str[istr++] = (char)va_arg(ap, int);
            istr += align_output(str + istr - 1, 1, state);
            break;
          case 's': {
            int start = istr;
            istr += s21_strcpy(str + istr, (char *)va_arg(ap, char *));
            istr += align_output(str + start, istr - start, state);
            break;
          }
        }

        if (contains("Xxou", c)) {
          state.upper = (c == 'X');
          switch (state.length) {
            case l:
              istr +=
                  unsigned_to_str(str + istr, va_arg(ap, long unsigned), state);
              break;
            case ll:
              istr += unsigned_to_str(str + istr,
                                      va_arg(ap, long long unsigned), state);
              break;
            default:
              istr += unsigned_to_str(str + istr, va_arg(ap, unsigned), state);
              break;
          }
        } else if (contains("id", c)) {
          switch (state.length) {
            case l:
              istr += signed_to_str(str + istr, va_arg(ap, long), state);
              break;
            case ll:
              istr += signed_to_str(str + istr, va_arg(ap, long long), state);
              break;
            default:
              istr += signed_to_str(str + istr, va_arg(ap, int), state);
              break;
          }
        } else if (c == 'f') {
          switch (state.length) {
            case L:
              istr += add_double(str + istr, va_arg(ap, long double), state);
              break;
            default:
              istr += add_double(str + istr, va_arg(ap, double), state);
              break;
          }
        } else if (contains("eE", c)) {
          long double number = (state.length == L) ? va_arg(ap, long double)
                                                   : va_arg(ap, double);
          const int start_istr = istr;
          int e = 0;
          while (number < 1. && number > -1.) {
            number *= 10.;
            e--;
          }
          while (number >= 10. || number <= -10.) {
            number /= 10.;
            e++;
          }

          struct state dstate = state;
          dstate.width = 0;
          istr += add_double(str + istr, number, dstate);

          str[istr++] = (c == 'e') ? 'e' : 'E';

          istr += signed_to_str(
              str + istr, e,
              (struct state){
                  .flags = (struct flags){.print_plus = true, .zeros = true},
                  .radix = 10,
                  .width = 3});

          istr += align_output(str + start_istr, istr - start_istr, state);
        }
        state = (struct state){0};
      } else if (c == '+')
        state.flags.print_plus = true;
      else if (c == '-')
        state.flags.left_align = true;
      else if (c == ' ')
        state.flags.sign_place = true;
      else if (state.status == flags && c == '0')
        state.flags.zeros = true;
      else if (c == 'h')
        state.length = h;
      else if (state.length == l && c == 'l')
        state.length = ll;
      else if (c == 'l')
        state.length = l;
      else if (c == 'L')
        state.length = L;
      else if (state.status == precision && is_digit(c)) {
        state.precision = state.precision * 10 + (c - '0');
      } else if (is_digit(c)) {
        state.width = state.width * 10 + (c - '0');
        state.status = width;
      } else if (c == '.') {
        state.status = precision;
        state.precision_changed = true;
      }
    } else if (c == '%')
      state.status = flags;
    else
      str[istr++] = c;
  }
  str[istr] = format[iformat];
  return istr;
}

int s21_sprintf(char *restrict str, const char *restrict format, ...) {
  va_list ap;
  va_start(ap, format);
  int res = s21_vsprintf(str, format, ap);
  va_end(ap);
  return res;
}
