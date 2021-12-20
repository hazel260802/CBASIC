#include<stdio.h>

int k, n;
int arr[2][32] = {0};
int m[32] = {0};
int check = 0;
int count = 0;

void output() {
    for (int i = 0; i < k; i++) {
        printf("%d ", arr[1][i]);
    }
    printf("\n");
}

int TRY(int v) {
    if (v == k) {
        if (count == 1) {
            output();
            check++;
        }
    } else {
        for (int i = v; i < n; i++) {
            if (!m[i]) {
                m[i] = 1;
                arr[1][v] = arr[0][i];
                if (arr[1][v] % 2 == 1) count++;
                if (count <= 1) TRY(v + 1);
                if (arr[1][v] % 2 == 1) count--;
                m[i] = 0;
            }
        }
    }
    return check;
}

int main() {
    printf("Nhap k, n: ");
    scanf("%d %d", &k, &n);
    printf("Nhap mang:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[0][i]);
    }
    if (!TRY(0)) printf("NO\n");
    return 0;
}
