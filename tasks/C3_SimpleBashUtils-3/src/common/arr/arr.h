#if defined(TYPE) && defined(NAME)

#include <stddef.h>

#include "../cat_macro.h"

#define STRUCT_TYPE CAT2(NAME, arr)

/**
 * A wrapper over a simple array contains length of the array.
 */
typedef struct STRUCT_TYPE {
  TYPE *dat;
  int len;
} STRUCT_TYPE;

#undef STRUCT_TYPE

#endif
