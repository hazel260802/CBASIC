#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgen/ext/io.h"
typedef char* pchar;
#define to_s(p) (*(const pchar*)p)
int cmp_inc_s (const void *a, const void *b){
    printf ("Before sorting:\n");
    printf ("%s %s\n", to_s(a), to_s(b));//* a co kieu char *
    return strcmp (to_s(a), to_s(b));
}
int main(){
    long n;
    pchar *arr;
    printf("Value n: ");
    scanf("%ld",&n);
    arr = calloc(n, sizeof(pchar));//char *arr[n];
    printf("Enter %ld strings\n",n);
    pchar s=NULL;
    clear_stdin();
    for (int i=0;i<n;i++){
        if(cgetline(&s,0,stdin)){
            remove_tail_lf(s);
            arr[i]=strdup(s);
        }
    }
    free(s);
    //arr[i] co kieu char *,
    //cmp_inc_s nhan dia chi cua arr[i]
    //=> kieu dung char **
    qsort((void*)arr,n,sizeof (char*),cmp_inc_s);
    printf("after sort :");
    for (int i=0;i<n;i++){
        printf("[%s] ",arr[i]);
    }
    printf("\n");
    for(int i=0;i<n;i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}