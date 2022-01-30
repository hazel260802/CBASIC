#include "cgen.h"
#include "ext/io.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
typedef struct item_s {
    char *code;//Mã số
    char *name;//Tên mặt hàng
    double cost;//Giá tiền
    int number;//Số lượng trong kho
} *item_t;
item_t item_create() {
  item_t item = malloc(sizeof(struct item_s));
  item->name = item->code = NULL;
  return item;
}
const char *field_sep = " ";
enum {
  ITEM_NULL,
  ITEM_NAME,
  ITEM_CODE,
  ITEM_COST,
  ITEM_NUMBER,
  ITEM_ELEMENTS
};
const char *field_names[] = {" ", "Mặt hàng", "Đơn giá ", "Số lượng", "Tiền",""};
const int field_width[] = {3, 20, 20, 5, 15, 0};

int estimate_utf8(const char *s) {
  int cc = 0;
  while (*s) {
    if ((*s & 0xC0) != 0x80) {
      ++cc;
    }
    ++s;
  }
  return cc;
}

void gtype_free_item(gtype value) {
  item_t item = (item_t)(value.v);
  free(item->name);
  free(item->code);
  free(item);
}
void pprint_utf8(const char *s, int width) {
  int align = width - estimate_utf8(s);
  if (align < 0) {
    align = 0;
  }
  printf("%s%*s", s, align, " ");
}

void gtype_pprint_item(gtype value) {
  item_t item = (item_t)(value.v);
  pprint_utf8(item->code, field_width[ITEM_CODE]);
  pprint_utf8(item->name, field_width[ITEM_NAME]);
  printf("%*d", -field_width[ITEM_NUMBER], item->number);
  printf("%*.2lf", -field_width[ITEM_COST], item->cost);
  printf("\n");
}

void item_list_pprint(gvec_t items) {
  for (int i = ITEM_NULL + 1; i < ITEM_ELEMENTS; ++i) {
    pprint_utf8(field_names[i], field_width[i]);
  }
  printf("\n");
  gvec_traverse(g, items) {
    gtype_pprint_item(*g);
  }
}

void item_list_idx_pprint(gvec_t items, gvec_t positions) {
  printf("STT  ");
  for (int i = ITEM_NULL + 1; i < ITEM_ELEMENTS; ++i) {
    pprint_utf8(field_names[i], field_width[i]);
  }
  printf("\n");
  gvec_traverse(cur, positions) {
    printf("%3ld  ", gvec_elem_idx(positions, cur) + 1);
    gtype_pprint_item(gvec_elem(items, cur->l));
  }
}

#define parse_attrib(line, sign, attrib) \
  do { \
    char *tmp; \
    if ((tmp = strstr(line, sign)) == NULL) { \
      return NULL; \
    } \
    attrib = line; \
    *tmp = 0; \
    line = tmp + strlen(sign); \
  } while (0)

item_t parse_item(char *line) {
  char *name, *code, *pnumber,*pcost;
  parse_attrib(line, field_sep, code);
  parse_attrib(line, field_sep, name);
  pnumber = line;
  int number;
  parse_attrib(line, field_sep, number);
  if (sscanf(pnumber, "%d", &number) != 1) {
    return NULL;
  }
  pcost = line;
  double cost;
  if (sscanf(pcost, "%lf", &cost) != 1) {
    return NULL;
  }
  item_t item = item_create();
  item->code = strdup(code);
  item->name = strdup(name);
  item->number=number;
  item->cost = cost;
  return item;
}
#undef parse_attrib
gvec_t parse_items_list(const char *fname) {
  FILE *f = fopen(fname, "r");
  if (!f) {
    printf("Không thể mở tệp %s\n", fname);
    return NULL;
  }
  gvec_t items = gvec_create(10, gtype_free_item);
  char *line = NULL;
  item_t tmp;
  while (cgetline(&line, 0, f)) {
    if ((tmp = parse_item(line))) {
      gvec_append(items, gtype_v(tmp));
    }
  }
  free(line);
  fclose(f);
  return items;
}
#define to_item(p) ((item_t)(((const gtype*)p)->v))
int item_cmp_code(const void* v1, const void* v2) {
  return  strcmp(to_item(v1)->code, to_item(v2)->code);
}
int item_cmp_number(const void* v1, const void* v2) {
  return to_item(v1)->number - to_item(v2)->number;
}
#undef to_item
int (*item_cmp[])(const void *, const void*) = {NULL,
    item_cmp_code, item_cmp_number};


