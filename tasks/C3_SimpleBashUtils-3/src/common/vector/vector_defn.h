#if defined(TYPE) && defined(NAME)

#include <malloc.h>
#include <stddef.h>
#include <string.h>

#include "../cat_macro.h"
#include "defines.h"

int CAT2(NAME, vec_alloc)(size_t init_cap, STRUCT_TYPE *v) {
  int exit_stat = SUCCESS;
  TYPE *dat = calloc(init_cap, sizeof(TYPE));
  if (dat == NULL)
    exit_stat = ALLOCATION_ERROR;
  else
    *v = (STRUCT_TYPE){.dat = dat, .len = 0, .cap = init_cap};
  return exit_stat;
}

int CAT2(NAME, vec_add)(STRUCT_TYPE *v, TYPE val) {
  return CAT2(NAME, vec_add_i)(v, val, v->len);
}

int CAT2(NAME, vec_add_i)(STRUCT_TYPE *v, TYPE val, size_t i) {
  if (i > v->len) return INDEX_OUT_OF_BOUNDS;
  int exit_stat = SUCCESS;
  v->len++;
  if (v->len >= v->cap) {
    if (v->cap == 0)
      v->cap = 2;
    else
      v->cap *= 2;
    v->dat = realloc(v->dat, sizeof(TYPE) * v->cap);
    if (v->dat == NULL) exit_stat = ALLOCATION_ERROR;
  }
  if (!exit_stat) {
    TYPE *ptri = v->dat + i;

    // `v->len - 1` is used instead of `v->len` because v->len has increased
    if (i < v->len - 1)
      memmove(ptri + 1, ptri, sizeof(TYPE) * (v->len - 1 - i));

    v->dat[i] = val;
  }
  return exit_stat;
}

int CAT2(NAME, vec_add_all)(STRUCT_TYPE *v, CAT2(NAME, arr) elems) {
  return CAT2(NAME, vec_add_all_i)(v, elems, v->len);
}

int CAT2(NAME, vec_add_all_i)(STRUCT_TYPE *v, CAT2(NAME, arr) elems, size_t i) {
  if (i > v->len) return INDEX_OUT_OF_BOUNDS;
  int exit_stat = SUCCESS;

  if (v->len + elems.len > v->cap) {
    v->cap = (v->len + elems.len) * 3 / 2;
    v->dat = realloc(v->dat, sizeof(TYPE) * v->cap);
    if (v->dat == NULL) exit_stat = ALLOCATION_ERROR;
  }
  if (!exit_stat) {
    memmove(v->dat + i + elems.len, v->dat + i, sizeof(TYPE) * (v->len - i));
    memmove(v->dat + i, elems.dat, sizeof(TYPE) * elems.len);
    v->len += elems.len;
  }
  return exit_stat;
}

void CAT2(NAME, vec_clear)(STRUCT_TYPE *v) { v->len = 0; }

int CAT2(NAME, vec_rm)(STRUCT_TYPE *v, size_t i) {
  int exit_stat = SUCCESS;
  if (i < v->len) {
    TYPE *ptri = v->dat + i;
    memmove(ptri, ptri + 1, sizeof(TYPE) * (v->len - i - 1));
    v->len--;
  } else {
    exit_stat = INDEX_OUT_OF_BOUNDS;
  }
  return exit_stat;
}

void CAT2(NAME, vec_free)(STRUCT_TYPE *v) { free(v->dat); }

#undef STRUCT_TYPE

#endif
