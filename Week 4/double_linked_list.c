#include "double_linked_list.h"

#include <stdlib.h>

dll_node_t dll_create_node() {
  dll_node_t n = malloc(sizeof(struct dll_node_s));
  n->next = n->prev = NULL;
  return n;
}

void dll_free_node(dll_node_t node) {
  free(node);
}

dll_t dll_create_list() {
  dll_t list = malloc(sizeof(struct dll_s));
  list->front = list->back = NULL;
  return list;
}

void dll_free_list(dll_t list) {}

void dll_push_back(dll_t list, dll_node_t nn) {
  if (list->back == NULL) {
    list->back = nn;
    list->front = nn;
  } else {
    nn->prev = list->back;
    list->back->next = nn;
    list->back = list->back->next;
  }
}
void dll_push_front(dll_t list, dll_node_t nn) {
  if (list->front == NULL) {
    list->front = nn;
    list->back = nn;
  } else {
    nn->next = list->front;
    list->front->prev = nn;
    list->front = list->front->prev;
  }
}
void dll_pop_back(dll_t list){
  if (list->front == NULL && list->back == NULL) {
    return ;
  }
  dll_node_t tmp = list->back;
  list->back = tmp->prev;
  if (list->back) {
    list->back->next = NULL;
  } else {
    list->front = NULL;
  }
  free(tmp); 
}
void dll_pop_front(dll_t list){
  if (list->front == NULL && list->back == NULL) {
    return ;
  }
  dll_node_t tmp = list->front;
  list->front = tmp->next;
  if (list->front) {
    list->front->prev = NULL;
  } else {
    list->back = NULL;
  }
  free(tmp); 
}
dll_node_t dll_front(dll_t list){
  return list->front; 
}
dll_node_t dll_back(dll_t list){
  return list->back;
}
dll_node_t dll_inserta(dll_t list, dll_node_t pos, dll_node_t nn){
  if (pos) {
    dll_node_t tmp = pos->next;
    pos->next = nn;
    nn->next = tmp;
    nn->prev = pos;
    if (tmp) {
      tmp->prev = nn;
    } else {
      list->back = nn;
    }
  } else {
    dll_push_back(list, nn);
  }
  return nn;
}
dll_node_t dll_insertb(dll_t list, dll_node_t pos, dll_node_t nn){
  if (pos) {
    dll_node_t tmp = pos->prev;
    pos->prev = nn;
    nn->prev = tmp;
    nn->next = pos;
    if (tmp) {
      tmp->next = nn;
    } else {
      list->front = nn;
    }
  } else {
    dll_push_front(list, nn);
  }
  return nn;
}
int dll_is_empty(dll_t list){
  if (list->front == NULL && list->back == NULL) {
    return 1;
  } else {
    return 0;
  }
}
long dll_length(dll_t list){
  if (list->front == NULL && list->back == NULL) {
    return 0;
  } else {
    dll_node_t n = list->front;
    long count = 0;
    while (n != NULL) {
      count++;
      n = n->next;
    }
    return count;
  }
}
void dll_clear(dll_t list){}
void dll_erase(dll_t list, dll_node_t pos){}
