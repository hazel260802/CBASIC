#include <stdio.h>
#include <stdlib.h>

//tim kiem trong khoang nua mo l <= i < r
//tra ve 1 neu tim thay q va tra ve 0 neu nguoc lai
// 0 1 2 3 4 5 6 7 8 9
int binsearch(int l, int r, int *a, int q) {
	if (l >= r) {
		return 0;
	}
	int i = (l + r)/2;
	if (a[i] > q) {
		return binsearch(l, i, a, q);
	} else if (a[i] < q) {
		return binsearch(i+1, r, a, q);
	}
	return 1;
}

int main(int argc, char *argv[]) {
	int a[] = {10, 20, 30, 50, 60, 70, 80, 90, 100, 110, 120};
	int n = sizeof(a)/sizeof(a[0]);
	printf("30: %d\n", binsearch(0, n, a, 30));
	printf("50:%d\n", binsearch(0, n, a, 50));
	printf("35: %d\n", binsearch(0, n, a, 35));
	printf("1: %d\n", binsearch(0, n, a, 1));
	printf("130: %d\n", binsearch(0, n, a, 130));
	printf("110: %d\n", binsearch(0, n, a, 110));
	return 0;
}
