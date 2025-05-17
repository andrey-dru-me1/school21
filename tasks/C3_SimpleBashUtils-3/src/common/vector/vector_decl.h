#if defined(TYPE) && defined(NAME)

#include <string.h>

#include "../arr/arr.h"
#include "../cat_macro.h"
#include "defines.h"

/**
 * Represents array with ability to grow. Lies on heap, not stack. Has to be
 * freed.
 */
typedef struct STRUCT_TYPE {
  TYPE *dat;
  size_t len;
  size_t cap;
} STRUCT_TYPE;

/**
 * Creates new vector with specified capacity.
 *
 * @param init_cap initial capacity - count of elements to be allocated
 * @param v variable where vector will be place as a result
 * @returns SUCCESS or ALLOCATION_ERROR
 */
int CAT2(NAME, vec_alloc)(size_t init_cap, STRUCT_TYPE *v);

/**
 * Append element to a vector's end.
 *
 * @param v vector to modify
 * @param val value to insert to an array
 * @returns SUCCESS or ALLOCATION_ERROR
 */
int CAT2(NAME, vec_add)(STRUCT_TYPE *v, TYPE val);

/**
 * Inserts element to a vector on i'th position.
 *
 * @param v vector to modify
 * @param val value to insert to an array
 * @param i index of an array to insert a value
 * @returns SUCCESS, INDEX_OUT_OF_BOUNDS or ALLOCATION_ERROR
 */
int CAT2(NAME, vec_add_i)(STRUCT_TYPE *v, TYPE val, size_t i);

void CAT2(NAME, vec_clear)(STRUCT_TYPE *v);

int CAT2(NAME, vec_add_all)(STRUCT_TYPE *v, CAT2(NAME, arr) elems);

int CAT2(NAME, vec_add_all_i)(STRUCT_TYPE *v, CAT2(NAME, arr) elems, size_t i);

/**
 * Removes i'th element of a vector.
 *
 * @param v vector remove element from
 * @param i index of an array to remove
 * @returns SUCCESS or INDEX_OUT_OF_BOUNDS
 */
int CAT2(NAME, vec_rm)(STRUCT_TYPE *v, size_t i);

/**
 * Frees the vector.
 *
 * @param v vector to free
 */
void CAT2(NAME, vec_free)(STRUCT_TYPE *v);

#undef STRUCT_TYPE

#endif