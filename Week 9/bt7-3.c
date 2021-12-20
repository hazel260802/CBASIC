#include "all.c"
#include <time.h>
typedef char* pchar;
#define to_s(p) (*(const pchar*)p)
#define to_node(x) (*(const node *)x) // từ con trỏ void*, chuyển thành dạng node
int cmp_inc_s (const void *a, const void *b){
    //printf ("Before sorting:\n");
    //printf ("%s %s\n", to_s(a), to_s(b));//* a co kieu char *
    return strcmp (to_s(a), to_s(b));
}
typedef struct node {
    char *w;
    int a;
}node;
int cmp_inc_i(const void *a, const void *b){
  //so sanh so lan xuat hien theo thu tu giam dan
  return to_node(b).a - to_node(a).a;
}

int main(int argc, char *argv[]){
  clock_t start=clock();
  if (argc != 2) {
    printf("Usage: ./prog input.txt\n");
    return 1;
  }
  FILE *inp = fopen(argv[1], "r");
  if (!inp) {
      printf("Lỗi mở tệp %s\n", argv[1]);
      return 1;
  }
  int i=0;
  char buff[1024];
  sll_t list=sll_create_list();
/*Nhập dữ liệu vào, 
cho vào danh sách liên kết để tìm số lượng từ, cho ngược lại vào mảng để sort*/
  while(feof(inp)==0){
      fscanf(inp, "%s",buff);
      //printf("%s\n",buff);
      sll_push_back_g(list, (gtype){.s = strdup (buff)});
      i++;
  }
    //printf("%d\n",i);
    //sll_pprint_list(list);
    //sll_traverse(cur,list){
    //    printf("%s ",sll_node_g_value(cur).s);
    //}
    long l=sll_length(list);
    printf("So luong tu: %ld\n", l);
    pchar *a =calloc(i, sizeof(pchar));
    int idx=0;
    sll_traverse(cur,list){
        a[idx++]=sll_node_g_value(cur).s;
    }
    qsort(a,l,sizeof(a[0]),cmp_inc_s);

    /*-------------------------------------------*/


    /*Lưu phần tử khác nhau vào node, số lần lặp được lưu lại vào node.a, 
    text được lưu vào node.w, xong sort lại node theo node.a 
    để có thứ tự xuất hiện từ bé đến lớn*/
        node *result = calloc(i, sizeof(node));
    int count = 1;
    idx = 0;
    result[0].w = a[0]; // lưu lại kí tự 
    for(int j=1; j<i; j++){
        if(!strcmp(a[j],a[j-1])){ // nếu phần tử đang duyệt giống phần tử trước đó thì biến đếm +1
            count ++;
        }
        else{
            result[idx].a = count; // lưu lại số lần xuất hiện
            idx++;
            result[idx].w = a[j];
            result[idx].a = 1;
            count = 1; // reset count
        }
    }
    qsort(result, idx, sizeof(node), cmp_inc_i); // sắp xếp theo số lượng xuất hiện
    //printf("So luong tu: %d\n",i);
    printf("So luong tu khac nhau: %d\n",idx+1);
    for(int j=0; j<10; j++){
        printf("%s - %d lan\n",result[j].w, result[j].a);
    }
    /*-------------------------------------------*/
    free(result);
    free(a);
    fclose(inp);
  sll_free_list(list);
  clock_t end = clock();
  double time_process = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Thoi gian xu ly: %lf\n",time_process);
  return 0;
}
//gcc -o bt7-3 bt7-3.c -I cgen   
// ./bt7-3 text/lisa_all_text.txt
