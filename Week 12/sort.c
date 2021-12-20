#include"functions.c"
#define to_s(x) (*(song_t*)x)
int song_cmp_name(const void *v1, const void *v2){
  return strcmp(to_s(v1)->name,to_s(v2)->name);
}
int song_cmp_singer(const void *v1, const void *v2){
  return strcmp(to_s(v1)->singer,to_s(v2)->singer);
}
int song_cmp_musician(const void *v1, const void *v2){
  return strcmp(to_s(v1)->musician,to_s(v2)->musician);
}
int song_cmp_year(const void *v1, const void *v2){
    char *p1=to_s(v1)->year;
    char *p2=to_s(v2)->year;
    int t1, t2;
    sscanf(p1, "%d", &t1);
    sscanf(p2, "%d", &t2);
    return t1-t2;
}
void sort(song_t *s, int n, int c){
    switch(c) {
        case 1: 
            qsort(s,n, sizeof(song_t), song_cmp_name);
            break;
        case 2: 
            qsort(s,n, sizeof(song_t), song_cmp_singer);
            break;
        case 3: 
            qsort(s,n, sizeof(song_t), song_cmp_musician);
            break;
        case 4: 
            qsort(s,n, sizeof(song_t), song_cmp_year);
            break;
    }
}