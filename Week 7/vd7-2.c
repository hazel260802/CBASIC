/*
  (C) Nguyễn Bá Ngọc 2021
  Minh họa sử dụng ánh xạ dựa trên cây đỏ/đen
  Chương trình hỏi người dùng nhập vào từng chuỗi
  ký tự cho tới khi người dùng nhập chuỗi rỗng
  (chỉ nhấn enter). Sau đó chương trình đưa
  ra các chuỗi người dùng đã nhập cùng với số lần
  chuỗi đó được nhập.
*/

#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>
#include <string.h>
int main() {
  char buff[1024];
  printf("Nhập chuỗi ký tự (hoặc chỉ bấm Enter): \n");
  rbm_t words = rbm_create(gtype_cmp_s);
  do {
    remove_tail_lf(fgets(buff, 1024, stdin));
    if (buff[0] == '\0') {
      break;
    }
    char *s = strdup(buff);
    rbm_node_t n = rbm_insert(words, gtype_s(s), gtype_i(-1));
     if (rbm_node_value(n).i < 0) {
       rbm_node_value(n).i = 1;
     } else {
       rbm_node_value(n).i++;
       free(s);
     }
  } while (1);
  printf("Các từ đã nhập và số lần nhập: \n");
  rbm_traverse(cur, words) {
    printf("%s: %ld\n",
      rbm_node_key(cur).s, rbm_node_value(cur).i);
  }
  rbm_traverse(cur, words) {
    free(rbm_node_key(cur).s);
  }
  rbm_free(words);
  return 0;
}