#include "dict.h"

#include <linux/string.h>
#include <linux/module.h>

#include "lib.h"
#include "vector.h"

MODULE_LICENSE("GPL");

State *dict_get(char *key) {
  State *ret_state = New(State);
  if (strcmp(key, "R") == 0) {
    int cp[] = {0, 2, 6, 3, 4, 1, 5, 7};
    int co[] = {0, 1, 2, 0, 0, 2, 1, 0};
    int ep[] = {0, 5, 9, 3, 4, 2, 6, 7, 8, 1, 10, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "RP") == 0) {
    int cp[] = {0, 5, 1, 3, 4, 6, 2, 7};
    int co[] = {0, 1, 2, 0, 0, 2, 1, 0};
    int ep[] = {0, 9, 5, 3, 4, 1, 6, 7, 8, 2, 10, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "R2") == 0) {
    int cp[] = {0, 6, 5, 3, 4, 2, 1, 7};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 2, 1, 3, 4, 9, 6, 7, 8, 5, 10, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "L") == 0) {
    int cp[] = {4, 1, 2, 0, 7, 5, 6, 3};
    int co[] = {2, 0, 0, 1, 1, 0, 0, 2};
    int ep[] = {11, 1, 2, 7, 4, 5, 6, 0, 8, 9, 10, 3};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "LP") == 0) {
    int cp[] = {3, 1, 2, 7, 0, 5, 6, 4};
    int co[] = {2, 0, 0, 1, 1, 0, 0, 2};
    int ep[] = {7, 1, 2, 11, 4, 5, 6, 3, 8, 9, 10, 0};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "L2") == 0) {
    int cp[] = {7, 1, 2, 4, 3, 5, 6, 0};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {3, 1, 2, 0, 4, 5, 6, 11, 8, 9, 10, 7};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "U") == 0) {
    int cp[] = {3, 0, 1, 2, 4, 5, 6, 7};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 1, 2, 3, 7, 4, 5, 6, 8, 9, 10, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "UP") == 0) {
    int cp[] = {1, 2, 3, 0, 4, 5, 6, 7};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 1, 2, 3, 5, 6, 7, 4, 8, 9, 10, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "U2") == 0) {
    int cp[] = {2, 3, 0, 1, 4, 5, 6, 7};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 1, 2, 3, 6, 7, 4, 5, 8, 9, 10, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "D") == 0) {
    int cp[] = {0, 1, 2, 3, 5, 6, 7, 4};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 8};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "DP") == 0) {
    int cp[] = {0, 1, 2, 3, 7, 4, 5, 6};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 1, 2, 3, 4, 5, 6, 7, 11, 8, 9, 10};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "D2") == 0) {
    int cp[] = {0, 1, 2, 3, 6, 7, 4, 5};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 8, 9};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "F") == 0) {
    int cp[] = {0, 1, 3, 7, 4, 5, 2, 6};
    int co[] = {0, 0, 1, 2, 0, 0, 2, 1};
    int ep[] = {0, 1, 6, 10, 4, 5, 3, 7, 8, 9, 2, 11};
    int eo[] = {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "FP") == 0) {
    int cp[] = {0, 1, 6, 2, 4, 5, 7, 3};
    int co[] = {0, 0, 1, 2, 0, 0, 2, 1};
    int ep[] = {0, 1, 10, 6, 4, 5, 2, 7, 8, 9, 3, 11};
    int eo[] = {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "F2") == 0) {
    int cp[] = {0, 1, 7, 6, 4, 5, 3, 2};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {0, 1, 3, 2, 4, 5, 10, 7, 8, 9, 6, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "B") == 0) {
    int cp[] = {1, 5, 2, 3, 0, 4, 6, 7};
    int co[] = {1, 2, 0, 0, 2, 1, 0, 0};
    int ep[] = {4, 8, 2, 3, 1, 5, 6, 7, 0, 9, 10, 11};
    int eo[] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "BP") == 0) {
    int cp[] = {4, 0, 2, 3, 5, 1, 6, 7};
    int co[] = {1, 2, 0, 0, 2, 1, 0, 0};
    int ep[] = {8, 4, 2, 3, 0, 5, 6, 7, 1, 9, 10, 11};
    int eo[] = {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  } else if (strcmp(key, "B2") == 0) {
    int cp[] = {5, 4, 2, 3, 1, 0, 6, 7};
    int co[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ep[] = {1, 0, 2, 3, 8, 5, 6, 7, 4, 9, 10, 11};
    int eo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret_state->cp = vec_new_from_arr(cp, 8);
    ret_state->co = vec_new_from_arr(co, 8);
    ret_state->ep = vec_new_from_arr(ep, 12);
    ret_state->eo = vec_new_from_arr(eo, 12);
  }
  return ret_state;
}
