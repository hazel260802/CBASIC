#include<stdio.h>
#include"cgen.h"
#include<stdlib.h>

#define to_i(x) (*(const int *)x)
int compare_i(const void *a, const void *b){
    return to_i(a) - to_i(b);
}

//---------------------TIM KIEM NHI PHAN --------------------------------
// tim kiem trong khoang nua mo l≤i<r
//tra ve 1 neu tim thay q va tra ve 0 neu nguoc lai
int binsearch(int l, int r, int *a, int q){
    if(l>=r){
        return 0;
    }
    int i=(l+r)/2; //Dam bao lon hon l va nho hon r
    if(a[i]>q){
        return binsearch(l,i,a,q);
    }
    else if (a[i]<q){
        return binsearch(i+1,r,a,q);
    }
    return 1;
}
int main(int argc, char *argv[]){
//-----------------------DOC TEP VA LUU MANG --------------------------------
    if (argc !=3){
        printf("Usage: ./prog inp.txt 101\n");
        return 1;
    }
    int q;
    sscanf(argv[2], "%d",&q);
    FILE *f = fopen(argv[1], "r");
    int n;
    fscanf(f, "%d",&n);
    int *a =malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        fscanf(f, "%d",a+i);
    }
    printf("n = %d, q = %d\n", n, q);
    //for(int i=0;i<n;i++){
    //    printf("%d ", a[i]);
    //}

int count1=0;
//--------------------TIM KIEM NHI PHAN-----------------------------
    BENCH("TIM KIEM NHI PHAN", 1, 
    count1=0;
    qsort(a,n,sizeof(int),compare_i);
    for(int i=0;i<n-1; ++i){
        //can tim j>i sao cgi a[i]+a[j]=q
        if(binsearch(i+1,n,a,q-a[i]))count1++;
    }
);
    printf("Tim kiem nhi phan: %d\n",count1);

// --------------------VET CAN -----------------------------    
    int count2=0;
    BENCH("VET CAN", 1,    
    for(int i=0;i<n-1;++i){
        for(int j=i+1;j<n;++j){
            //printf("%d +%d\n", a[i], a[j]);
            if(a[i]+a[j]==q)count2++;
        }
    });
    printf("Vet can: %d\n",count2);

    free(a);
    fclose(f);
    return 0;
}
//gcc -o prog bt9-1.c cgen//all.c -I cgen
//./prog inp10k.txt 1000000