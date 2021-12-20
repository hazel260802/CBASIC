#include<stdio.h>
#include<stdlib.h>
#define to_double(p) (*((const double*)p))
int cmp_inc_d(const void *a, const void *b){
    return to_double(a) - to_double(b);
}

int main(){
    long n;
    printf("Value n: ");
    scanf("%ld",&n);
    double *ptr= (double*)calloc(n,sizeof(double));
    printf("Enter value of array: \n");
    for(int i=0;i<n;++i){
        scanf("%lf",&ptr[i]);
    }
    printf("Before sorting:\n");
    for(int i=0;i<n;++i){
        printf("%.2lf ", ptr[i]);
    }
    printf("\n");
    qsort(ptr,n,sizeof(double),cmp_inc_d);
    printf("After sorting:\n");
    for(int i=0;i<n;++i){
        printf("%.2lf ", ptr[i]);
    }
    printf("\n");
    //Luu y: giai phong vung nho con tro
    free(ptr);
    return 0;
}