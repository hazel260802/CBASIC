#include <stdio.h>
//Day Fibonaci

int fibo (int n) {
	if (n == 0 || n == 1) {
		return 1;
	}
	return fibo(n - 1) + fibo(n - 2);
}

/*
	fibo(8) = fibo(7) + fibo(6)
		fibo(7) = fibo(6) + fibo(5)
			fibo(6) = fibo(5) + fibo(4)
	=> Co choonfg laasn trong caasu trucs chia nhor baif toasn
*/
int main() {
	int n;
	printf("Nhap n = ");
	scanf("%d", &n);
	printf("%d\n", fibo(n));
	return 0;
}