gvec_t item_filter_1(gvec_t items) {
  printf("Bạn muốn tìm mặt hàng nào: \n");
  gvec_qsort(items, item_cmp[1]);
  gvec_t filtered = gvec_create(10, NULL);
  char *sub = NULL;
      printf("Nhập chuỗi truy vấn: ");
      remove_tail_lf(cgetline(&sub, 0, stdin));
  gvec_traverse(cur, items) {
    item_t item = (item_t)(cur->v);
    int ok = (strstr(item->code, sub) != NULL);
    if (ok) {
      gvec_append(filtered, gtype_l(gvec_elem_idx(items, cur)));
    }
  }

  free(sub);
  return filtered;
}
void item_search(gvec_t items) {
  gvec_t filtered =  item_filter_1(items);
  if (filtered) {
    item_list_idx_pprint(items, filtered);
    gvec_free(filtered);
  } 
  else{
    printf("Đã phát sinh lỗi\n");
  }
}
void item_filter_2(gvec_t items) {
  int n,ex=0;
  double total = 0;
  printf("Bạn muốn tìm mặt hàng nào: \n");
  gvec_qsort(items, item_cmp[1]);
  gvec_t filtered = gvec_create(10, NULL);
  char *sub = NULL;
    for(;;){
      printf("Nhập chuỗi truy vấn: ");
      remove_tail_lf(cgetline(&sub, 0, stdin));
      if(strcmp(sub,"STOP")!=0){
        gvec_traverse(cur, items) {
          item_t item = (item_t)(cur->v);
          int ok = (strstr(item->code, sub) != NULL);
          if (ok) {
            ex++;
            printf("Nhập số lượng: ");
            scanf("%d",&n);
            clear_stdin();
            if(item->number-n<0)printf("Không đủ hàng\n");
            else{
                item->number=n;
                item->cost=n*item->cost;
                total+=item->cost;
              gvec_append(filtered, gtype_l(gvec_elem_idx(items, cur)));
            }
          }
        }
        if(ex==0)printf("Mặt hàng không tồn tại\n");
      }
      else{
        break;
      }
    }

  if (filtered) {
    item_list_idx_pprint(items,filtered);
    printf("Total: %.2lf\n", total);
  } 
  else{
    printf("Đã phát sinh lỗi\n");
  }
  free(sub);
  gvec_free(filtered);
}



void save_items(gvec_t items, const char *fname) {
  FILE *f = fopen(fname, "w");
  if (!f) {
    printf("Lỗi mở tệp %s\n", fname);
    return;
  }
  gvec_traverse(cur, items) {
    item_t item = (item_t)(cur->v);
    fprintf(f, "%s%s%s%s%lf%s%d\n", item->code, field_sep, item->name,
                  field_sep, item->cost, field_sep, item->number);
  }
  fclose(f);
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog songs.txt\n");
    return 1;
  }
  char *fname = argv[1];
  gvec_t items = parse_items_list(fname);
  if (!items) {
    printf("Không thể đọc dữ liệu từ %s\n", fname);
    return 1;
  }
  int n;

  for (;;) {
    printf("Lựa chọn chức năng:\n"
           "1. Xem thông tin mặt hàng\n"
           "2. Tạo đơn hàng\n"
           "3. Thoát\n"
           "Lựa chọn của bạn [1-3]: ");
    int c = 0;
    scanf("%d", &c);
    clear_stdin();
    if (c == 1) {
      item_search(items);
    } else if (c == 2) {
            item_filter_2(items);
    } else if (c == 3) {
      break;
    } else {
      printf("Lựa chọn không hợp lệ.\n");
    }
  }
  gvec_free(items);
  return 0;
}
//gcc -o prog b11-1.c ./cgen/all.c -I ./cgen