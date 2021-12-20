#include <stdio.h>
//Tinh tong day so nguyen duong 1..n
int f(int n) {
	if (n == 1) {
		return 1;
	}
	return n + f(n-1);
}

/*
f(5) = 5 + f(4)
	f(4) = 4 + f(3)
		f(3) = 3 + f(2)
			f(2) = 2 + f(1)
			
*/

int main() {
	printf("Nhap n = ");
	int n;
	scanf("%d", &n);
	int sum = f(n);
	printf("sum = %d\n", sum); //de quy
	int tong = 0;
	for (int i = 1; i<=n; i++) {
		tong += i;
	}
	printf("tong = %d\n", tong); //quy hoach dong
	return 0;
}
