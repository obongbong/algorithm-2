#include <stdio.h>
#include "euclid.h"
#include <stdlib.h>
#include <time.h>

int testeuclid()
{
	int n = 1000;
	int i, a= 0, b = 0;

	int gcd = 0;
	int gcd1 = 0;
	printf("안녕하세요. 테스트 합시다.\n");

	srand(time(NULL));

	for (i = 0; i < n; i++)
	{
		a = rand();
		b = rand();
		gcd = euclidRecursive(a, b);
		printf("%d 와 %d의 최대공약수는 %d입니다.\n", a, b, gcd);

		gcd1 = euclidRepeatitive(a, b);
		printf("%d 와 %d의 최대공약수는 %d입니다.\n", a, b, gcd1);
		if (gcd == gcd1)
		{
			printf("최대공약수 %d와 %d의 값이 같습니다.\n\n", gcd, gcd1);
		}
	}

	return 0;
}
