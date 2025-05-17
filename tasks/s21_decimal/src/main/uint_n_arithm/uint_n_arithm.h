#ifndef S21_DECIMAL_UINT96_ARITHM
#define S21_DECIMAL_UINT96_ARITHM

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Compares two numbers and returns: 0 if they are equal; 1 if a > b; -1 if a <
 * b.
 *
 * @param a first long number to compare
 * @param a_len count of uint32 numbers in `a` array
 * @param b second long number to compare
 * @param b_len count of uint32 numbers in `b` array
 * @return equal: 0, greater: 1, less: -1
 */
char s21_uint_n_cmp(uint32_t *a, size_t a_len, uint32_t *b, size_t b_len);

/**
 * Multiplies a long number by an integer, stores the result under `res` pointer
 * and returns overflowing value. If an `additional_int` is set then overflowing
 * value will be stored to the most significant int of a res (to `res[a_len]`).
 *
 * @param a long integer to be multiplied
 * @param a_len count of uint32 numbers in `a` array
 * @param b typical number to be multiplied by
 * @param additional_int tells that overflowing value will be stored to the high
 * uint32 of `res` instead of being returned
 * @param res long number to store production to
 * @return multiplication overflow
 */
uint32_t s21_uint_n_mul(uint32_t *a, uint32_t a_len, uint32_t b,
                        bool additional_int, uint32_t *res);

/**
 * Adds a long number to another long number, stores the result under `res`
 * pointer, and returns overflowing value. If an `additional_int` is set then
 * overflowing value will be stored to the most significant int of a res.
 *
 * @param a one of the long summands
 * @param a_len count of uint32 numbers in `a` array
 * @param b one of the long summands
 * @param b_len count of uint32 numbers in `b` array
 * @param additional_int tells that overflowing value will be stored to the high
 * uint32 of `res` instea#include <stdio.h>
d of being returned
 * @param res long number to store sum to
 * @return addition overflow
 */
uint32_t s21_uint_n_add(uint32_t *a, size_t a_len, uint32_t *b, size_t b_len,
                        bool additional_int, uint32_t *res);

/**
 * Subtract one long number from another, stores the result under `res` pointer.
 *
 * @param minuend a long number to subtract from
 * @param minuend_len count of uint32 numbers in `minuend` array
 * @param subtrahend a long number to be subtracted
 * @param subtrahend_len count of uint32 numbers in `subtrahend` array
 * @param res long number to store difference to
 * @return 0 on success and UINT32_MAX otherwise
 */
uint32_t s21_uint_n_sub(uint32_t *minuend, size_t minuend_len,
                        uint32_t *subtrahend, size_t subtrahend_len,
                        uint32_t *res);

/**
 * Divides a long number to an int, stores the result under some pointer, and
 * returns ramainder of the division.
 *
 * @param dividend long dividend
 * @param divisible_len count of ints which compose long int
 * @param divisor int divisor
 * @param res long number to store quotient to
 * @return remainder of the division
 */
uint32_t s21_uint_n_div(uint32_t *dividend, size_t divisible_len,
                        uint32_t divisor, uint32_t *res);

#endif
