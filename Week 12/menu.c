#include<stdio.h>


void menu();// Xuat ra cac lua chon trong menu
int menu_choice(); // Xu ly lua chon
void property();
int prop_choice();
void heading();

void menu(){
    printf("=================MENU================\n");
    printf("1. Xem danh sách bài hát\n");
 
    printf("2. Lọc danh sách bài hát\n");
    printf("3. Thêm bài hát\n");
    printf("4. Xoá bài hát\n");
    printf("5. Thoát\n");
}
int menu_choice(){
    int c=0;
    printf("Lựa chọn của bạn là [1, 2, 3, 4, 5]: ");
    scanf("%d",&c);   
    if(c>0||c<6)return c;
    else return menu_choice();
}
void property(){
    printf("1. Ten bai hat\n");
    printf("2. Ten ca si\n");
    printf("3. Ten nhac si\n");
    printf("4. Nam sang tac\n");
}
int prop_choice(){
    int c=0;
    printf("Lựa chọn của bạn là [1, 2, 3, 4]: ");
    scanf("%d",&c);   
    if(c>0||c<5)return c;
    else return prop_choice();
}
void heading(){
    printf(" %30s", "Ten bai hat");
    printf(" %30s","Ten ca si");
    printf(" %30s","Ten nhac si");
    printf(" %30s\n\n","Nam sang tac");
}
