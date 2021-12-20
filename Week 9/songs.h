#include<stdio.h>


void songs_menu(); //Xuat ra bang loc theo thuoc tinh
int sort(); // Lua chon 1 thay doi mong muon
void songs_sort(); // Xu ly lua chon


void songs_menu(){
    printf("=================Lọc theo thuộc tính================\n");
    printf("1. Tên bài hát\n");
    printf("2. Ca sỹ\n");
    printf("3. Nhạc sỹ\n");
    printf("4. Năm sáng tác\n");
    printf("Lựa chọn của bạn là [1, 2, 3, 4]: ");
}
int sort(){
    int n=0;
    printf("Lựa chọn của bạn là [1, 2, 3, 4]: ");
    scanf("%d",&n);   
    if(n>0||n<5)return n;
    else return sort(); 
}
void songs_sort(){
    int c= sort();
    switch(c) {
        case 1: 
            printf("1. Tên bài hát\n");
            break;
        case 2:
            printf("2. Ca sỹ\n");
            break;
        case 3:
            printf("3. Nhạc sỹ\n");
            break;
        case 4:
            printf("4. Năm sáng tác\n");
            break;
    }
}