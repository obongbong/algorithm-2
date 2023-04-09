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
	printf("�ȳ��ϼ���. �׽�Ʈ �սô�.\n");

	srand(time(NULL));

	for (i = 0; i < n; i++)
	{
		a = rand();
		b = rand();
		gcd = euclidRecursive(a, b);
		printf("%d �� %d�� �ִ������� %d�Դϴ�.\n", a, b, gcd);

		gcd1 = euclidRepeatitive(a, b);
		printf("%d �� %d�� �ִ������� %d�Դϴ�.\n", a, b, gcd1);
		if (gcd == gcd1)
		{
			printf("�ִ����� %d�� %d�� ���� �����ϴ�.\n\n", gcd, gcd1);
		}
	}

	return 0;
}
