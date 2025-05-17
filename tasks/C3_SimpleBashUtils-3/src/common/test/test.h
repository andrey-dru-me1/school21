#ifndef TEST_10_2023_H
#define TEST_10_2023_H

#include <stdbool.h>

/**
 * Prints in stdout test name and SUCCESS or FAILURE if test returns
 * respectively true or false.
 *
 * @param cond condition to test
 * @param test_name name of a test to print
 * @returns cond
 */
bool test(bool cond, const char *test_name);

#endif