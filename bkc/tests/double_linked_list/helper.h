#ifndef TESTS_DOUBLE_LINKED_LIST_HELPER_H_
#define TESTS_DOUBLE_LINKED_LIST_HELPER_H_

#include "double_linked_list.h"

static int dll_sequence(dll_t list, dll_node_t *a, int n) {
  dll_node_t p = list->front;
  for (int i = 0; i < n; ++i) {
    if (p != a[i]) {
      return 0;
    }
    p = p->next;
  }
  if (p != NULL) {
    return 0;
  }
  p = list->back;
  for (int i = n - 1; i >= 0; --i) {
    if (p != a[i]) {
      return 0;
    }
    p = p->prev;
  }
  if (p != NULL) {
    return 0;
  }
  return 1;
}

#endif  // TESTS_DOUBLE_LINKED_LIST_HELPER_H_